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

#include "ftest.h"
#include "ui_ftest.h"

ftest::ftest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ftest)
{
    ui->setupUi(this);
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_QuitOnClose, false);
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->calcButton, SIGNAL(clicked()), this, SLOT(calculate()));
    setupList();
}

ftest::~ftest()
{
    delete ui;
}

void ftest::setupList()
{
    extern QStringList itemLabels;
    QStringListIterator it(itemLabels);
    int i=0;
    while(it.hasNext())
    {
        QListWidgetItem *listItem = new QListWidgetItem(it.next(), ui->graphList);
        listItem->setCheckState(Qt::Unchecked);
        ui->graphList->addItem(listItem);
        i++;
    }
}

void ftest::calculate()
{
    QString errMessage = "", firstSet="", trueFirst="", trueSecond="";
    int counter=0, correctCount=0;
    for(int i=0; i<ui->graphList->count(); i++)
    {
        if(ui->graphList->item(i)->checkState())
        {
            counter++;
            if(ui->graphList->item(i)->text().length()>4)
                for(int j=0; j<ui->graphList->item(i)->text().length()-4; j++)
                {
                    if(ui->graphList->item(i)->text()[j]=='(' && ui->graphList->item(i)->text()[j+1]=='f' && ui->graphList->item(i)->text()[j+2]=='i' && ui->graphList->item(i)->text()[j+3]=='t' && ui->graphList->item(i)->text()[j+4]==':')
                    {
                        correctCount++;
                        if(correctCount==1)
                        {
                            firstSet = ui->graphList->item(i)->text().mid(0,j);
                            trueFirst = ui->graphList->item(i)->text();
                        }
                        else
                        {
                            if(firstSet!=ui->graphList->item(i)->text().mid(0,j))
                                errMessage = "The submitted fitted datasets belong to different experimental datasets.\nPlease submit two fitted datasets, belonging to the same experimental dataset, to perform an f-test.";
                            else
                                trueSecond = ui->graphList->item(i)->text();
                        }
                        break;
                    }
                }
        }
    }
    if(counter<2)
        errMessage = "Too few datasets submitted.\nPlease submit two fitted datasets, belonging to the same experimental dataset, to perform an f-test.";
    else if(counter>2)
        errMessage = "Too many datasets submitted.\nPlease submit two fitted datasets, belonging to the same experimental dataset, to perform an f-test.";
    else if(correctCount!=2)
        errMessage = "Cannot perform an f-test on experimental data.\nPlease submit two fitted datasets, belonging to the same experimental dataset, to perform an f-test.";

    if(errMessage!="") //Error
        QMessageBox::warning(this, "CDpal",errMessage, QMessageBox::Ok);
    else //Calculate
    {
        extern std::vector< std::vector< std::string> > resultStrVec;
        double pval = 0.00, f = 0.00;
        double chisq1=0.00, _df1=0.00, chisq2=0.00, _df2=0.00;
        for(unsigned int k=0; k<resultStrVec.size(); k++)
        {
            if(mconvert(resultStrVec[k][1])==trueFirst || mconvert(resultStrVec[k][1])==trueSecond)
            {
                bool first;
                if(mconvert(resultStrVec[k][1])==trueFirst)
                    first=true;
                else
                    first=false;
                std::string line = resultStrVec[k][0];
                std::istringstream iss(line);
                std::string sub;
                int cC=0;
                while(iss>>sub)
                {
                    cC++;
                    if(cC==9) //DoF
                    {
                        for(unsigned int i=0; i<sub.length(); i++)
                            if(sub[i]=='<')
                            {
                                if(first)
                                    _df1 = atof(sub.substr(0,i).c_str());
                                else
                                    _df2 = atof(sub.substr(0,i).c_str());
                                break;
                            }
                    }
                    else if(cC==13) //Chisq
                    {
                        for(unsigned int i=0; i<sub.length(); i++)
                            if(sub[i]=='<')
                            {
                                if(first)
                                    chisq1 = atof(sub.substr(0,i).c_str());
                                else
                                    chisq2 = atof(sub.substr(0,i).c_str());
                                break;
                            }
                        break;
                    }
                }
            }
        }
        ftestchisq(chisq1, _df1, chisq2, _df2, f, pval);
        QString testing = "H<sub>0</sub>: ";
        if(swapped)
            testing+=trueSecond;
        else
            testing+=trueFirst;
        testing+=" is the better fit.";
        ui->testingLabel->setText(testing);
        testing = "H<sub>1</sub>: ";
        if(swapped)
            testing+=trueFirst;
        else
            testing+=trueSecond;
        testing+=" is the better fit.";
        ui->testingLabel_2->setText(testing);
        ui->pvalueLabel->setText(QString::number(pval));
        QString rej = "H<sub>0</sub> can be rejected to the significance level of ";
        rej += QString::number(pval*100.0);
        rej +="%.";
        ui->nullHypLabel->setText(rej);
    }
}

void ftest::ftestchisq(const double chisq1, const double _df1, const double chisq2, const double _df2, double &f, double &pval)
{
// Calculates f statistic and probability (pval) that two fits are
// equally good. The fits have chisquares of chisq1 and chisq2 and
// their degrees of freedom (fitted points minus number of fit
// parameters) are df1, and df2.
    double betai(double a,double b, double x);

    int df1, df2;
    if (chisq1 > chisq2)
    {
        swapped = false;
        f = chisq1/chisq2;
        df1 = _df1;
        df2 = _df2;
    }
    else
    {
        swapped = true;
        f = chisq2/chisq1;
        df1 = _df2;
        df2 = _df1;
    }
    pval = betai(0.5*df2,0.5*df1,df2/(df2+df1*f));
    if (pval > 0.5)
        pval = 1 - pval;
}

double ftest::gammln(double xx)
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

double ftest::betai(double a,double b, double x)
{
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
double ftest::betacf(double a, double b, double x)
{
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
