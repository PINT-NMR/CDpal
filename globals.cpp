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

#include "globals.h"
int faucetInt;
QPen faucetPen;
int faucetShape;
int activeGraph=-1;
int highlightGraph=-1;
int scaleIdx=0;
double xmin=-1;
double xmax=1;
double ymin=-1;
double ymax=1;
int degree = 3;
std::vector< std::string > xplotfit;
std::vector< std::string > yplotfit;
std::string resultStr;
bool drawLine =false;
QStringList itemLabels;
QString activeIndex="";
std::vector< std::vector< std::string> > resultStrVec;
std::vector < std::vector <QString> > fitParams;
QString matrixError="";
bool fitRes=false;
QStringList exportList;
bool titleChanged=false;
QString dirString="";
QString titleName="Double click to change title";
std::vector< std::vector< std::string> > rV2;
std::vector< std::string> rV;
bool saveRes;
//MODEL 1: 0= NumberOfPoints, 1= DoF, 2= SoR, 3= dH, 4=dHerr,
//5=Tm, 6=Tmerr, 7=mN, 8=mNerr, 9=mD, 10=mDerr, 11=KN, 12=KNerr,
//13=KD, 14=KDerr, 15=dCP, 16=dCperr, 17=dH2, 18=dH2err, 19=Tm2,
//20=Tm2err, 21=mI, 22=mIerr, 23=Ki, 24=Kierr, 25=dCp2, 26=dCp2err
//27=prot, 28=proterr, 29=dS, 30=dSerr
QString resFileName="";
QString sPattern="";
int sPatternType;
int sskipR;
int sH;
int sC;
int sT;
int mode=0;
QVector<bool> isFitVec;
QVector<QPen> penVec;
QVector<QCPScatterStyle> ornamentVec;
QVector<QString> styleVec;
QString dispError;
QStringList files;
bool customName;
QString currentName;
QStringList graphNames;
std::vector< std::vector<std::vector<std::string> > >storedData;
double minXG=9999.9;
double maxXG=-9999.9;
QStringList takenNames;
