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

#include <fstream>
#include <cmath>
#include <complex>
#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

#define R 8.314462
#define STEP 0.001

double fitfunccore_two_state(const double x, std::vector< double > &a)
{
// Fits data to the process: N -> U
//

    double T = x + 273.15; // x is melt temperature in oC
    double deltaH = a[0];
    double Tm = a[1] + 273.15; // a[1] is temp in oC
    double thetaN = a[2];
    double thetaU = a[3];
    double slopeN = a[4];
    double slopeU = a[5];
    double deltaCp = a[6];

    double K = exp(deltaH/R*(1./Tm-1./T) + deltaCp/R*((Tm/T-1.)+log(T/Tm)));

    return ((thetaN+slopeN*(x+273.15)) + (thetaU+slopeU*(x+273.15))*K) / (1. + K);
}

//fitfunc_two_state
void function(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda) // temperatur (X), parametrar från fit, CD signalen (Y), partiella derivator map passningsparametrar
{
    std::vector< double > aPlus = a;
    std::vector< double > aMinus = a;

    y = fitfunccore_two_state(x, a);

    for (unsigned int i=0; i< a.size(); i++)
    {
        aPlus[i] *= (1. + STEP);
        aMinus[i] *= (1. - STEP);

        dyda[i] = (fitfunccore_two_state(x, aPlus) - fitfunccore_two_state(x, aMinus)) / (aPlus[i] - aMinus[i]);

        aPlus[i] = a[i];
        aMinus[i] = a[i];
    }
}
// flin

void flin(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda)
{
    // fits data to a linear function
    y = a[0] + a[1]*x;

    dyda[0] = 1;
    dyda[1] = x;
}


double fitfunccore_three_state(const double x, std::vector< double > &a)
{
// Fits data to the process: N -> I -> U
//

    double T = x + 273.15; // x is melt temperature in oC

    // Fitting parameters
    double deltaH_NI = a[0];
    double Tm_NI = a[1] + 273.15; // a[1] is temp in oC
    double thetaN = a[2];
    double thetaU = a[3];
    double slopeN = a[4];
    double slopeU = a[5];
    double deltaCp_NI = a[6];
    double deltaH_IU = a[7];
    double Tm_IU = a[8] + 273.15; // a[1] is temp in oC
    double thetaI = a[9];
    double slopeI = a[10];
    double deltaCp_IU = a[11];



    // Equilibrium constants
    double K_NI = exp(deltaH_NI/R*(1./Tm_NI-1./T) + deltaCp_NI/R*((Tm_NI/T-1.)+log(T/Tm_NI)));
    double K_IU = exp(deltaH_IU/R*(1./Tm_IU-1./T) + deltaCp_IU/R*((Tm_IU/T-1.)+log(T/Tm_IU)));

    // Relative populations
    double p_U = K_NI*K_IU / (1. + K_NI + K_NI*K_IU);
    double p_I = K_NI / (1. + K_NI + K_NI*K_IU);
    double p_N = 1. / (1. + K_NI + K_NI*K_IU);

    return (thetaN+slopeN*(x+273.15))*p_N + (thetaI+slopeI*(x+273.15))*p_I + (thetaU+slopeU*(x+273.15))*p_U;
}


void fitfunc_three_state(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda)
{
    std::vector< double > aPlus = a;
    std::vector< double > aMinus = a;

    y = fitfunccore_three_state(x, a);

    for (unsigned int i=0; i< a.size(); i++) {
        aPlus[i] *= (1. + STEP);
        aMinus[i] *= (1. - STEP);

        dyda[i] = (fitfunccore_three_state(x, aPlus) - fitfunccore_three_state(x, aMinus)) / (aPlus[i] - aMinus[i]);

        aPlus[i] = a[i];
        aMinus[i] = a[i];
    }
}




double fitfunccore_three_state_dimer1(const double x, std::vector< double > &a)
{
// Fits data to the process: N2 -> 2I -> 2U
//

    double T = x + 273.15; // x is melt temperature in oC

    // Fitting parameters
    double deltaH_NI = a[0];
    double Tm_NI = a[1] + 273.15; // a[1] is temp in oC
    double thetaN = a[2];
    double thetaU = a[3];
    double slopeN = a[4];
    double slopeU = a[5];
    double deltaCp_NI = a[6];
    double deltaH_IU = a[7];
    double Tm_IU = a[8] + 273.15; // a[1] is temp in oC
    double thetaI = a[9];
    double slopeI = a[10];
    double deltaCp_IU = a[11];

    // Protein concentration
    double Po = a[12]; // Should be kept fixed as default



    // Equilibrium constants
    double K_NI = exp(deltaH_NI/R*(1./Tm_NI-1./T) + deltaCp_NI/R*((Tm_NI/T-1.)+log(T/Tm_NI)));
    double K_IU = exp(deltaH_IU/R*(1./Tm_IU-1./T) + deltaCp_IU/R*((Tm_IU/T-1.)+log(T/Tm_IU)));

    // Relative populations
    double p_U = 2. / (1. + 1./K_IU + sqrt((1.+1./K_IU)*(1.+1./K_IU) + 8.*Po/(K_NI*K_IU)));
    double p_I = p_U / K_IU;
    double p_N = 2.*p_U*p_U*Po / (K_NI*K_IU*K_IU);

    return (thetaN+slopeN*(x+273.15))*p_N + (thetaI+slopeI*(x+273.15))*p_I + (thetaU+slopeU*(x+273.15))*p_U;
}


