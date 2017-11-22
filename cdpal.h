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

#ifndef CDPAL_H
#define CDPAL_H

#include <QMainWindow>
#include <iostream>
#include <fstream>
#include "cstdlib"
#include "mfunc.h"
#include "globals.h"
#include "scaledialog.h"
#include "exportdialog.h"
#include "helpdialog.h"
#include "qcustomplot.h"
#include "customformat.h"
#include "ftest.h"
#include "savepreset.h"
#include "loadpreset.h"
#include "namefiles.h"
#include "qcustomplot.h"
#include "fitdiff.h"
#include "simulatedialog.h"

namespace Ui {
class CDpal;
}

class CDpal : public QMainWindow
{
    Q_OBJECT

public:
    explicit CDpal(QWidget *parent = 0);
    ~CDpal();
    struct style{
        QPen pen;
        QCPScatterStyle ornament;
    };

private:
    Ui::CDpal *ui;
    bool toggleState;
    bool toggleState2;
    bool chemical;
    bool diffMode;
    simulateDialog *simDiag;

public slots:
    void changeDiffMode(bool startup);
    void Autofit();
    void AutofitAll();
    void AutofitTm(std::vector< double > xV, std::vector< double > yV);
    void Autofit2Tm(std::vector< double > xV, std::vector< double > yV);
    void AutofitDeltaCp();
    void AutofitDeltaH();
    void Autofit2DeltaCp();
    void Autofit2DeltaH();
    void Autofitm();
    void Autofit2m();
    void AutofitRegion(int state, int len, std::vector< double > x, std::vector< double > y);
    void Autofit2Region(int state, int len, std::vector< double > x, std::vector< double > y);
    void autoScale();
    void axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part);
    QString calcSG(int model, int mode, double x, double y, double x2, double y2);
    QString calcdSdG(int model, int submodel, int submodel2, int mode, double x, double y, double x2, double y2, double dx, double dy, double dx2, double dy2);
    void changeOrnament();
    QString checkCustomFormat(std::string f, int h, int c, int t, int sr, int pb,QString text);
    QString checkFormat(std::string f);
    QPen changePen(QPen pen, int i);
    void changeWidth();
    void childClosed();
    void clearForm();
    void clearResults();
    void closeEvent(QCloseEvent *event);
    void colorGraph();
    void contextMenuRequest(QPoint pos);
    void exportResults();
    void fillLabels(int no, int model);
    void fitData();
    void fitRegion(int state);
    void fTest();
    double convertNotation(QString str);
    QString convSlash(QString word);
    void graphClicked(QCPAbstractPlottable *plottable);
    void handleAutofit(int type);
    void helpAdv();
    void helpEvent();
    void highlight();
    void initializeGlobals();
    void legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item);
    void loadData();
    void loadLabels(int model);
    void loadStyle();
    void mergeGraphs();
    void moveLegend();
    void mousePress();
    void mouseWheel();
    void omitData();
    void on_actionMenu_triggered();
    void on_actionND_triggered();
    void on_actionNID_triggered();
    void on_actionNDNID_triggered();
    void on_actionQuit_triggered();
    void on_actionSimulate_data_triggered();
    void on_helpButton_clicked();
    void openProject();
    void plotfit(int graphNo);
    void readData(QStringList list, int normalize, QString item);
    void removeAllGraphs();
    void removeFittedGraphs();
    void removeHighlight();
    void removeSelectedGraph();
    void deleteLastDataset();
    void renderGraph(std::vector< std::vector<std::string> > dataVec, int mode, int graphNo);
    void saveProject();
    void saveResults();
    void saveStyle();
    void scaleGraph();
    void selectionChanged();
    void setupChemicalGUI();
    void setupLabels();
    void setupDiffLabels();
    void titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title);
    void toggleDW();
    void toggleDW2();
    void updateTable(int graphNo);
    void differentiate();
    void simulate();
private slots:
    void on_clearButtonDiff_clicked();
    void on_fitDiff_clicked();
    void on_autoFitDiff_clicked();
    void on_autofitAllDiff_clicked();
    void autoFitDiff(int idx, bool manual, double mdH, double mtm, double ma);
};

#endif // CDPAL_H
