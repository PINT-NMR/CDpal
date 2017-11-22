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

#ifndef MFUNC_H
#define MFUNC_H
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
#include <cstdlib>
#include <QtWidgets>

void mout(QString str);
void mout(QString str, QString comment);
void mout(QString str, QString str2, QString comment);
void mout(QString str, QString str2,QString str3, QString comment);
void mout(QString str, QString str2,QString str3, QString str4, QString comment);
void mout(QString str, QString str2,QString str3, QString str4, QString str5, QString comment);
void mout(std::string str);
void mout(std::string str, std::string comment);
void mout(std::string str, std::string str2, std::string comment);
void mout(std::string str, std::string str2,std::string str3, std::string comment);
void mout(std::string str, std::string str2,std::string str3, std::string str4, std::string comment);
void mout(std::string str, std::string str2,std::string str3, std::string str4, std::string str5, std::string comment);
void mout(QString str, std::string str2);
void mout(std::string str, QString str2);
void mout(QString str, std::string str2, QString str3);
void mout(QString str, std::string str2, std::string str3);
void mout(std::string str, QString str2, std::string str3);
void mout(std::string str, QString str2, QString str3);
void mout(std::vector<std::string> vec);
void mout(std::vector<int> vec);
void mout(std::vector<double> vec);
void mout(std::vector<QString> vec);
void mout(std::vector< std::vector< std::string > > vec);
void mout(std::vector< std::vector< int > > vec);
void mout(std::vector< std::vector< double > > vec);
QString mconvert(std::string str);
std::string mconvert(QString str);
void mout(const char str1, const char str2, const char str3);
std::string mconvert(double d);
std::string mconvert(int i);
int mcountlines(std::string filename);
void mout(double d, double d2, double d3, double d4, double d5, double d6);
void mout(double d, double d2, double d3, double d4, double d5);
void mout(double d, double d2, double d3, double d4);
void mout(double d, double d2, double d3);
void mout(double d, double d2);
void mout(double d);

#endif // MFUNC_H
