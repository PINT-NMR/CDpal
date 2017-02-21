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

#include "globals.h"
#include "algorithm"

using namespace std;

void invertMatrix(std::vector< std::vector< double > >  &temp, std::vector< std::vector< double > >  &unitVec)
{
    double d1,d2,d3;
    int column=0,row=0,n=temp.size(),m=unitVec[0].size();
    std::vector< int > Col(n),Row(n),Pivot(n);
    for (int i=0; i<n; i++)
        Pivot[i]=0;
    for (int i=0; i<n; i++)
    {
        d1=0.0;
        for (int j=0; j<n; j++)
            if (Pivot[j] != 1)
                for (int k=0; k<n; k++)
                {
                    if (Pivot[k] == 0)
                    {
                        if (abs(temp[j][k])>= d1)
                        {
                            d1=abs(temp[j][k]);
                            row=j;
                            column=k;
						}
					}
				}
        Pivot[column]+=1;
        if (row != column)
        {
            for (int k=0; k<n; k++)
                std::swap(temp[row][k],temp[column][k]);
            for (int k=0; k<m; k++)
                std::swap(unitVec[row][k],unitVec[column][k]);
		}
        Row[i]=row;
        Col[i]=column;
        if (temp[column][column] == 0.0)
        {
            extern QString matrixError;
            matrixError = "Singular matrix, recheck your starting parameters.";
            return;
        }
        d3=1.0/temp[column][column];
        temp[column][column]=1.0;
        for (int k=0; k<n; k++)
            temp[column][k] *= d3;
        for (int k=0; k<m; k++)
            unitVec[column][k] *= d3;
        for (int k=0; k<n; k++)
            if (k != column)
            {
                d2=temp[k][column];
                temp[k][column]=0.0;
                for (int l=0; l<n; l++)
                    temp[k][l] -= temp[column][l]*d2;
                for (int l=0; l<m; l++)
                    unitVec[k][l] -= unitVec[column][l]*d2;
			}
	}
    for (int k=n-1; k>=0; k--)
    {
        if (Row[k] != Col[k])
            for (int l=0; l<n; l++)
                std::swap(temp[l][Row[k]],temp[l][Col[k]]);
	}
}
