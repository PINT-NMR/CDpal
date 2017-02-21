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

#ifndef GLOBALS_H
#define GLOBALS_H
#include "qcustomplot.h"
namespace Ui
{
    extern int activeGraph;
    extern QString activeIndex;
    extern int degree;
    extern bool drawLine;
    extern QStringList exportList;
    extern int faucetInt;
    extern QPen faucetPen;
    extern int faucetShape;
    extern std::vector < std::vector <QString> > fitParams;
    extern bool fitRes;
    extern QString matrixError;
    extern int highlightGraph;
    extern int index;
    extern QStringList itemLabels;
    extern std::string resultStr;
    extern std::vector< std::vector< std::string> > resultStrVec;
    extern int scaleIdx;
    extern double xmax;
    extern double xmin;
    extern std::vector< std::string > xplotfit;
    extern double ymax;
    extern double ymin;
    extern std::vector< std::string > yplotfit;
    extern bool titleChanged;
    extern QString dirString;
    extern QString titleName;
    extern std::vector< std::string> rV;
    extern std::vector< std::vector< std::string> > rV2;
    extern bool saveRes;
    extern QString resFileName;
    extern QString sPattern;
    extern int sPatternType;
    extern int sskipR;
    extern int sH;
    extern int sC;
    extern int sT;
    extern int mode;
    extern QVector<bool> isFitVec;
    extern QVector<QPen> penVec;
    extern QVector<QCPScatterStyle> ornamentVec;
    extern QVector<QString> styleVec;
    extern QString dispError;
    extern QStringList files;
    extern bool customName;
    extern QString currentName;
    extern QStringList graphNames;
    extern std::vector< std::vector<std::vector<std::string> > >storedData;
    extern double minXG;
    extern double maxXG;
    extern QStringList takenNames;
}
#endif // GLOBALS_H
