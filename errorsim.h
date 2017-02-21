//
//	CDpal
//
//  This software is intended to be used for curve fitting of CD thermal
//	denaturation data.
//
//  Copyright (C) 2015 Markus Niklasson and Patrik Lundström
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program. If not, see http://www.gnu.org/licenses/.
//
//  Programmers: Markus Niklasson and Patrik Lundström
//
//  Adress correspondence to: patlu@ifm.liu.se
//  Date: 21 February, 2017
//  Version: 2.16
//

#define N_MC 300
#define N_BOOTSTRAP 100

struct ErrorSim {
   std::vector< double > x, y, error;
   int size;
   std::vector< double > limit;
   std::vector< bool > fixedVec;
   int argSize;

   void (*function)(const double, std::vector< double > &, double &, std::vector< double > &);
   std::vector< double > jackerr;

   ErrorSim(std::vector< double > &xVec, std::vector< double > &yVec, std::vector< double > &variance, std::vector< double > &upLimit, std::vector< bool > &fixed,
        void (*fitData)(const double, std::vector< double > &, double &, std::vector< double > &)) :
        x(xVec), y(yVec), error(variance), size(x.size()), limit(upLimit), fixedVec(fixed), argSize(limit.size()), function(fitData) { }
	
   
   void simerror()
   {
       jackknife();
   }
   void jackknife()
   {
      double pseudoa;
      double xspare, yspare, errorspare;
      std::vector< double > s(argSize, 0.);
      std::vector< double > s2(argSize, 0.);
      std::vector< double > xjack(size-1);
      std::vector< double > yjack(size-1);
      std::vector< double > errorjack(size-1);

      for (int i=0; i<size-1; i++) {
		  xjack[i] = x[i];
		  yjack[i] = y[i];
          errorjack[i] = error[i];
      }
      xspare = x[size-1];
      yspare = y[size-1];
      errorspare = error[size-1];

      for (int i=0; i<size; i++) {
         fitFunction fitData(xjack, yjack, errorjack, limit, fixedVec, function);
         fitData.start();
		 
         for (int j=0; j<argSize; j++) {
            pseudoa = size*limit[j] - (size-1)*fitData.parVec[j];
			s[j] += pseudoa;
            s2[j] += pseudoa*pseudoa;
       	 }
         if (i<size-1) {
           std::swap(xjack[i],xspare);
           std::swap(yjack[i],yspare);
           std::swap(errorjack[i],errorspare);
		 }
	  }		
      jackerr.resize(argSize);
      for (int j=0; j<argSize; j++)
         jackerr[j] = sqrt((s2[j] - s[j]*s[j]/(double)size)/(double)(size*(size-1)));
   }		
};