void fitfunc_three_state_dimer1(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda)
{
    std::vector< double > aPlus = a;
    std::vector< double > aMinus = a;

    y = fitfunccore_three_state_dimer1(x, a);

    for (unsigned int i=0; i< a.size(); i++) {
        aPlus[i] *= (1. + STEP);
        aMinus[i] *= (1. - STEP);

        dyda[i] = (fitfunccore_three_state_dimer1(x, aPlus) - fitfunccore_three_state_dimer1(x, aMinus)) / (aPlus[i] - aMinus[i]);

        aPlus[i] = a[i];
        aMinus[i] = a[i];
    }
}


double fitfunccore_three_state_dimer2(const double x, std::vector< double > &a)
{
// Fits data to the process: N2 -> I2 -> 2U
//

    double T = x + 273.15; // x is melt temperature in oC

    // Fitting parameters
    double deltaH_NI = a[0];
    double Tm_NI = a[1] + 273.15; // a[1] is temp in oC
    double thetaN = a[2];
    double thetaU = a[3];
    double slopeN = a[4];
    double slopeU = a[5];
    double deltaCp_NI = a[6];
    double deltaH_IU = a[7];
    double Tm_IU = a[8] + 273.15; // a[1] is temp in oC
    double thetaI = a[9];
    double slopeI = a[10];
    double deltaCp_IU = a[11];

    // Protein concentration
    double Po = a[12]; // Keep fixed as default



    // Equilibrium constants
    double K_NI = exp(deltaH_NI/R*(1./Tm_NI-1./T) + deltaCp_NI/R*((Tm_NI/T-1.)+log(T/Tm_NI)));
    double K_IU = exp(deltaH_IU/R*(1./Tm_IU-1./T) + deltaCp_IU/R*((Tm_IU/T-1.)+log(T/Tm_IU)));

    // Relative populations
    double p_U = 2. / (1. + sqrt(1. + 8.*Po*(1.+1./K_NI)/K_IU));
    double p_I = 2.*p_U*p_U*Po/K_IU;
    double p_N = p_I / K_NI;

    return (thetaN+slopeN*(x+273.15))*p_N + (thetaI+slopeI*(x+273.15))*p_I + (thetaU+slopeU*(x+273.15))*p_U;
}


void fitfunc_three_state_dimer2(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda)
{
    std::vector< double > aPlus = a;
    std::vector< double > aMinus = a;

    y = fitfunccore_three_state_dimer2(x, a);

    for (unsigned int i=0; i< a.size(); i++) {
        aPlus[i] *= (1. + STEP);
        aMinus[i] *= (1. - STEP);

        dyda[i] = (fitfunccore_three_state_dimer2(x, aPlus) - fitfunccore_three_state_dimer2(x, aMinus)) / (aPlus[i] - aMinus[i]);

        aPlus[i] = a[i];
        aMinus[i] = a[i];
    }
}

// fCDchemicaldenaturation_CDpal.cpp
//
// Fits CD chemical denaturation data
// to a model where m and Tm
// are the optimized parameters in addition
// to the signal for native and denatured state.
// Denaturant concentration dependence of signal in
// native and denatured states is taken into account.
//
// a[0] = m-value  (rate of denaturation)
// a[1] = Cm (mid point concentration. Same units as x)
// a[2] = thetaN  (intercept for signal for native protein)
// a[3] = thetaU  (intercept forsignal for unfolded protein)
// a[4] = slopeN  (slope for signal for native protein)
// a[5] = slopeU  (slope for signal for unfolded protein)
// a[6] = Temperature (in degrees Celcius) DO NOT OPTIMIZE
//
// There are also three different models involving an
// intermediate state. Then the parameters are:
//
// a[0] = m-value  (rate of denaturation) for N->I
// a[1] = Cm (mid point concentration. Same units as x) for N->I
// a[2] = thetaN  (intercept for signal for native protein)
// a[3] = thetaU  (intercept forsignal for unfolded protein)
// a[4] = slopeN  (slope for signal for native protein)
// a[5] = slopeU  (slope for signal for unfolded protein)
// a[6] = Temperature (in degrees Celcius) DO NOT OPTIMIZE
// a[7] = m-value  (rate of denaturation) for I->U
// a[8] = Cm (mid point concentration. Same units as x) for I->U
// a[9] = thetaI  (intercept forsignal for unfolded protein)
// a[10] = slopeI  (slope for signal for native protein)
//
// The functions named fitfunccore_XXX_chem evaluate
// the function at a certain temperature and the
// ones called fitfunc_XXX_chem also calculate partial
// derivatives with resepct to fitting parameters.
//
// Patrik Lundstrom, 150429

