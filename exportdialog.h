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

#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include "QRect"
#include "QDesktopWidget"
#include "QMessageBox"

namespace Ui {
class exportDialog;
}

class exportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit exportDialog(QWidget *parent = 0);
    ~exportDialog();

private:
    Ui::exportDialog *ui;
    bool fitExist;

public slots:
    void acceptEvent();
    void selectAll();
    void selectNone();
    void setupList();
    void checkSave();
};

#endif // EXPORTDIALOG_H
