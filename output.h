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

#include "cstdlib"
#include "iostream"
#include "globals.h"

#define NO_PLOTSTEP 1000
using namespace std;

struct Output 
{
    std::vector< double > x, y, err, parVec;
    void (*function)(const double, std::vector< double > &, double &, std::vector< double > &);
    std::vector< double > jackerr;
    std::vector< std::vector< double > > variance;
    int size;
    int parSize;
    int DoF;
    double chi;
    char *plotfile;
    char *plotfileFit;
    std::string deltaH, Tm, ddeltaH, dTm;

    Output() {}

    Output(std::vector< double > &xVec, std::vector< double > &yVec, std::vector< double > &error, std::vector< double > &params,
       void (*fitData)(const double, std::vector< double > &, double &, std::vector< double > &), std::vector< double > &jjackerr,
       std::vector< std::vector< double > > &variance2, double chi2, int dof, char *pplotfile, char *pplotfileFit) :
          x(xVec), y(yVec), err(error), parVec(params), function(fitData),jackerr(jjackerr),
          variance(variance2), size(x.size()), parSize(parVec.size()),
          DoF(dof), chi(chi2), plotfile(pplotfile), plotfileFit(pplotfileFit) {  }

    void print(bool fjack=false) {
        extern std::string resultStr;
        extern std::vector< std::string> rV;
        rV.clear();
        extern bool fitRes;
        if(fitRes)
        {
            std::stringstream ss, ss2;
            std::string str, str2;
            ss.width(7);
            ss.precision(7);
            ss << parVec[0];
            ss >> str;
            ss2 << parVec[1];
            ss2 >> str2;
            resultStr = str + " " + str2;
            return;
        }
        resultStr="Number of points = ";
        std::string str, str2, str3;
        std::stringstream ss, ss2, ss3;
        ss << size;
        ss >> str;
        rV.push_back(str);
        resultStr += str;
        resultStr +="<br>Degrees of freedom = ";
        ss2 << DoF;
        ss2 >> str2;
        rV.push_back(str2);
        resultStr += str2;
        resultStr += "<br>Sum of residuals = ";
        ss3 << chi;
        ss3 >> str3;
        rV.push_back(str3);
        resultStr += str3;
        resultStr += "<br><br>";
        printLine(-1,fjack);
        for (int i = 0; i < parSize; i++)
        {
                printLine(i,fjack);
        }
        //Print deltaS, calculated from deltaH/Tm, also with Error propagation
        resultStr+="<FONT COLOR='#0101DF'>&Delta;S<sub> </sub></FONT>";
        std::stringstream ss4;
        ss4.width(7);
        ss4.precision(7);
        std::string VAL;
        if(atof(Tm.c_str())>0)
        {
            ss4 << atof(deltaH.c_str())/atof(Tm.c_str());
            ss4 >> VAL;
        }
        else
            VAL="N/A";
        int c1=0;
        if(VAL[0]!='-')
        {
            resultStr += "&nbsp;";
            c1++;
        }
        rV.push_back(VAL);
        resultStr += VAL;
        for(int i= VAL.length(); i<=12-c1; i++)
            resultStr += "&nbsp;";
        resultStr+="&nbsp;&nbsp;";
        std::stringstream ss5;
        ss5.width(7);
        ss5.precision(7);
        if(atof(Tm.c_str())>0)
        {
            double exp1, exp2;
            exp1 = atof(ddeltaH.c_str())/atof(Tm.c_str());
            exp2 = atof(dTm.c_str())*atof(deltaH.c_str())/(atof(Tm.c_str())*atof(Tm.c_str()));
            exp1 *= exp1;
            exp2 *= exp2;
            ss5 << sqrt(exp1 + exp2);
            ss5 >> VAL;
        }
        else
            VAL = "N/A";
        if(VAL[0]!='-')
            resultStr+="&nbsp;";
        rV.push_back(VAL);
        resultStr+=VAL;
        resultStr+="<br>";

	}