// Two-state denaturation
double fitfunccore_two_state_chem(const double x, std::vector< double > &a)
{
    double m = a[0];          // how much deltaG changes per 1 M denaturant added
    double Cm = a[1];         // denaturant concentration when 50% is denatured
    double thetaN = a[2];
    double thetaU = a[3];
    double slopeN = a[4];
    double slopeU = a[5];
    double T = a[6] + 273.15; // a[6] is sample temperature in degrees Celcius

    double K = exp(-m/(R*T)*(Cm - x));

    return ((thetaN+slopeN*x) + (thetaU+slopeU*x)*K) / (1. + K);
}


void fitfunc_two_state_chem(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda)
{
    std::vector< double > aPlus = a;
    std::vector< double >aMinus = a;

    y = fitfunccore_two_state_chem(x, a);

    for (unsigned int i=0; i< a.size(); i++) {
        aPlus[i] *= (1. + STEP);
        aMinus[i] *= (1. - STEP);

        dyda[i] = (fitfunccore_two_state_chem(x, aPlus) - fitfunccore_two_state_chem(x, aMinus)) / (aPlus[i] - aMinus[i]);

        aPlus[i] = a[i];
        aMinus[i] = a[i];
    }
}
////////////////////////////////////////////////////////////////////////////////



// Three-state denaturation
double fitfunccore_three_state_chem(const double x, std::vector< double > &a)
{
    double mNI = a[0];          // how much deltaG changes per 1 M denaturant added
    double CmNI = a[1];         // denaturant concentration when 50% is denatured
    double thetaN = a[2];
    double thetaU = a[3];
    double slopeN = a[4];
    double slopeU = a[5];
    double T = a[6] + 273.15; // a[6] is sample temperature in degrees Celcius
    double mIU = a[7];          // how much deltaG changes per 1 M denaturant added
    double CmIU = a[8];         // denaturant concentration when 50% is denatured
    double thetaI = a[9];
    double slopeI = a[10];

    // Equilibrium constants
    double K_NI = exp(-mNI/(R*T)*(CmNI - x));
    double K_IU = exp(-mIU/(R*T)*(CmIU - x));

    // Relative populations
    double p_U = K_NI*K_IU / (1. + K_NI + K_NI*K_IU);
    double p_I = K_NI / (1. + K_NI + K_NI*K_IU);
    double p_N = 1. / (1. + K_NI + K_NI*K_IU);

    return (thetaN+slopeN*x)*p_N + (thetaI+slopeI*x)*p_I + (thetaU+slopeU*x)*p_U;
}


void fitfunc_three_state_chem(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda)
{
    std::vector< double > aPlus = a;
    std::vector< double > aMinus = a;

    y = fitfunccore_three_state_chem(x, a);

    for (unsigned int i=0; i< a.size(); i++) {
        aPlus[i] *= (1. + STEP);
        aMinus[i] *= (1. - STEP);

        dyda[i] = (fitfunccore_three_state_chem(x, aPlus) - fitfunccore_three_state_chem(x, aMinus)) / (aPlus[i] - aMinus[i]);

        aPlus[i] = a[i];
        aMinus[i] = a[i];
    }
}
/////////////////////////////////////////////////////////////////////////////////////////



