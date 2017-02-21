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

#ifndef FTEST_H
#define FTEST_H

#include <QDialog>
#include "QRect"
#include "QDesktopWidget"
#include "QMessageBox"
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "mfunc.h"

namespace Ui {
class ftest;
}

class ftest : public QDialog
{
    Q_OBJECT

public:
    explicit ftest(QWidget *parent = 0);
    ~ftest();

private:
    Ui::ftest *ui;
    bool swapped;

public slots:
    void setupList();
    void calculate();
    void ftestchisq(const double chisq1, const double _df1, const double chisq2, const double _df2, double &f, double &pval);
    double gammln(double xx);
    double betai(double a,double b, double x);
    double betacf(double a, double b, double x);
};

#endif // FTEST_H