    void plot(bool fplot=true, bool fplotFit=true)
	{
        std::vector< double > dydx(parSize);
        double yplot;
        double step;


		if (fplot)
        {
            {
                const int M=7,NSTACK=64;
                    int i,ir,j,k,jstack=-1,l=0,n=x.size();

                    double a;
                    double b;
                    double c;
                    std::vector< int > istack(NSTACK);
                    ir=n-1;
                    for (;;) {
                        if (ir-l < M) {
                            for (j=l+1;j<=ir;j++) {
                                a=x[j];
                                b=y[j];
                                c=err[j];
                                for (i=j-1;i>=l;i--) {
                                    if (x[i] <= a) break;
                                    x[i+1]=x[i];
                                    y[i+1]=y[i];
                                    err[i+1]=err[i];
                                }
                                x[i+1]=a;
                                y[i+1]=b;
                                err[i+1]=c;
                            }
                            if (jstack < 0) break;
                            ir=istack[jstack--];
                            l=istack[jstack--];
                        } else {
                            k=(l+ir) >> 1;
                            std::swap(x[k],x[l+1]);
                            std::swap(y[k],y[l+1]);
                            std::swap(err[k],err[l+1]);
                            if (x[l] > x[ir]) {
                                std::swap(x[l],x[ir]);
                                std::swap(y[l],y[ir]);
                                std::swap(err[l],err[ir]);
                            }
                            if (x[l+1] > x[ir]) {
                                std::swap(x[l+1],x[ir]);
                                std::swap(y[l+1],y[ir]);
                                std::swap(err[l+1],err[ir]);
                            }
                            if (x[l] > x[l+1]) {
                                std::swap(x[l],x[l+1]);
                                std::swap(y[l],y[l+1]);
                                std::swap(err[l],err[l+1]);
                            }
                            i=l+1;
                            j=ir;
                            a=x[l+1];
                            b=y[l+1];
                            c=err[l+1];
                            for (;;) {
                                do i++; while (x[i] < a);
                                do j--; while (x[j] > a);
                                if (j < i) break;
                                std::swap(x[i],x[j]);
                                std::swap(y[i],y[j]);
                                std::swap(err[i],err[j]);
                            }
                            x[l+1]=x[j];
                            x[j]=a;
                            y[l+1]=y[j];
                            y[j]=b;
                            err[l+1]=err[j];
                            err[j]=c;
                            jstack += 2;
                            if (jstack >= NSTACK) throw("NSTACK too small in sort2.");
                            if (ir-i+1 >= j-l) {
                                istack[jstack]=ir;
                                istack[jstack-1]=i;
                                ir=j-1;
                            } else {
                                istack[jstack]=j-1;
                                istack[jstack-1]=l;
                                l=i;
                            }
                        }
                    }
            }
            extern std::vector< std::string > xplotfit, yplotfit;
            xplotfit.clear();
            yplotfit.clear();

            for (unsigned int i=0; i<static_cast<unsigned int>(x.size()); i++)
            {
                function(x[i], parVec, yplot, dydx);
                std::stringstream ss,ss2;
                std::string str, str2;
                ss << x[i];
                ss >> str;
                xplotfit.push_back(str);
                ss2 << yplot;
                ss2 >> str2;
                yplotfit.push_back(str2);
			}
            //myFile.close();
	    }
		if (fplotFit)
        {
            {
                const int M=7,NSTACK=64;
                    int i,ir,j,k,jstack=-1,l=0,n=x.size();

                    double a;
                    double b;
                    double c;
                    std::vector< int > istack(NSTACK);
                    ir=n-1;
                    for (;;) {
                        if (ir-l < M) {
                            for (j=l+1;j<=ir;j++) {
                                a=x[j];
                                b=y[j];
                                c=err[j];
                                for (i=j-1;i>=l;i--) {
                                    if (x[i] <= a) break;
                                    x[i+1]=x[i];
                                    y[i+1]=y[i];
                                    err[i+1]=err[i];
                                }
                                x[i+1]=a;
                                y[i+1]=b;
                                err[i+1]=c;
                            }
                            if (jstack < 0) break;
                            ir=istack[jstack--];
                            l=istack[jstack--];
                        } else {
                            k=(l+ir) >> 1;
                            std::swap(x[k],x[l+1]);
                            std::swap(y[k],y[l+1]);
                            std::swap(err[k],err[l+1]);
                            if (x[l] > x[ir]) {
                                std::swap(x[l],x[ir]);
                                std::swap(y[l],y[ir]);
                                std::swap(err[l],err[ir]);
                            }
                            if (x[l+1] > x[ir]) {
                                std::swap(x[l+1],x[ir]);
                                std::swap(y[l+1],y[ir]);
                                std::swap(err[l+1],err[ir]);
                            }
                            if (x[l] > x[l+1]) {
                                std::swap(x[l],x[l+1]);
                                std::swap(y[l],y[l+1]);
                                std::swap(err[l],err[l+1]);
                            }
                            i=l+1;
                            j=ir;
                            a=x[l+1];
                            b=y[l+1];
                            c=err[l+1];
                            for (;;) {
                                do i++; while (x[i] < a);
                                do j--; while (x[j] > a);
                                if (j < i) break;
                                std::swap(x[i],x[j]);
                                std::swap(y[i],y[j]);
                                std::swap(err[i],err[j]);
                            }
                            x[l+1]=x[j];
                            x[j]=a;
                            y[l+1]=y[j];
                            y[j]=b;
                            err[l+1]=err[j];
                            err[j]=c;
                            jstack += 2;
                            if (jstack >= NSTACK) throw("NSTACK too small in sort2.");
                            if (ir-i+1 >= j-l) {
                                istack[jstack]=ir;
                                istack[jstack-1]=i;
                                ir=j-1;
                            } else {
                                istack[jstack]=j-1;
                                istack[jstack-1]=l;
                                l=i;
                            }
                        }
                    }
            }
            extern std::vector< std::string > xplotfit, yplotfit;
            xplotfit.clear();
            yplotfit.clear();

            step = (x[x.size()-1]-x[0])/(double)NO_PLOTSTEP;
	        for (int i=0; i<=NO_PLOTSTEP; i++) {
                function(x[0]+i*step, parVec, yplot, dydx);
                std::stringstream ss,ss2;
                std::string str, str2;
                ss << x[0]+i*step;
                ss >> str;
                xplotfit.push_back(str);
                ss2 << yplot;
                ss2 >> str2;
                yplotfit.push_back(str2);
			}
	    }
	}
	private:
    double showDecimals(const double& x, const int& numDecimals) {
        int y=x;
        double z=x-y;
        double m=pow(10,numDecimals);
        double q=z*m;
        double r=round(q);

        return static_cast<double>(y)+(1.0/m)*r;
    }
    void printLine(int index, bool fjack)
    {
        extern std::string resultStr;
        extern std::vector< std::string> rV;
        std::stringstream ss,ss4;
        std::string str,str4;
        if (index > -1)
        {
            if(index==0)
                resultStr+="<FONT COLOR='#FF0000'>&Delta;H<sub> </sub></FONT>";
            else if(index==1)
                resultStr+="<FONT COLOR='#00FF00'>T<sub>m</sub>&nbsp;</FONT>";
            else if(index==2)
                resultStr+="<FONT COLOR='#0000FF'>I<sub>N</sub>&nbsp;</FONT>";
            else if(index==3)
                resultStr+="<FONT COLOR='#F000F0'>I<sub>D</sub>&nbsp;</FONT>";
            else if(index==4)
                resultStr+="<FONT COLOR='#00F0F0'>k<sub>N</sub>&nbsp;</FONT>";
            else if(index==5)
                resultStr+="<FONT COLOR='#330000'>k<sub>D</sub>&nbsp;</FONT>";
            else if(index==6)
                resultStr+="<FONT COLOR='#FF0000'>&Delta;Cp<sub> </sub></FONT>";
            else if(index==7)
                resultStr+="<FONT COLOR='#00FF00'>&Delta;H<sub>2</sub></FONT>";
            else if(index==8)
                resultStr+="<FONT COLOR='#0000FF'>T<sub>m</sub>2</FONT>";
            else if(index==9)
                resultStr+="<FONT COLOR='#F000F0'>I<sub>I</sub>&nbsp;</FONT>";
            else if(index==10)
                resultStr+="<FONT COLOR='#00F0F0'>k<sub>I</sub>&nbsp;</FONT>";
            else if(index==11)
                resultStr+="<FONT COLOR='#330000'>&Delta;Cp<sub>2</sub></FONT>";
            else if(index==12)
                resultStr+="<FONT COLOR='#FF0000'>P<sub>0</sub>&nbsp;</FONT>";

            ss.width(7);
            ss.precision(7);
            if(index==0 || index==7)
                ss << parVec[index]/1000.0;
            else if(index==12)
                ss << parVec[index]*1000000.0;
            else
                ss << parVec[index];
            ss >> str;
            int c1=0;
            if(str[0]!='-' && index!=6 && index!=11)
            {
                resultStr+="&nbsp;";
                c1++;
            }
            else if(index==11 || index==6)
            {
                c1++;
            }
            rV.push_back(str);
            resultStr += str;
            if(index==0)
                deltaH=str;
            else if(index==1)
                Tm=str;
            for(int i= str.length(); i<=12-c1; i++)
                resultStr += "&nbsp;";
        }
        else 
        {
            resultStr += "&nbsp;&nbsp;&nbsp;<sub> </sub>Fitted&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;";
        }
        if (fjack) {
             if (index > -1)
             {
                 resultStr+="&nbsp;&nbsp;";
                 ss4.width(7);
                 ss4.precision(7);
                 if(index==0 || index==7)
                     ss4 << jackerr[index]/1000.0;
                 else if(index==12)
                     ss4 << jackerr[index]*1000000.0;
                 else
                     ss4 << jackerr[index];
                 ss4 >> str4;
                 if(index==0)
                     ddeltaH = str4;
                 else if(index==1)
                     dTm = str4;
                 if(str4[0]!='-')
                     resultStr+="&nbsp;";
                 rV.push_back(str4);
                 resultStr += str4;
             }
			 else 
             {
                 resultStr += "Jackknife error";
             }
		}
        resultStr += "<br>";
	}
};

#undef NO_PLOTSTEP
