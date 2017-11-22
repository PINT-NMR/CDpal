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
//  Date: 18 August, 2017
//  Version: 2.18
//

#define N_MC 300
#define N_BOOTSTRAP 100

struct CDdiffErrorSim {


   std::vector< double > x, y, sig;
   int ndata;

   std::vector< double > guess;
   std::vector< bool > ia;
   int ma;

   void (*funcs)(const double, std::vector< double > &, double &, std::vector< double > &);

   std::vector< double > mcerr;
   std::vector< double > jackerr;
   std::vector< double > booterr;

   CDdiffErrorSim(std::vector< double > &xx, std::vector< double > &yy, std::vector< double > &ssig, std::vector< double > &gguess, std::vector< bool > &iia,
        void (*funks)(const double, std::vector< double > &, double &, std::vector< double > &)) :
        x(xx), y(yy), sig(ssig), ndata(x.size()), guess(gguess), ia(iia), ma(guess.size()), funcs(funks) { }


   void simerror(bool fmc, bool fjack, bool fboot)
   {
       montecarlo(fmc);
       jackknife(fjack);
       bootstrap(fboot);
   }

   void montecarlo(bool fmc=true)
   {
       if (!fmc)
           return;
   }

   void jackknife(bool fjack=true)
   {
      if (!fjack)
          return;

      double pseudoa;
      double xspare, yspare, sigspare;
      std::vector< double > chisqjack(ndata);
      std::vector< double > s(ma, 0.);
      std::vector< double > s2(ma, 0.);
      std::vector< double > xjack(ndata-1);
      std::vector< double > yjack(ndata-1);
      std::vector< double > sigjack(ndata-1);

      for (int i=0; i<ndata-1; i++) {
          xjack[i] = x[i];
          yjack[i] = y[i];
          sigjack[i] = sig[i];
      }
      xspare = x[ndata-1];
      yspare = y[ndata-1];
      sigspare = sig[ndata-1];

      for (int i=0; i<ndata; i++) {
         CDdiffFitmrq mrqfit(xjack, yjack, sigjack, guess, ia, funcs);
         mrqfit.fit();

         for (int j=0; j<ma; j++) {
            pseudoa = ndata*guess[j] - (ndata-1)*mrqfit.a[j];
            s[j] += pseudoa;
            s2[j] += pseudoa*pseudoa;
         }
         if (i<ndata-1) {
           std::swap(xjack[i],xspare);
           std::swap(yjack[i],yspare);
           std::swap(sigjack[i],sigspare);
         }
      }

      jackerr.resize(ma);
      for (int j=0; j<ma; j++)
         jackerr[j] = sqrt((s2[j] - s[j]*s[j]/(double)ndata)/(double)(ndata*(ndata-1)));
   }

   void bootstrap(bool fboot=true)
   {
   //////////////////////////////////
   // Bootstrap estimation of errors some data points are replaced
   // with duplicates of other data points in each round. The
   // standard error of the fitted values are used as a
   // measure of the uncertainty of the fitted parameters.
   //
   // BOOTSTRAP IS NO GOOD WHEN TO FEW DATA POINTS ARE FITTED
   // SINCE HIGHLY IRREGULAR DATA SETS MAY RESULT. A WORST
   // CASE SCENARIO IS THAT THE SAME DATA POINT IS DRAWN FOR
   // THE ENTIRE SET MEANING THAT THE PROGRAM EVEN CRASHES.
   // USE WITH CAUTION!!
   //
   // coded by Patrik Lundstrom
   //////////////////////////////////
       if (!fboot)
           return;
   }
};



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

