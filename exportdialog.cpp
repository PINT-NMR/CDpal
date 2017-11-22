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

#include "exportdialog.h"
#include "ui_exportdialog.h"

exportDialog::exportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::exportDialog),fitExist(false)
{
    ui->setupUi(this);
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_QuitOnClose, false);
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(acceptEvent()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->allButton, SIGNAL(clicked()), this, SLOT(selectAll()));
    connect(ui->noneButton, SIGNAL(clicked()), this, SLOT(selectNone()));
    ui->fitEdit->hide();
    ui->fitLabel->hide();
    ui->fitLabel2->hide();
    setupList();
}

exportDialog::~exportDialog()
{
    delete ui;
}

void exportDialog::setupList()
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
    for(int i=0; i<ui->graphList->count(); i++)
    {
        if(ui->graphList->item(i)->text().length()>4)
        {
            for(int j=0; j<ui->graphList->item(i)->text().length()-4; j++)
            {
                if(ui->graphList->item(i)->text()[j]=='(' && ui->graphList->item(i)->text()[j+1]=='f' && ui->graphList->item(i)->text()[j+2]=='i' && ui->graphList->item(i)->text()[j+3]=='t' && ui->graphList->item(i)->text()[j+4]==':')
                {
                    fitExist = true;
                    break;
                }
            }
        }
        if(fitExist)
            break;
    }
    connect(ui->graphList, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(checkSave()));
}

void exportDialog::selectAll()
{
    for(int i=0; i<ui->graphList->count(); i++)
        ui->graphList->item(i)->setCheckState(Qt::Checked);
    if(fitExist)
    {
        ui->saveBox->setChecked(true);
        ui->saveBox->setEnabled(true);
    }
}
void exportDialog::selectNone()
{
    for(int i=0; i<ui->graphList->count(); i++)
        ui->graphList->item(i)->setCheckState(Qt::Unchecked);
    if(fitExist)
    {
        ui->saveBox->setChecked(false);
        ui->saveBox->setDisabled(true);
    }
}

void exportDialog::acceptEvent()
{
    QString passed="";
    extern QStringList exportList;
    exportList.clear();
    for(int i=0; i<ui->graphList->count(); i++)
    {
        if(ui->graphList->item(i)->checkState())
            exportList << ui->graphList->item(i)->text();
        if(i==ui->graphList->count()-1 && exportList.size()==0)
            passed="Please select at least one dataset to export.";
    }

    if(passed=="")
    {
        extern QString resFileName;
        resFileName="";
        if(ui->saveBox->checkState())
        {
            QString append =ui->fitEdit->text();
            QString illegalChars = "\\/:?\"<>|.";
            for (int m=0; m<append.size(); m++)
            {
                for(int l=0; l<illegalChars.size(); l++)
                    if(illegalChars[l]==append[m])
                        append[m]=' ';
            }
            for (int m=0; m<append.size(); m++)
            {
                if(append[m]!=' ')
                    resFileName+=append[m];
            }
        }
        if(resFileName=="")
            resFileName="CDpal_Results.txt";
        else
            resFileName+=".txt";
        extern bool saveRes;
        if(ui->saveBox->checkState())
            saveRes=true;
        else
            saveRes=false;
        accept();
    }
    else
        QMessageBox::warning(this, "CDpal",passed, QMessageBox::Ok);
}

void exportDialog::checkSave()
{
    bool checkExist=false;
    for(int i=0; i<ui->graphList->count(); i++)
    {
        if(ui->graphList->item(i)->checkState())
        {
            if(ui->graphList->item(i)->text().length()>4)
            {
                for(int j=0; j<ui->graphList->item(i)->text().length()-4; j++)
                {
                    if(ui->graphList->item(i)->text()[j]=='(' && ui->graphList->item(i)->text()[j+1]=='f' && ui->graphList->item(i)->text()[j+2]=='i' && ui->graphList->item(i)->text()[j+3]=='t' && ui->graphList->item(i)->text()[j+4]==':')
                    {
                        checkExist = true;
                        break;
                    }
                }
            }
            if(checkExist)
                break;
        }
    }
    if(checkExist)
    {
        ui->saveBox->setEnabled(true);
        ui->fitEdit->show();
        ui->fitLabel->show();
        ui->fitLabel2->show();
        ui->fitEdit->setText("CDpal_Results");
    }
    else
    {
        ui->fitEdit->hide();
        ui->fitLabel->hide();
        ui->fitLabel2->hide();
        ui->saveBox->setDisabled(true);
        ui->saveBox->setChecked(false);
        ui->fitEdit->setText("");
    }
}
