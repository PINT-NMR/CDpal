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

#include "scaledialog.h"
#include "ui_scaledialog.h"
#include <iostream>

scaleDialog::scaleDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::scaleDialog)
{
    ui->setupUi(this);
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_QuitOnClose, false);
    ui->minEdit->setValidator( new QDoubleValidator(ui->minEdit) );
    ui->minEdit_2->setValidator( new QDoubleValidator(ui->minEdit_2) );
    ui->maxEdit->setValidator( new QDoubleValidator(ui->maxEdit) );
    ui->maxEdit_2->setValidator( new QDoubleValidator(ui->maxEdit_2) );
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acceptEvent()));
    connect(ui->idxBox, SIGNAL(currentIndexChanged(int)), this, SLOT(enable()));
}

scaleDialog::~scaleDialog()
{
    delete ui;    
}
void scaleDialog::enable()
{
    if(ui->idxBox->currentIndex()==1)
    {
        ui->minEdit->setEnabled(true);
        ui->minEdit_2->setEnabled(true);
        ui->maxEdit->setEnabled(true);
        ui->maxEdit_2->setEnabled(true);
        ui->label->setEnabled(true);
        ui->label_2->setEnabled(true);
        ui->label_3->setEnabled(true);
        ui->label_4->setEnabled(true);
    }
    else
    {
        ui->minEdit->setDisabled(true);
        ui->minEdit_2->setDisabled(true);
        ui->maxEdit->setDisabled(true);
        ui->maxEdit_2->setDisabled(true);
        ui->label->setDisabled(true);
        ui->label_2->setDisabled(true);
        ui->label_3->setDisabled(true);
        ui->label_4->setDisabled(true);
    }
}

void scaleDialog::acceptEvent()
{
    extern int scaleIdx;
    bool ok =true;
    if(ui->idxBox->currentIndex()==0)
        scaleIdx=0;
    else
    {
        scaleIdx=1;
        extern double xmin;
        extern double xmax;
        extern double ymin;
        extern double ymax;
        QString x1,x2,y1,y2;
        x1 = ui->minEdit->text();
        x2 = ui->maxEdit->text();
        y1 = ui->minEdit_2->text();
        y2 = ui->maxEdit_2->text();
        for(int i=0; i<x1.length(); i++)
            if(x1[i]==',')
            {
                x1[i]='.';
                break;
            }
        for(int i=0; i<x2.length(); i++)
            if(x2[i]==',')
            {
                x2[i]='.';
                break;
            }
        for(int i=0; i<y1.length(); i++)
            if(y1[i]==',')
            {
                y1[i]='.';
                break;
            }
        for(int i=0; i<y2.length(); i++)
            if(y2[i]==',')
            {
                y2[i]='.';
                break;
            }
        xmin=x1.toDouble();
        ymin=y1.toDouble();
        xmax=x2.toDouble();
        ymax=y2.toDouble();
    }
    if(ok == true)
        accept();
}
