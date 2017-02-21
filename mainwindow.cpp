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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    extern int mode;
    ui->denaturationBox->setCurrentIndex(mode);
#ifdef Q_OS_LINUX
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
    ui->label_4->setFont(QFont( "Arial", 9));
    ui->updateLink->setFont(QFont( "Arial", 9));
    ui->denaturationBox->setFont(QFont( "Arial", 8));
#endif
#ifdef Q_OS_MAC
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
    ui->label_4->setFont(QFont( "Arial", 11));
    ui->denaturationBox->setFont(QFont("Arial",10));
#endif
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_startButton_clicked()
{
    extern int mode;
    mode = ui->denaturationBox->currentIndex(); //0 = Thermal, 1 = Chemical
    winCD = new CDpal(this);
    winCD->showMaximized();
    hide();
}

void CDpal::on_actionMenu_triggered()
{
    QMessageBox::StandardButton dialog;
    dialog = QMessageBox::warning(this, "CDpal",
                 "Do you want to return to the main menu? Any unsaved changes will be lost.",
                 QMessageBox::Ok | QMessageBox::Cancel);
    if( dialog == QMessageBox::Ok)
    {
        hide();
        MainWindow *winMain;
        winMain = new MainWindow(this);
        winMain->show();
    }
}

void MainWindow::on_updateLink_clicked()
{
        QDesktopServices::openUrl(QUrl("https://github.com/PINT-NMR/CDpal"));
}

void MainWindow::on_exitButton_clicked()
{
    QApplication::quit();
}
