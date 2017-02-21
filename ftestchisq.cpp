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

#include <math.h>
#include <stdlib.h>
#include <iostream>



void ftestchisq(const double chisq1, const double _df1, const double chisq2, const double _df2, double &f, double &pval)
{
// Calculates f statistic and probability (pval) that two fits are 
// equally good. The fits have chisquares of chisq1 and chisq2 and 
// their degrees of freedom (fitted points minus number of fit 
// parameters) are df1, and df2.
// 
// coded by Patrik Lundstrom, 021024

	double betai(double a,double b, double x);

	int df1, df2;


	/* Calculate f-statistic */
	/* --------------------- */
	
	// If the degrees of freedom are the same
	if (chisq1 > chisq2) {
		f = chisq1/chisq2;
		df1 = _df1;
		df2 = _df2;
	}
	else {
		f = chisq2/chisq1;
		df1 = _df2;
		df2 = _df1;
	}

	/* Calculate probability that fits are equally good */
	/* ------------------------------------------------ */
	pval = betai(0.5*df2,0.5*df1,df2/(df2+df1*f));
	
	/* Case where model with more d.o.f. has lower chi2 */
	if (pval > 0.5)
		pval = 1 - pval;
}

double gammln(double xx)

/* computes logarithm of the complete
// gamma function at xx
// TESTED: WORKS FINE!
//
// coded by Patrik Lundstrom, 20 May 2002
*/
{
	double x,y,tmp,ser;
	static double cof[6] = {76.18009172947146, -86.50532032941677,
				24.01409824083091, -1.231739572450155,
				0.1208650973866179e-2, -0.5395239384953e-5};
	int j;

	y=x=xx;
	tmp=x+5.5;
	tmp -= (x+0.5)*log(tmp);
	ser=1.000000000190015;
	for (j=0;j<=5;j++) 
		ser += cof[j]/++y;
	return -tmp+log(2.5066282746310005*ser/x);
}


double betai(double a,double b, double x)
{
// Calculates the incomplete beta function
// 
// coded by Patrik Lundstrom, 021024

	double betacf(double a, double b, double x);
	double gammln(double xx);

	double bt;

	if (x < 0.0 || x > 1.0) 
		{ std::cerr << "betai(): Bad x"; exit(1); }
	if (x == 0.0 || x == 1.0) 
		bt=0.0;
	else
		bt=exp(gammln(a+b)-gammln(a)-gammln(b)+a*log(x)+b*log(1.0-x));
	if (x < (a+1.0)/(a+b+2.0))
		return bt*betacf(a,b,x)/a;
	else
		return 1.0-bt*betacf(b,a,1.0-x)/b;
}

#define MAXIT 100
#define EPS 3.0e-7
#define FPMIN 1.0e-30

double betacf(double a, double b, double x)
{
// Used by betai(). Avaluates continued fraction for
// incomplete beta function
//
// coded by Patrik Lundstrom, 021024

        int m,m2;
        double aa,c,d,del,h,qab,qam,qap;

        qab=a+b;
        qap=a+1.0;
        qam=a-1.0;
        c=1.0;
        d=1.0-qab*x/qap;
        if (fabs(d) < FPMIN) d=FPMIN;
        d=1.0/d;
        h=d;
        for (m=1;m<=MAXIT;m++) {
                m2=2*m;
                aa=m*(b-m)*x/((qam+m2)*(a+m2));
                d=1.0+aa*d;
                if (fabs(d) < FPMIN) d=FPMIN;
                c=1.0+aa/c;
                if (fabs(c) < FPMIN) c=FPMIN;
                d=1.0/d;
                h *= d*c;
                aa = -(a+m)*(qab+m)*x/((a+m2)*(qap+m2));
                d=1.0+aa*d;
                if (fabs(d) < FPMIN) d=FPMIN;
                c=1.0+aa/c;
                if (fabs(c) < FPMIN) c=FPMIN;
                d=1.0/d;
                del=d*c;
                h *= del;
                if (fabs(del-1.0) < EPS) break;
        }
        if (m > MAXIT) { std::cerr << "a or b too big, or MAXIT too small in betacf\n"; exit(1); } 
        return h;
}

#undef MAXIT
#undef EPS
#undef FPMIN


//-----------------------------------------------------
void usage(void)
{
	std::cerr << "Usage:\n";
	std::cerr << "ftestchisq [-in <testfile>] or [-c1 var(1) -c2 var(2) -df1 dof(1) -df2 dof(2)]\n";
	std::cerr << "\t<testfile> should consist of lines with\n";
	std::cerr << "\tthe following parameters:\n";
	std::cerr << "\tColumn 1: Chi2 of 1st model\n";
	std::cerr << "\tColumn 2: Degrees of freedom of 1st model\n";
	std::cerr << "\tColumn 3: Chi2 of 2nd model\n";
	std::cerr << "\tColumn 4: Degrees of freedom of 2nd model\n";
}