// Denaturation of dimers to the process: N2 -> 2I -> 2U
double fitfunccore_three_state_dimer1_chem(const double x, std::vector< double > &a)
{
    double mNI = a[0];          // how much deltaG changes per 1 M denaturant added
    double CmNI = a[1];         // denaturant concentration when 50% is denatured
    double thetaN = a[2];
    double thetaU = a[3];
    double slopeN = a[4];
    double slopeU = a[5];
    double T = a[6] + 273.15; // a[6] is sample temperature in degrees Celcius
    double mIU = a[7];          // how much deltaG changes per 1 M denaturant added
    double CmIU = a[8];         // denaturant concentration when 50% is denatured
    double thetaI = a[9];
    double slopeI = a[10];
    double Po = a[11]; // Protein concentration, keep fixed as default


    // Equilibrium constants
    double K_NI = exp(-mNI/(R*T)*(CmNI - x));
    double K_IU = exp(-mIU/(R*T)*(CmIU - x));

    // Relative populations
    double p_U = 2. / (1. + 1./K_IU + sqrt(pow((1.+1./K_IU),2) + 8.*Po/(K_NI*pow(K_IU,2))));
    double p_I = p_U / K_IU;
    double p_N = 2.*pow(p_U,2)*Po / (K_NI*pow(K_IU,2));

    return (thetaN+slopeN*x)*p_N + (thetaI+slopeI*x)*p_I + (thetaU+slopeU*x)*p_U;
}


void fitfunc_three_state_dimer1_chem(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda)
{
    // Fits data to the process: N2 -> 2I -> 2U

    std::vector< double > aPlus = a;
    std::vector< double > aMinus = a;

    y = fitfunccore_three_state_dimer1_chem(x, a);

    for (unsigned int i=0; i< a.size(); i++) {
        aPlus[i] *= (1. + STEP);
        aMinus[i] *= (1. - STEP);

        dyda[i] = (fitfunccore_three_state_dimer1_chem(x, aPlus) - fitfunccore_three_state_dimer1_chem(x, aMinus)) / (aPlus[i] - aMinus[i]);

        aPlus[i] = a[i];
        aMinus[i] = a[i];
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////



// Denaturation of dimers to the process: N2 -> I2 -> 2U
double fitfunccore_three_state_dimer2_chem(const double x, std::vector< double > &a)
{
    double mNI = a[0];          // how much deltaG changes per 1 M denaturant added
    double CmNI = a[1];         // denaturant concentration when 50% is denatured
    double thetaN = a[2];
    double thetaU = a[3];
    double slopeN = a[4];
    double slopeU = a[5];
    double T = a[6] + 273.15; // a[6] is sample temperature in degrees Celcius
    double mIU = a[7];          // how much deltaG changes per 1 M denaturant added
    double CmIU = a[8];         // denaturant concentration when 50% is denatured
    double thetaI = a[9];
    double slopeI = a[10];
    double Po = a[11]; // Protein concentration, keep fixed as default

    // Equilibrium constants
    double K_NI = exp(-mNI/(R*T)*(CmNI - x));
    double K_IU = exp(-mIU/(R*T)*(CmIU - x));

    // Relative populations
    double p_U = 2. / (1. + sqrt(1. + 8.*Po*(1.+1./K_NI)/K_IU));
    double p_I = 2.*pow(p_U,2)*Po/K_IU;
    double p_N = p_I / K_NI;


    return (thetaN+slopeN*x)*p_N + (thetaI+slopeI*x)*p_I + (thetaU+slopeU*x)*p_U;
}


void fitfunc_three_state_dimer2_chem(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda)
{
    // Fits data to the process: N2 -> 2I -> 2U
    //
    std::vector< double > aPlus = a;
    std::vector< double > aMinus = a;

    y = fitfunccore_three_state_dimer2_chem(x, a);

    for (unsigned int i=0; i< a.size(); i++) {
        aPlus[i] *= (1. + STEP);
        aMinus[i] *= (1. - STEP);

        dyda[i] = (fitfunccore_three_state_dimer2_chem(x, aPlus) - fitfunccore_three_state_dimer2_chem(x, aMinus)) / (aPlus[i] - aMinus[i]);

        aPlus[i] = a[i];
        aMinus[i] = a[i];
    }
}
///////////////////////////////////////////////////////////////////////////////////////////////////

double fitfunccore(const double x, std::vector< double > &a)
{
    double deltaH = a[0];
    double Tm = a[1];
    double A = a[2];
    double K = exp(deltaH/R*(1./(Tm+273.15) - 1./(x+273.15)));
    double f = K/(1.+K);

    return A*f*(1.-f)*(x+273.15)*(x+273.15);
}


void fitfunc(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda)
{
    std::vector< double > aPlus = a;
    std::vector< double > aMinus = a;

    y = fitfunccore(x, a);

    for (unsigned int i=0; i< a.size(); i++) {
        aPlus[i] *= (1. + STEP);
        aMinus[i] *= (1. - STEP);

        dyda[i] = (fitfunccore(x, aPlus) - fitfunccore(x, aMinus)) / (aPlus[i] - aMinus[i]);

        aPlus[i] = a[i];
        aMinus[i] = a[i];
    }
}


