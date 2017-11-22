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

using namespace std;

struct fitFunction {
    int size, argSize;
    std::vector< double > &x,&y,&errVec;
    int counter, upperLimit;
    double limit;
    void (*function)(const double, std::vector< double > &, double &, std::vector< double > &);
    std::vector< bool > argVec;
    std::vector< double > parVec;
    std::vector< std::vector< double > > variance, tmpVariance;
    double chi;
    int rowVal;

    fitFunction(std::vector< double > &xVec, std::vector< double > &yVec, std::vector< double > &errVal, std::vector< double > &params,
       std::vector< bool > &fixed, void fitData(const double, std::vector< double > &, double &, std::vector< double > &),
       const int CC=4) : size(xVec.size()), argSize(params.size()), x(xVec), y(yVec), errVec(errVal),
          counter(CC), upperLimit(1000), limit(1.e-3), function(fitData), argVec(argSize),
          parVec(params), variance(argSize,std::vector<double>(argSize,0)), tmpVariance(argSize,std::vector<double>(argSize,0))
    {
        for (int i=0;i<argSize;i++)
            argVec[i] = fixed[i];
    }

    void start() {
        int maxCount=0;
        double dev=.001,chi2;
        std::vector< double > test(argSize),input(argSize),diff(argSize);
        rowVal=0;
        for (int j=0; j<argSize; j++)
            if (argVec[j])
                rowVal++;
        std::vector< std::vector< double > >  unitVec(rowVal,std::vector<double>(1,0)), temp(rowVal,std::vector<double>(rowVal,0));
        calcStat(parVec,tmpVariance,input);
        for (int j=0;j <argSize; j++)
            test[j]=parVec[j];
        chi2=chi;
        for (int counter2 = 0; counter2<upperLimit; counter2++)
        {
            if (maxCount==counter)
                dev=0.0;
            for (int j=0; j<rowVal; j++)
            {
                for (int k=0; k<rowVal; k++)
                    variance[j][k]=tmpVariance[j][k];
                variance[j][j]=tmpVariance[j][j]*(1.0+dev);
                for (int k=0; k<rowVal; k++)
                    temp[j][k]=variance[j][k];
                unitVec[j][0]=input[j];
			}
            if(rowVal>0)
                invertMatrix(temp,unitVec);
            extern QString matrixError;
            if(matrixError!="")
                return;
            for (int j=0; j<rowVal; j++)
            {
                for (int k=0; k<rowVal; k++)
                    variance[j][k]=temp[j][k];
                diff[j]=unitVec[j][0];
			}
            if (maxCount==counter)
            {
                sortVar(variance);
                sortVar(tmpVariance);
				return;
			}
            for (int j=0,l=0; l<argSize; l++)
                if (argVec[l])
                    test[l]=parVec[l]+diff[j++];
            calcStat(test,variance,diff);
            if (abs(chi-chi2)<std::max(limit,limit*chi))
                maxCount++;
            if (chi < chi2)
            {
                dev *= 0.1;
                chi2=chi;
                for (int j=0; j<rowVal; j++)
                {
                    for (int k=0; k<rowVal; k++)
                        tmpVariance[j][k]=variance[j][k];
                    input[j]=diff[j];
				}
                for (int l=0; l<argSize; l++)
                    parVec[l]=test[l];
            }
            else
            {
                dev *= 10.0;
                chi=chi2;
			}
        }
        extern QString matrixError;
        matrixError = "Too many iterations!\nRecheck your start parameters.";
	}
    void sortVar(std::vector< std::vector< double > > &variance)
    {
        for(int i=rowVal; i<argSize; i++)
            for(int j=0; j<i+1; j++)
                variance[i][j]=variance[j][i]=0.0;
        int k=rowVal-1;
        for(int j=argSize-1; j>=0; j--)
        {
            if (argVec[j])
            {
                for (int i=0; i<argSize; i++)
                    std::swap(variance[i][k],variance[i][j]);
                for (int i=0; i<argSize; i++)
                    std::swap(variance[k][i],variance[j][i]);
                k--;
            }
        }
    }
    void calcStat(std::vector< double > &parVec, std::vector< std::vector< double > >  &tmpVariance, std::vector< double > &input)
    {
        double value,weight,errVec2,error;
        std::vector< double > dydx(argSize);
        for (int j=0; j<rowVal; j++)
        {
            for (int k=0; k<=j; k++)
                tmpVariance[j][k]=0.0;
            input[j]=0.;
		}
        chi=0.;
        for (int i=0; i<size; i++)
        {
            function(x[i],parVec,value,dydx);
            errVec2=1.0/(errVec[i]*errVec[i]);
            error=y[i]-value;
            for (int j=0, l=0; l<argSize; l++)
            {
                if (argVec[l])
                {
                    weight= dydx[l]*errVec2;
                    for (int k=0, m=0; m<l+1; m++)
                        if (argVec[m]) tmpVariance[j][k++] += weight*dydx[m];
                    input[j++] += error*weight;
				}
			}
            chi += error*error*errVec2;
		}
        for (int j=1; j<rowVal; j++)
            for (int k=0; k<j; k++)
                tmpVariance[k][j]=tmpVariance[j][k];
	}
};
