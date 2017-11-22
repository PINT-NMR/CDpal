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

#include "mfunc.h"

//<QString>
void mout(const char str1, const char str2, const char str3)
{
    std::cerr<<str1<<str2<<str3<<"fasd";
}
void mout(QString str)
{
    std::cerr<<qPrintable(str)<<"\n";
}
void mout(QString str, QString comment)
{
    std::cerr<<qPrintable(str)<<" "<<qPrintable(comment)<<"\n";
}
void mout(QString str, QString str2, QString comment)
{
    std::cerr<<qPrintable(str)<<" "<<qPrintable(str2)<<" "<<qPrintable(comment)<<"\n";
}
void mout(QString str, QString str2,QString str3, QString comment)
{
    std::cerr<<qPrintable(str)<<" "<<qPrintable(str2)<<" "<<qPrintable(str3)<<" "<<qPrintable(comment)<<"\n";
}
void mout(QString str, QString str2,QString str3, QString str4, QString comment)
{
    std::cerr<<qPrintable(str)<<" "<<qPrintable(str2)<<" "<<qPrintable(str3)<<" "<<qPrintable(str4)<<" "<<qPrintable(comment)<<"\n";
}
void mout(QString str, QString str2,QString str3, QString str4, QString str5, QString comment)
{
    std::cerr<<qPrintable(str)<<" "<<qPrintable(str2)<<" "<<qPrintable(str3)<<" "<<qPrintable(str4)<<" "<<qPrintable(str5)<<" "<<qPrintable(comment)<<"\n";
}
//</QString>
//<std::string>
void mout(std::string str)
{
    std::cerr<<str<<"\n";
}
void mout(std::string str, std::string comment)
{
    std::cerr<<str<<" "<<comment<<"\n";
}
void mout(std::string str, std::string str2, std::string comment)
{
    std::cerr<<str<<" "<<str2<<" "<<comment<<"\n";
}
void mout(std::string str, std::string str2,std::string str3, std::string comment)
{
    std::cerr<<str<<" "<<str2<<" "<<str3<<" "<<comment<<"\n";
}
void mout(std::string str, std::string str2,std::string str3, std::string str4, std::string comment)
{
    std::cerr<<str<<" "<<str2<<" "<<str3<<" "<<str4<<" "<<comment<<"\n";
}
void mout(std::string str, std::string str2,std::string str3, std::string str4, std::string str5, std::string comment)
{
    std::cerr<<str<<" "<<str2<<" "<<str3<<" "<<str4<<" "<<str5<<" "<<comment<<"\n";
}
//</std::string>
//<Mixed std::string && QString>
void mout(QString str, std::string str2)
{
    std::cerr<<qPrintable(str)<<" "<<str2<<"\n";
}
void mout(std::string str, QString str2)
{
    std::cerr<<str<<" "<<qPrintable(str2)<<"\n";
}
void mout(QString str, std::string str2, QString str3)
{
    std::cerr<<qPrintable(str)<<" "<<str2<<" "<<qPrintable(str3)<<"\n";
}
void mout(QString str, std::string str2, std::string str3)
{
    std::cerr<<qPrintable(str)<<" "<<str2<<" "<<str3<<"\n";
}
void mout(std::string str, QString str2, std::string str3)
{
    std::cerr<<str<<" "<<qPrintable(str2)<<" "<<str3<<"\n";
}
void mout(std::string str, QString str2, QString str3)
{
    std::cerr<<str<<" "<<qPrintable(str2)<<" "<<qPrintable(str3)<<"\n";
}
//</Mixed std::string && QString>
//<double>
void mout(double d)
{
    mout(mconvert(d));
}
void mout(double d, double d2)
{
    mout(mconvert(d), mconvert(d2));
}
void mout(double d, double d2, double d3)
{
    mout(mconvert(d), mconvert(d2), mconvert(d3));
}
void mout(double d, double d2, double d3, double d4)
{
    mout(mconvert(d), mconvert(d2), mconvert(d3), mconvert(d4));
}
void mout(double d, double d2, double d3, double d4, double d5)
{
    mout(mconvert(d), mconvert(d2), mconvert(d3), mconvert(d4), mconvert(d5));
}
void mout(double d, double d2, double d3, double d4, double d5, double d6)
{
    mout(mconvert(d), mconvert(d2), mconvert(d3), mconvert(d4), mconvert(d5), mconvert(d6));
}
//</double>
//<std::vector>
void mout(std::vector<std::string> vec)
{
    for (std::vector<std::string>::size_type i = 0; i < vec.size(); i++)
        std::cerr<<"Index ["<<i <<"] contains: "<<vec[i]<<"\n";
}
void mout(std::vector<int> vec)
{
    for (std::vector<int>::size_type i = 0; i < vec.size(); i++)
        std::cerr<<"Index ["<<i <<"] contains: "<<vec[i]<<"\n";
}
void mout(std::vector<double> vec)
{
    for (std::vector<double>::size_type i = 0; i < vec.size(); i++)
        std::cerr<<"Index ["<<i <<"] contains: "<<vec[i]<<"\n";
}
void mout(std::vector<QString> vec)
{
    for (std::vector<QString>::size_type i = 0; i < vec.size(); i++)
        std::cerr<<"Index ["<<i <<"] contains: "<<qPrintable(vec[i])<<"\n";
}
void mout(std::vector< std::vector< std::string > > vec)
{
    for (std::vector<std::vector<std::string> >::size_type i = 0; i < vec.size(); i++)
        for (std::vector<std::string>::size_type j = 0; j < vec[i].size(); j++)
        std::cerr<<"Index ["<<i<<"]["<<j<<"] contains: "<<vec[i][j]<<"\n";
}
void mout(std::vector< std::vector< int > > vec)
{
    for (std::vector<std::vector<int> >::size_type i = 0; i < vec.size(); i++)
        for (std::vector<int>::size_type j = 0; j < vec[i].size(); j++)
        std::cerr<<"Index ["<<i<<"]["<<j<<"] contains: "<<vec[i][j]<<"\n";
}
void mout(std::vector< std::vector< double > > vec)
{
    for (std::vector<std::vector<double> >::size_type i = 0; i < vec.size(); i++)
        for (std::vector<double>::size_type j = 0; j < vec[i].size(); j++)
        std::cerr<<"Index ["<<i<<"]["<<j<<"] contains: "<<vec[i][j]<<"\n";
}
//</std::vector>
//<convert>
QString mconvert(std::string str)
{
    return QString::fromUtf8(str.c_str());
}
std::string mconvert(QString str)
{
    return str.toUtf8().data();
}
std::string mconvert(int i)
{
    std::stringstream conv;
    conv << i;
    return conv.str();
}
std::string mconvert(double d)
{
    std::stringstream conv;
    conv << d;
    return conv.str();
}
//</convert>
//<file>
int mcountlines(std::string filename)
{
    std::ifstream file;
    int i=0;
    file.open(filename.c_str(), std::ios::in);
    std::string line;
    if(file.is_open())
    {
        while(getline(file, line))
            i++;
        file.clear();
        file.close();
    }
    i--;
    return i;
}
//</file>
