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
//  Date: 22 November, 2017
//  Version: 2.18
//

#include "cdpal.h"
#include "ui_cdpal.h"
#include "invertmatrix.h"
#include "fitFunction.h"
#include "errorsim.h"
#include "output.h"
#include "QLocale"
#include "random"

CDpal::CDpal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CDpal)
{
    simDiag = 0;
    diffMode = false;
    initializeGlobals();
    toggleState =false;
    toggleState2 =false;
    srand(QDateTime::currentDateTime().toTime_t());
    extern int mode;
    chemical=mode; //1 = true = Chemical, 0 = false = Temp
    ui->setupUi(this);
#ifdef Q_OS_LINUX
    ui->l1->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->l2->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->l3->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->l4->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_3->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_4->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_5->setFont(QFont( "Arial", 8));
    ui->label_6->setFont(QFont( "Arial", 8));
    ui->label_7->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_8->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_9->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_10->setFont(QFont( "Arial", 8));
    ui->label_11->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_12->setFont(QFont( "Arial", 8));
    ui->label_13->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_14->setFont(QFont( "Arial", 8));
    ui->label_15->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_16->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_17->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_18->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_19->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_20->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_21->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_22->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_23->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_24->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_30->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_31->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_32->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_33->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_34->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_35->setFont(QFont( "Arial", 8));
    ui->chemicalP->setFont(QFont( "Arial", 8));
    ui->label_36->setFont(QFont( "Arial", 8));
    ui->label_37->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_38->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_39->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_40->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_41->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_81->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_82->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_83->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_84->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_85->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_86->setFont(QFont( "Arial", 8));
    ui->label_87->setFont(QFont( "Arial", 8));
    ui->label_88->setFont(QFont( "Arial", 8));
    ui->label_89->setFont(QFont( "Arial", 8));
    ui->label_90->setFont(QFont( "Arial", 8));
    ui->label_93->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_95->setFont(QFont( "Arial", 8));
    ui->label_96->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_97->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_98->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_99->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_101->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_117->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_118->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_119->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_120->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_121->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_122->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_123->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_124->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_125->setFont(QFont( "Arial", 8));
    ui->label_126->setFont(QFont( "Arial", 8));
    ui->label_127->setFont(QFont( "Arial", 8));
    ui->label_129->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_130->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_131->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_132->setFont(QFont( "Arial", 8));
    ui->label_133->setFont(QFont( "Arial", 8));
    ui->label_134->setFont(QFont( "Arial", 8));
    ui->label_135->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_136->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_137->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_138->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_139->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_140->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_141->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_142->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_143->setFont(QFont( "Arial", 8));
    ui->label_144->setFont(QFont( "Arial", 8));
    ui->label_145->setFont(QFont( "Arial", 8));
    ui->label_147->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_148->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_149->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->label_150->setFont(QFont( "Arial", 8));
    ui->label_151->setFont(QFont( "Arial", 8));
    ui->label_152->setFont(QFont( "Arial", 8));
    ui->proteinFix3->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->proteinFixChemical->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->proteinFix4->setFont(QFont( "Arial", 8, QFont::Bold));
    ui->lCp->setFont(QFont( "Arial", 8));
    ui->lCp_2->setFont(QFont( "Arial", 8));
    ui->lH1->setFont(QFont( "Arial", 8));
    ui->lH2->setFont(QFont( "Arial", 8));
    ui->lId->setFont(QFont( "Arial", 8));
    ui->lIi->setFont(QFont( "Arial", 8));
    ui->lIn->setFont(QFont( "Arial", 8));
    ui->lKd->setFont(QFont( "Arial", 8));
    ui->lKi->setFont(QFont( "Arial", 8));
    ui->lKn->setFont(QFont( "Arial", 8));
    ui->lP->setFont(QFont( "Arial", 8));
    ui->lS->setFont(QFont( "Arial", 8));
    ui->lTm1->setFont(QFont( "Arial", 8));
    ui->lTm2->setFont(QFont( "Arial", 8));
    //Tabwidgets
    ui->tabWidget->setFont(QFont( "Arial", 9));
    ui->tabWidget_2->setFont(QFont( "Arial", 9));
    //Toolbar
    ui->actionAutofit->setFont(QFont( "Arial", 8));
    ui->actionMenu->setFont(QFont( "Arial", 8));
    ui->actionAutofit_All->setFont(QFont( "Arial", 8));
    ui->actionAutoscale->setFont(QFont( "Arial", 8));
    ui->actionAutoscale_2->setFont(QFont( "Arial", 8));
    ui->actionChange_pen_width->setFont(QFont( "Arial", 8));
    ui->actionChange_style->setFont(QFont( "Arial", 8));
    ui->actionColor->setFont(QFont( "Arial", 8));
    ui->actionContext_Help->setFont(QFont( "Arial", 8));
    ui->actionDelete_all_graphs->setFont(QFont( "Arial", 8));
    ui->actionDelete_fitted_graphs->setFont(QFont( "Arial", 8));
    ui->actionDelete_graph->setFont(QFont( "Arial", 8));
    ui->actionExport->setFont(QFont( "Arial", 8));
    ui->actionExport_data->setFont(QFont( "Arial", 8));
    ui->actionFit->setFont(QFont( "Arial", 8));
    ui->actionF_test->setFont(QFont( "Arial", 8));
    ui->actionMerge->setFont(QFont( "Arial", 8));
    ui->actionOpen->setFont(QFont( "Arial", 8));
    ui->actionOpen_Project->setFont(QFont( "Arial", 8));
    ui->actionQuit->setFont(QFont( "Arial", 8));
    ui->actionSave->setFont(QFont( "Arial", 8));
    ui->actionSave_Project->setFont(QFont( "Arial", 8));
    ui->actionLoad_style_preset_2->setFont(QFont( "Arial", 8));
    ui->actionSave_style_preset->setFont(QFont( "Arial", 8));
    ui->actionScale_graph->setFont(QFont( "Arial", 8));
    ui->actionToggle_dock_widgets->setFont(QFont( "Arial", 8));
    ui->actionToggle_dock_widgets2->setFont(QFont( "Arial", 8));
    ui->toolBar->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.511, y1:1, x2:0.506, y2:0, stop:0 rgba(135, 190, 205, 255), stop:1 rgba(255, 255, 255, 255));\nborder-right-color: rgb(0,0,0);");
#endif
#ifdef Q_OS_MAC
    ui->l1->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->l2->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->l3->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->l4->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_3->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_4->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_5->setFont(QFont( "Arial", 10));
    ui->label_6->setFont(QFont( "Arial", 10));
    ui->label_7->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_8->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_9->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_10->setFont(QFont( "Arial", 10));
    ui->label_11->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_12->setFont(QFont( "Arial", 10));
    ui->label_13->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_14->setFont(QFont( "Arial", 10));
    ui->label_15->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_16->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_17->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_18->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_19->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_20->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_21->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_22->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_23->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_24->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_30->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_31->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_32->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_33->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_34->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_35->setFont(QFont( "Arial", 10));
    ui->label_36->setFont(QFont( "Arial", 10));
    ui->label_37->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_38->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->chemicalP->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_39->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_40->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_41->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_81->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_82->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_83->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_84->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_85->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_86->setFont(QFont( "Arial", 10));
    ui->label_87->setFont(QFont( "Arial", 10));
    ui->label_88->setFont(QFont( "Arial", 10));
    ui->label_89->setFont(QFont( "Arial", 10));
    ui->label_90->setFont(QFont( "Arial", 10));
    ui->label_93->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_95->setFont(QFont( "Arial", 10));
    ui->label_96->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_97->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_98->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_99->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_101->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_117->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_118->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_119->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_120->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_121->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_122->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_123->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_124->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_125->setFont(QFont( "Arial", 10));
    ui->label_126->setFont(QFont( "Arial", 10));
    ui->label_127->setFont(QFont( "Arial", 10));
    ui->label_129->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_130->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_131->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_132->setFont(QFont( "Arial", 10));
    ui->label_133->setFont(QFont( "Arial", 10));
    ui->label_134->setFont(QFont( "Arial", 10));
    ui->label_135->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_136->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_137->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_138->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_139->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_140->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_141->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_142->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_143->setFont(QFont( "Arial", 10));
    ui->label_144->setFont(QFont( "Arial", 10));
    ui->label_145->setFont(QFont( "Arial", 10));
    ui->label_147->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_148->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_149->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->label_150->setFont(QFont( "Arial", 10));
    ui->label_151->setFont(QFont( "Arial", 10));
    ui->label_152->setFont(QFont( "Arial", 10));
    ui->proteinFix3->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->proteinFix4->setFont(QFont( "Arial", 10, QFont::Bold));
    ui->lCp->setFont(QFont( "Arial", 10));
    ui->lCp_2->setFont(QFont( "Arial", 10));
    ui->lH1->setFont(QFont( "Arial", 10));
    ui->lH2->setFont(QFont( "Arial", 10));
    ui->lId->setFont(QFont( "Arial", 10));
    ui->lIi->setFont(QFont( "Arial", 10));
    ui->lIn->setFont(QFont( "Arial", 10));
    ui->lKd->setFont(QFont( "Arial", 10));
    ui->lKi->setFont(QFont( "Arial", 10));
    ui->lKn->setFont(QFont( "Arial", 10));
    ui->lP->setFont(QFont( "Arial", 10));
    ui->lS->setFont(QFont( "Arial", 10));
    ui->lTm1->setFont(QFont( "Arial", 10));
    ui->lTm2->setFont(QFont( "Arial", 10));
    //Tabwidgets
    ui->tabWidget->setFont(QFont( "Arial", 10));
    ui->tabWidget_2->setFont(QFont( "Arial", 10));
    //Toolbar
    ui->actionAutofit->setFont(QFont( "Arial", 10));
    ui->actionMenu->setFont(QFont( "Arial", 10));
    ui->actionAutofit_All->setFont(QFont( "Arial", 10));
    ui->actionAutoscale->setFont(QFont( "Arial", 10));
    ui->actionAutoscale_2->setFont(QFont( "Arial", 10));
    ui->actionChange_pen_width->setFont(QFont( "Arial", 10));
    ui->actionChange_style->setFont(QFont( "Arial", 10));
    ui->actionColor->setFont(QFont( "Arial", 10));
    ui->actionContext_Help->setFont(QFont( "Arial", 10));
    ui->actionDelete_all_graphs->setFont(QFont( "Arial", 10));
    ui->actionDelete_fitted_graphs->setFont(QFont( "Arial", 10));
    ui->actionDelete_graph->setFont(QFont( "Arial", 10));
    ui->actionExport->setFont(QFont( "Arial", 10));
    ui->actionExport_data->setFont(QFont( "Arial", 10));
    ui->actionFit->setFont(QFont( "Arial", 10));
    ui->actionF_test->setFont(QFont( "Arial", 10));
    ui->actionMerge->setFont(QFont( "Arial", 10));
    ui->actionOpen->setFont(QFont( "Arial", 10));
    ui->actionOpen_Project->setFont(QFont( "Arial", 10));
    ui->actionQuit->setFont(QFont( "Arial", 10));
    ui->actionSave->setFont(QFont( "Arial", 10));
    ui->actionSave_Project->setFont(QFont( "Arial", 10));
    ui->actionLoad_style_preset_2->setFont(QFont( "Arial", 10));
    ui->actionSave_style_preset->setFont(QFont( "Arial", 10));
    ui->actionScale_graph->setFont(QFont( "Arial", 10));
    ui->actionToggle_dock_widgets->setFont(QFont( "Arial", 10));
    ui->actionToggle_dock_widgets2->setFont(QFont( "Arial", 10));
    ui->toolBar->setStyleSheet("background-color: qlineargradient(spread:pad, x1:0.511, y1:1, x2:0.506, y2:0, stop:0 rgba(135, 190, 205, 255), stop:1 rgba(255, 255, 255, 255));\nborder-right-color: rgb(0,0,0);");
    //ButtonSize
    ui->helpButton->setFont(QFont( "Arial", 10));
    ui->helpButton->setMaximumHeight(15);
    ui->helpButton_2->setFont(QFont( "Arial", 10));
    ui->helpButton_2->setMaximumHeight(15);
    ui->helpButton_3->setFont(QFont( "Arial", 10));
    ui->helpButton_3->setMaximumHeight(15);
    ui->helpButton_4->setFont(QFont( "Arial", 10));
    ui->helpButton_4->setMaximumHeight(15);
    ui->region1->setFont(QFont( "Arial", 10));
    ui->region1->setMaximumHeight(15);
    ui->region2->setFont(QFont( "Arial", 10));
    ui->region2->setMaximumHeight(15);
    ui->regionD2->setFont(QFont( "Arial", 10));
    ui->regionD2->setMaximumHeight(15);
    ui->regionD3->setFont(QFont( "Arial", 10));
    ui->regionD3->setMaximumHeight(15);
    ui->regionD_4->setFont(QFont( "Arial", 10));
    ui->regionD_4->setMaximumHeight(15);
    ui->regionI2->setFont(QFont( "Arial", 10));
    ui->regionI2->setMaximumHeight(15);
    ui->regionI3->setFont(QFont( "Arial", 10));
    ui->regionI3->setMaximumHeight(15);
    ui->regionI_4->setFont(QFont( "Arial", 10));
    ui->regionI_4->setMaximumHeight(15);
    ui->regionN2->setFont(QFont( "Arial", 10));
    ui->regionN2->setMaximumHeight(15);
    ui->regionN3->setFont(QFont( "Arial", 10));
    ui->regionN3->setMaximumHeight(15);
    ui->regionN_4->setFont(QFont( "Arial", 10));
    ui->regionN_4->setMaximumHeight(15);
    ui->fitButton->setFont(QFont( "Arial", 10));
    ui->fitButton->setMaximumHeight(15);
    ui->fitButton_2->setFont(QFont( "Arial", 10));
    ui->fitButton_2->setMaximumHeight(15);
    ui->fitButton_3->setFont(QFont( "Arial", 10));
    ui->fitButton_3->setMaximumHeight(15);
    ui->fitButton_4->setFont(QFont( "Arial", 10));
    ui->fitButton_4->setMaximumHeight(15);
    ui->clearButton_3->setFont(QFont( "Arial", 10));
    ui->clearButton_3->setMaximumHeight(15);
    ui->clearButton_2->setFont(QFont( "Arial", 10));
    ui->clearButton_2->setMaximumHeight(15);
    ui->clearButton_4->setFont(QFont( "Arial", 10));
    ui->clearButton_4->setMaximumHeight(15);
    ui->clearButton->setFont(QFont( "Arial", 10));
    ui->clearButton->setMaximumHeight(15);
    ui->activeLabel->setFont(QFont( "Arial", 12));
    ui->omitButton->setFont(QFont( "Arial", 11));
    ui->omitButton->setMinimumHeight(21);
    ui->omitButton->setMaximumHeight(21);
    // Layouts
    ui->label_120->setMaximumWidth(130);
    ui->label_138->setMaximumWidth(130);
    ui->label_30->setMaximumWidth(110);
    ui->label_37->setMaximumWidth(110);
    ui->horizontalLayout_106->setSpacing(0);
    ui->horizontalLayout_107->setSpacing(0);
    ui->horizontalLayout_119->setSpacing(0);
    ui->horizontalLayout_120->setSpacing(0);
    ui->horizontalLayout_108->setSpacing(15);
    ui->horizontalLayout_109->setSpacing(15);
    ui->horizontalLayout_110->setSpacing(15);
    ui->horizontalLayout_112->setSpacing(10);
    ui->horizontalLayout_113->setSpacing(15);
    ui->horizontalLayout_114->setSpacing(15);
    ui->horizontalLayout_115->setSpacing(15);
    ui->horizontalLayout_121->setSpacing(15);
    ui->horizontalLayout_122->setSpacing(15);
    ui->horizontalLayout_123->setSpacing(15);
    ui->horizontalLayout_125->setSpacing(10);
    ui->horizontalLayout_126->setSpacing(15);
    ui->horizontalLayout_127->setSpacing(15);
    ui->horizontalLayout_128->setSpacing(15);
    ui->horizontalLayout_84->setSpacing(10);
    ui->horizontalLayout_85->setSpacing(10);
    ui->horizontalLayout_92->setSpacing(10);
    ui->horizontalLayout_78->setSpacing(10);
    ui->horizontalLayout_15->setSpacing(0);
    ui->horizontalLayout_18->setSpacing(10);
    ui->horizontalLayout_21->setSpacing(10);
    ui->horizontalSpacer_4->changeSize(50,20,QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->horizontalSpacer_27->changeSize(20,20,QSizePolicy::Fixed,QSizePolicy::Fixed);
    ui->verticalLayout->setSpacing(0);
    ui->verticalLayout_3->setSpacing(0);
    ui->verticalLayout_5->setSpacing(0);
    ui->verticalLayout_6->setSpacing(0);
    ui->verticalLayout_9->setSpacing(0);
    ui->verticalLayout_10->setSpacing(0);
    ui->verticalLayout_11->setSpacing(0);
    ui->verticalLayout_14->setSpacing(0);
    ui->verticalLayout_15->setSpacing(0);
    ui->verticalLayout_16->setSpacing(0);
    ui->verticalLayout_18->setSpacing(0);
#endif
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
    ui->CDplot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                QCP::iSelectLegend | QCP::iSelectPlottables | QCP::iSelectItems);
    if(mode==0)
        ui->CDplot->xAxis->setRange(20, 70);
    else
        ui->CDplot->xAxis->setRange(0, 1);
    ui->CDplot->yAxis->setRange(-0.1, 1.1);
    ui->CDplot->axisRect()->setupFullAxesBox();

    ui->CDplot->plotLayout()->insertRow(0);
    QCPPlotTitle *qTitle =  new QCPPlotTitle(ui->CDplot, "Double click to change title");
    qTitle->setFont(QFont("sans", 16, QFont::Bold));
    ui->CDplot->plotLayout()->addElement(0, 0, qTitle);
    if(mode==0)
        ui->CDplot->xAxis->setLabel("Temperature (°C)");
    else
        ui->CDplot->xAxis->setLabel("Concentration (M)");
    ui->CDplot->yAxis->setLabel("CD");
    ui->CDplot->xAxis->setLabelFont(QFont("sans", 12, QFont::Bold));
    ui->CDplot->yAxis->setLabelFont(QFont("sans", 12, QFont::Bold));
    ui->CDplot->legend->setVisible(true);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->CDplot->legend->setFont(legendFont);
    ui->CDplot->legend->setSelectedFont(legendFont);
    ui->CDplot->legend->setSelectableParts(QCPLegend::spItems); // legend box shall not be selectable, only legend items
    // connect slot that ties some axis selections together (especially opposite axes):
    connect(ui->CDplot, SIGNAL(selectionChangedByUser()), this, SLOT(selectionChanged()));
    // connect slots that takes care that when an axis is selected, only that direction can be dragged and zoomed:
    connect(ui->CDplot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->CDplot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    // make bottom and left axes transfer their ranges to top and right axes:
    connect(ui->CDplot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->CDplot->xAxis2, SLOT(setRange(QCPRange)));
    connect(ui->CDplot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->CDplot->yAxis2, SLOT(setRange(QCPRange)));

    // connect some interaction slots:
    connect(ui->CDplot, SIGNAL(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)), this, SLOT(titleDoubleClick(QMouseEvent*,QCPPlotTitle*)));
    connect(ui->CDplot, SIGNAL(axisDoubleClick(QCPAxis*,QCPAxis::SelectablePart,QMouseEvent*)), this, SLOT(axisLabelDoubleClick(QCPAxis*,QCPAxis::SelectablePart)));
    connect(ui->CDplot, SIGNAL(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*,QMouseEvent*)), this, SLOT(legendDoubleClick(QCPLegend*,QCPAbstractLegendItem*)));

    // connect slot that shows a message in the status bar when a graph is clicked:
    connect(ui->CDplot, SIGNAL(plottableClick(QCPAbstractPlottable*,QMouseEvent*)), this, SLOT(graphClicked(QCPAbstractPlottable*)));

    // setup policy and connect slot for context menu popup:
    ui->CDplot->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->CDplot, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuRequest(QPoint)));
    extern QPen faucetPen;
    extern int faucetInt;
    extern int faucetShape;
    faucetInt = 0;
    faucetShape = 2;
    faucetPen.setColor(QColor(sin(0.7)*100+100, 0,sin(0.6)*100+100));

    connect(ui->table, SIGNAL(itemSelectionChanged()), this, SLOT(highlight()));

    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveResults()));

    connect(ui->omitButton, SIGNAL(clicked()), this, SLOT(omitData()));
    connect(ui->actionScale_graph, SIGNAL(triggered()), this, SLOT(scaleGraph()));

    QSignalMapper *mapper = new QSignalMapper(this);
    connect(mapper, SIGNAL(mapped(int)), this, SLOT(fitRegion(int)));
    //Model 1
    connect(ui->region1, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->region1,1);
    connect(ui->region2, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->region2,2);
    //Model 2
    connect(ui->regionN2, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->regionN2,1);
    connect(ui->regionD2, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->regionD2,2);
    connect(ui->regionI2, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->regionI2,3);
    //Model 3
    connect(ui->regionN3, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->regionN3,1);
    connect(ui->regionD3, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->regionD3,2);
    connect(ui->regionI3, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->regionI3,3);
    //Model 4
    connect(ui->regionN_4, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->regionN_4,1);
    connect(ui->regionD_4, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->regionD_4,2);
    connect(ui->regionI_4, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(ui->regionI_4,3);

    connect(ui->actionMerge, SIGNAL(triggered()),this, SLOT(mergeGraphs()));

    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));
    ui->deltaEdit->setValidator( new QDoubleValidator(ui->deltaEdit) );
    ui->tmEdit->setValidator( new QDoubleValidator(ui->tmEdit) );
    ui->slope1Edit->setValidator( new QDoubleValidator(ui->slope1Edit) );
    ui->slope2Edit->setValidator( new QDoubleValidator(ui->slope2Edit) );
    ui->intercept1Edit->setValidator( new QDoubleValidator(ui->intercept1Edit) );
    ui->intercept2Edit->setValidator( new QDoubleValidator(ui->intercept2Edit) );
    connect(ui->clearButton, SIGNAL(clicked()), this, SLOT(clearForm()));
    connect(ui->clearButton_2, SIGNAL(clicked()), this, SLOT(clearForm()));
    connect(ui->clearButton_3, SIGNAL(clicked()), this, SLOT(clearForm()));
    connect(ui->clearButton_4, SIGNAL(clicked()), this, SLOT(clearForm()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(loadData()));
    connect(ui->actionAutoscale_2, SIGNAL(triggered()), this, SLOT(autoScale()));
    connect(ui->actionContext_Help, SIGNAL(triggered()), this, SLOT(helpEvent()));
    connect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
    connect(ui->helpButton_2, SIGNAL(clicked()), this, SLOT(helpAdv()));
    connect(ui->helpButton_3, SIGNAL(clicked()), this, SLOT(helpAdv()));
    connect(ui->helpButton_4, SIGNAL(clicked()), this, SLOT(helpAdv()));
    ui->CDplot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    ui->CDplot->replot();

    connect(ui->actionToggle_dock_widgets,SIGNAL(triggered()), this, SLOT(toggleDW()));
    connect(ui->actionToggle_dock_widgets2,SIGNAL(triggered()), this, SLOT(toggleDW2()));
    if(mode==1)
        setupChemicalGUI();
    else
        setupLabels();
    ui->trButton->setVisible(false);
    ui->modelButton->setVisible(false);
    connect(ui->trButton, SIGNAL(clicked()), this, SLOT(toggleDW()));
    connect(ui->modelButton, SIGNAL(clicked()), this, SLOT(toggleDW2()));
    connect(ui->actionOpen_Project, SIGNAL(triggered()), this, SLOT(openProject()));
    if(chemical)
        ui->toolBar->removeAction(ui->actionDifferentiate);
    connect(ui->actionDifferentiate, SIGNAL(triggered()), this, SLOT(differentiate()));
    changeDiffMode(false);
}

void CDpal::changeDiffMode(bool startup)
{
    ui->actionAutofit->setDisabled(diffMode);
    ui->actionAutofit_All->setDisabled(diffMode);
    ui->actionFit->setDisabled(diffMode);
    ui->actionDifferentiate->setDisabled(diffMode);
    if(diffMode)
    {
        if(!startup)
            ui->CDplot->yAxis->setLabel("Rate of fractional change");
        ui->tabWidget->setTabEnabled(4,true);
        ui->tabWidget->setTabEnabled(0,false);
        ui->tabWidget->setTabEnabled(1,false);
        ui->tabWidget->setTabEnabled(2,false);
        ui->tabWidget->setTabEnabled(3,false);
        ui->tabWidget->setStyleSheet("QTabWidget::pane { \nmargin: 0px,1px,1px,1px;\nborder: 3px solid #020202;\nborder-radius: 7px;\npadding: 1px;\n	background-color: qlineargradient(spread:pad, x1:0.511, y1:1, x2:0.506, y2:0, stop:0 rgba(135, 190, 205, 100), stop:1 rgba(255, 255, 255, 255));\n}\nQTabBar::tab { \nmargin: 0px,0px,0px,0px;\nborder: 1px solid #020202;\nborder-radius: 5px;\npadding: 4px;\n }\nQTabBar::tab:selected, QTabBar::tab:hover {\n    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,                                      stop: 0 #fafafa, stop: 0.4 #f4f4f4,                                      stop: 0.5 #e7e7e7, stop: 1.0 #fafafa); \n     }\nQTabBar::tab:selected { \n	border-color: #9B9B9B;          \n	border-bottom-color: #C2C7CB;\n}\nQTabBar::tab:!selected {\n    margin-top: 2px;\n}\n\nQTabBar::tab::disabled {width: 0; height: 0; margin: 0; padding: 0; border: none;}");
        ui->CDplot->replot();
        setupDiffLabels();
    }
    else
    {
        if(!startup)
            ui->CDplot->yAxis->setLabel("Fractional change");
        ui->tabWidget->setTabEnabled(4,false);
        ui->tabWidget->setTabEnabled(0,true);
        ui->tabWidget->setTabEnabled(1,true);
        ui->tabWidget->setTabEnabled(2,true);
        ui->tabWidget->setTabEnabled(3,true);
        ui->tabWidget->setStyleSheet("QTabWidget::pane { \nmargin: 0px,1px,1px,1px;\nborder: 3px solid #020202;\nborder-radius: 7px;\npadding: 1px;\n	background-color: qlineargradient(spread:pad, x1:0.511, y1:1, x2:0.506, y2:0, stop:0 rgba(135, 190, 205, 100), stop:1 rgba(255, 255, 255, 255));\n}\nQTabBar::tab { \nmargin: 0px,0px,0px,0px;\nborder: 1px solid #020202;\nborder-radius: 5px;\npadding: 4px;\n }\nQTabBar::tab:selected, QTabBar::tab:hover {\n    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,                                      stop: 0 #fafafa, stop: 0.4 #f4f4f4,                                      stop: 0.5 #e7e7e7, stop: 1.0 #fafafa); \n     }\nQTabBar::tab:selected { \n	border-color: #9B9B9B;          \n	border-bottom-color: #C2C7CB;\n}\nQTabBar::tab:!selected {\n    margin-top: 2px;\n}\n\nQTabBar::tab::disabled {width: 0; height: 0; margin: 0; padding: 0; border: none;}");
        ui->CDplot->replot();
        if(chemical)
            setupChemicalGUI();
        else
            setupLabels();
    }
}

void CDpal::differentiate()
{
    if(diffMode) return;
    QMessageBox::StandardButton dialog;
    dialog = QMessageBox::warning(this, "CDpal",
                                  "Do you want to differentiate the data sets?\n"
                                  "All current data sets will be discarded."
                                  "\nThis step cannot be undone.",
                                  QMessageBox::Yes | QMessageBox::No);
    if( dialog == QMessageBox::No)
        return;
    diffMode = true;
    changeDiffMode(false);
    int max(ui->CDplot->graphCount());
    std::vector< std::vector< std::vector<std::string> > > dVec2;
    QVector<QString> graphNames;
    for(int i(0); i<max; ++i)
    {
        if(ui->CDplot->graph(i)->name().contains("(fit:"))
            continue;
        std::vector<std::string> diffVec;
        bool ok(true);
        for(int j(0); j<ui->CDplot->graph(i)->data()->values().count(); ++j)
        {
            double x2(.0),x1(.0);
            double y2(.0),y1(.0);
            int it(0);
            if(j==0)
            {
                if(ui->CDplot->graph(i)->data()->values().count()<4)
                {
                    ok = false;
                    break;
                }
                while(x2-x1==0.0 && ok)
                {
                    x1 =ui->CDplot->graph(i)->data()->values().at(j+1).key;
                    y1 =ui->CDplot->graph(i)->data()->values().at(j+1).value;
                    x2 =ui->CDplot->graph(i)->data()->values().at(j+2+it).key;
                    y2 =ui->CDplot->graph(i)->data()->values().at(j+2+it).value;
                    if(x2-x1)
                        diffVec.push_back(QString::number((y2-y1)/(x2-x1)).toStdString());
                    else
                    {
                        if(j+2+it < ui->CDplot->graph(i)->data()->values().count())
                            it++;
                        else //fail
                            ok = false;
                    }
                }
            }
            else if(j==ui->CDplot->graph(i)->data()->values().count()-1)
            {
                if(ui->CDplot->graph(i)->data()->values().count()<4)
                {
                    ok = false;
                    break;
                }
                while(x2-x1==0.0 && ok)
                {
                    x1 =ui->CDplot->graph(i)->data()->values().at(j-2-it).key;
                    y1 =ui->CDplot->graph(i)->data()->values().at(j-2-it).value;
                    x2 =ui->CDplot->graph(i)->data()->values().at(j-1).key;
                    y2 =ui->CDplot->graph(i)->data()->values().at(j-1).value;
                    if(x2-x1)
                        diffVec.push_back(QString::number((y2-y1)/(x2-x1)).toStdString());
                    else
                    {
                        if(j-it-3 > 0)
                            it++;
                        else //fail
                            ok = false;
                    }
                }
            }
            else
            {
                int it2(0);
                while(x2-x1==0.0 && ok)
                {
                    x1 =ui->CDplot->graph(i)->data()->values().at(j-1-it).key;
                    y1 =ui->CDplot->graph(i)->data()->values().at(j-1-it).value;
                    x2 =ui->CDplot->graph(i)->data()->values().at(j+1+it2).key;
                    y2 =ui->CDplot->graph(i)->data()->values().at(j+1+it2).value;
                    if(x2-x1)
                        diffVec.push_back(QString::number((y2-y1)/(x2-x1)).toStdString());
                    else
                    {
                        if(j-it-2 > 0)
                            it++;
                        else if(j+2+it2 < ui->CDplot->graph(i)->data()->values().count())
                            it2++;
                        else //fail
                            ok = false;
                    }
                }
            }
            if(!ok)
                break;
        }
        if(!ok || diffVec.size() != (uint) ui->CDplot->graph(i)->data()->values().count())
            continue;

        std::vector< std::vector<std::string> > dVec;
        for(uint j(0); j<diffVec.size(); ++j)
        {
            std::vector<std::string> tmpVec;
            double d = ui->CDplot->graph(i)->data()->keys().at(j);
            std::string x(mconvert(d));
            tmpVec.push_back(x);
            tmpVec.push_back(diffVec.at(j));
            dVec.push_back(tmpVec);
        }
        dVec2.push_back(dVec);
        graphNames.push_back(ui->CDplot->graph(i)->name());
    }
    ui->CDplot->clearGraphs();
    ui->CDplot->replot();
    updateTable(0);
    clearResults();
    extern std::vector< std::vector< std::string> > rV2;
    extern std::vector< std::vector< std::string> > resultStrVec;
    resultStrVec.clear();
    rV2.clear();
    ui->graphBox->clear();
    ui->graphBox_2->clear();
    ui->graphBox_3->clear();
    ui->graphBox_4->clear();
    ui->graphBoxDiff->clear();
    extern bool customName;
    extern QString currentName;
    customName = true;
    for(uint i(0); i<dVec2.size(); ++i)
    {
        currentName = graphNames.at(i);
        renderGraph(dVec2.at(i), 0, 0);
    }
    customName = false;
}

void CDpal::on_actionND_triggered()
{
    handleAutofit(1);
}

void CDpal::on_actionNID_triggered()
{
    handleAutofit(2);
}

void CDpal::on_actionNDNID_triggered()
{
    handleAutofit(3);
}

void CDpal::handleAutofit(int type)
{
    switch(type)
    {
    case 1:
        ui->actionND->setChecked(true);
        ui->actionNID->setChecked(false);
        ui->actionNDNID->setChecked(false);
        break;
    case 2:
        ui->actionND->setChecked(false);
        ui->actionNID->setChecked(true);
        ui->actionNDNID->setChecked(false);
        break;
    case 3:
        ui->actionND->setChecked(false);
        ui->actionNID->setChecked(false);
        ui->actionNDNID->setChecked(true);
        break;
    }
}

void CDpal::setupChemicalGUI()
{
    ui->scaleLabel->hide();
    ui->fscale->hide();
    ui->errscale->hide();
    ui->chemicalP->hide();
    ui->proteinBoxChemical->hide();
    ui->proteinFixChemical->hide();
    //Ensure html for labels in the result tab
    ui->lP->setText("<html><font color=\"black\">[P]</font> (µM)</html>");
    ui->lH1->setText("<html><font color=\"red\">m</font> (kJ&bull;mol<sup>-1</sup>&bull;M<sup>-1</sup>)</html>");
    ui->lH2->setText("<html><font color=\"red\">m<sub>2</sub></font> (kJ&bull;mol<sup>-1</sup>&bull;M<sup>-1</sup>)</html>");
    ui->lTm1->setText("<html><font color=\"green\">Cm</font> (M)</html>");
    ui->lTm2->setText("<html><font color=\"green\">Cm<sub>2</sub></font> (M)</html>");
    ui->lIn->setText("<html><font color=\"red\">m<sub>N</sub></font></html>");
    ui->lId->setText("<html><font color=\"blue\">m<sub>D</sub></font></html>");
    ui->lIi->setText("<html><font color=\"green\">m<sub>I</sub><font color=\"green\"></html>");
    ui->lKd->setText("<html><font color=\"blue\">k<sub>D</sub></font></html>");
    ui->lKi->setText("<html><font color=\"green\">k<sub>I</sub></font></html>");
    ui->lKn->setText("<html><font color=\"red\">k<sub>N</sub></font></html>");
    ui->lS->setText("<html>&Delta;G (kJ/mol)</html>");
    //Hides elements according to N->D model
    ui->lCp->setVisible(false);
    ui->fCp->setVisible(false);
    ui->errCp->setVisible(false);
    ui->lP->setVisible(false);
    ui->fP->setVisible(false);
    ui->errP->setVisible(false);
    ui->lH2->setVisible(false);
    ui->fH2->setVisible(false);
    ui->errH2->setVisible(false);
    ui->lTm2->setVisible(false);
    ui->fTm2->setVisible(false);
    ui->errTm2->setVisible(false);
    ui->lCp_2->setText("<html><font color=\"black\">[P]</font> (µM)</html>");
    ui->lCp_2->setVisible(false);
    ui->fCp_2->setVisible(false);
    ui->errCp_2->setVisible(false);
    ui->lIi->setVisible(false);
    ui->fIi->setVisible(false);
    ui->errIi->setVisible(false);
    ui->lKi->setVisible(false);
    ui->fKi->setVisible(false);
    ui->errKi->setVisible(false);

    //Special settings correcting labels in the model interface
    //N->D
    ui->label_5->setText("m (kJ<html>&bull;mol<sup>-1</sup>&bull;M<sup>-1</sup>)</html>");
    ui->label_6->setText("Cm (M)");
    ui->label_14->setText("Temperature (<html>&deg;</html>C)");
    ui->cpBox->setChecked(false);
    ui->cpEdit->setText("25");
    ui->cpBox->setVisible(false);
    ui->chemicalSpacer->changeSize(31,20);
    //N->I->D
    ui->label_86->setText("m (kJ<html>&bull;mol<sup>-1</sup>&bull;M<sup>-1</sup>)</html>");
    ui->label_87->setText("Cm (M)");
    ui->label_88->setText("Temperature (<html>&deg;</html>C)");
    ui->cpBox_2a->setChecked(false);
    ui->cpEdit_2b->setVisible(false);
    ui->cpBox_2b->setVisible(false);
    ui->cpEdit_2a->setText("25");
    ui->cpBox_2a->setVisible(false);
    ui->chemicalSpacer1->changeSize(118,20);
    //N2->2I-2D
    ui->label_125->setText("m (kJ<html>&bull;mol<sup>-1</sup>&bull;M<sup>-1</sup>)</html>");
    ui->label_126->setText("Cm (M)");
    ui->label_127->setText("Temperature (<html>&deg;</html>C)");
    ui->cpBox_3a->setChecked(false);
    ui->cpEdit_3b->setVisible(false);
    ui->cpBox_3b->setVisible(false);
    ui->chemicalSpacer2->changeSize(118,20);
    ui->cpEdit_3a->setText("25");
    ui->cpBox_3a->setVisible(false);
    //N2->I2->2D
    ui->label_143->setText("m (kJ<html>&bull;mol<sup>-1</sup>&bull;M<sup>-1</sup>)</html>");
    ui->label_144->setText("Cm (M)");
    ui->label_145->setText("Temperature (<html>&deg;</html>C)");
    ui->cpBox_4a->setChecked(false);
    ui->cpEdit_4b->setVisible(false);
    ui->cpBox_4b->setVisible(false);
    ui->chemicalSpacer3->changeSize(118,20);
    ui->cpEdit_4a->setText("25");
    ui->cpBox_4a->setVisible(false);
}

void CDpal::initializeGlobals()
{
    //Switching between chemical and temperature modes can cause errors
    //if the global variables are not reinitialized
    extern int activeGraph; activeGraph=-1;
    extern QString activeIndex; activeIndex="";
    extern int degree; degree=3;
    extern bool drawLine; drawLine=false;
    extern QStringList exportList; exportList.clear();
    extern std::vector < std::vector <QString> > fitParams; fitParams.clear();
    extern bool fitRes; fitRes=false;
    extern QString matrixError; matrixError="";
    extern int highlightGraph; highlightGraph=-1;
    extern QStringList itemLabels; itemLabels.clear();
    extern std::string resultStr; resultStr="";
    extern std::vector< std::vector< std::string> > resultStrVec; resultStrVec.clear();
    extern int scaleIdx; scaleIdx=0;
    extern double xmax; xmax=1;
    extern double xmin; xmin=-1;
    extern std::vector< std::string > xplotfit; xplotfit.clear();
    extern double ymax; ymax=1;
    extern double ymin; ymin=-1;
    extern std::vector< std::string > yplotfit; yplotfit.clear();
    extern bool titleChanged; titleChanged=false;
    extern QString dirString; dirString="";
    extern QString titleName; titleName="Double click to change title";
    extern std::vector< std::string> rV; rV.clear();
    extern std::vector< std::vector< std::string> > rV2; rV2.clear();
    extern bool saveRes; saveRes=true;
    extern QString resFileName; resFileName="";
    extern QString sPattern; sPattern="";
    extern double minXG; minXG=9999.9;
    extern double maxXG; maxXG=-9999.9;
    extern QStringList takenNames; takenNames.clear();
    extern std::vector< std::vector<std::vector<std::string> > >storedData; storedData.clear();
    extern QString currentName; currentName.clear();
    extern QStringList graphNames; graphNames.clear();
    extern QStringList files; files.clear();
    extern QVector<QCPScatterStyle> ornamentVec; ornamentVec.clear();
    extern QVector<QString> styleVec; styleVec.clear();
}

void CDpal::setupDiffLabels()
{
    ui->modelEdit->hide();
    ui->label_2->hide();
    ui->lP->hide();
    ui->lH2->hide();
    ui->lTm2->hide();
    ui->lCp->hide();;
    ui->lCp_2->hide();
    ui->lIn->hide();
    ui->lId->hide();
    ui->lIi->hide();
    ui->lKd->hide();
    ui->lKi->hide();
    ui->lKn->hide();
    ui->lS->hide();
    ui->lH1->hide();
    ui->lH1diff->show();
    ui->lH1diff->setText("<html><font color=\"red\">|&Delta;H|</font> (kJ/mol)</html>");

    ui->fP->hide();
    ui->fH2->hide();
    ui->fTm2->hide();
    ui->fCp->hide();;
    ui->fCp_2->hide();
    ui->fIn->hide();
    ui->fId->hide();
    ui->fIi->hide();
    ui->fKd->hide();
    ui->fKi->hide();
    ui->fKn->hide();
    ui->fS->hide();

    ui->errP->hide();
    ui->errH2->hide();
    ui->errTm2->hide();
    ui->errCp->hide();;
    ui->errCp_2->hide();
    ui->errIn->hide();
    ui->errId->hide();
    ui->errIi->hide();
    ui->errKd->hide();
    ui->errKi->hide();
    ui->errKn->hide();
    ui->errS->hide();
    ui->scaleLabel->show();
    ui->fscale->show();
    ui->errscale->show();
}

void CDpal::setupLabels()
{
    ui->scaleLabel->hide();
    ui->fscale->hide();
    ui->errscale->hide();
    ui->fP->show();
    ui->fH2->show();
    ui->fTm2->show();
    ui->fCp->show();;
    ui->fCp_2->show();
    ui->fIn->show();
    ui->fId->show();
    ui->fIi->show();
    ui->fKd->show();
    ui->fKi->show();
    ui->fKn->show();
    ui->fS->show();
    ui->errP->show();
    ui->errH2->show();
    ui->errTm2->show();
    ui->errCp->show();;
    ui->errCp_2->show();
    ui->errIn->show();
    ui->errId->show();
    ui->errIi->show();
    ui->errKd->show();
    ui->errKi->show();
    ui->errKn->show();
    ui->errS->show();
    ui->lP->show();
    ui->lH2->show();
    ui->lTm1->show();
    ui->lCp->show();;
    ui->lCp_2->show();
    ui->lIn->show();
    ui->lId->show();
    ui->lIi->show();
    ui->lKd->show();
    ui->lKi->show();
    ui->lKn->show();
    ui->lS->show();
    ui->label_2->show();
    ui->modelEdit->show();
    //Special settings for thermal denaturation mode
    ui->chemicalLine->hide();
    ui->chemicalLine1->hide();
    ui->chemicalLine2->hide();
    ui->chemicalLine3->hide();
    ui->chemicalP->hide();
    ui->proteinBoxChemical->hide();
    ui->proteinFixChemical->hide();
    //Ensure html for labels in the result tab
    ui->lP->setText("<html><font color=\"black\">[P]</font> (µM)</html>");
    ui->lH1->setText("<html><font color=\"red\">&Delta;H</font> (kJ/mol)</html>");
    ui->lH2->setText("<html><font color=\"red\">&Delta;H<sub>2</sub></font> (kJ/mol)</html>");
    ui->lTm1->setText("<html><font color=\"green\">Tm</font> (&deg;C)</html>");
    ui->lTm2->setText("<html><font color=\"green\">Tm<sub>2</sub></font> (&deg;C)</html>");
    ui->lCp->setText("<html><font color=\"blue\">&Delta;Cp</font> (J/(K&bull;mol))</html>");
    ui->lCp_2->setText("<html><font color=\"blue\">&Delta;Cp<sub>2</sub></font> (J/(K&bull;mol))</html>");
    ui->lIn->setText("<html><font color=\"red\">m<sub>N</sub></font></html>");
    ui->lId->setText("<html><font color=\"blue\">m<sub>D</sub></font></html>");
    ui->lIi->setText("<html><font color=\"green\">m<sub>I</sub><font color=\"green\"></html>");
    ui->lKd->setText("<html><font color=\"blue\">k<sub>D</sub></font></html>");
    ui->lKi->setText("<html><font color=\"green\">k<sub>I</sub></font></html>");
    ui->lKn->setText("<html><font color=\"red\">k<sub>N</sub></font></html>");
    ui->lS->setText("<html>&Delta;S (kJ/(K&bull;mol))</html>");
    //Hides elements according to N->D model
    ui->lP->setVisible(false);
    ui->fP->setVisible(false);
    ui->errP->setVisible(false);
    ui->lH2->setVisible(false);
    ui->fH2->setVisible(false);
    ui->errH2->setVisible(false);
    ui->lTm2->setVisible(false);
    ui->fTm2->setVisible(false);
    ui->errTm2->setVisible(false);
    ui->lCp_2->setVisible(false);
    ui->fCp_2->setVisible(false);
    ui->errCp_2->setVisible(false);
    ui->lIi->setVisible(false);
    ui->fIi->setVisible(false);
    ui->errIi->setVisible(false);
    ui->lKi->setVisible(false);
    ui->fKi->setVisible(false);
    ui->errKi->setVisible(false);
    ui->lH1->show();
    ui->lH1diff->hide();
}

void CDpal::clearResults()
{
    ui->modelEdit->setText("");
    ui->e1->setText("");
    ui->e2->setText("");
    ui->e3->setText("");
    ui->e4->setText("");
    ui->fH1->setText("");
    ui->errH1->setText("");
    ui->fTm1->setText("");
    ui->errTm1->setText("");
    ui->fId->setText("");
    ui->errId->setText("");
    ui->fIn->setText("");
    ui->errIn->setText("");
    ui->fH2->setText("");
    ui->errH2->setText("");
    ui->fTm2->setText("");
    ui->errTm2->setText("");
    ui->fCp->setText("");
    ui->errCp->setText("");
    ui->fCp_2->setText("");
    ui->errCp_2->setText("");
    ui->fP->setText("");
    ui->errP->setText("");
    ui->fIi->setText("");
    ui->errIi->setText("");
    ui->fS->setText("");
    ui->errS->setText("");
    ui->fKi->setText("");
    ui->fKd->setText("");
    ui->fKn->setText("");
    ui->errKi->setText("");
    ui->errKn->setText("");
    ui->errKd->setText("");

}

void CDpal::toggleDW()
{
    if(toggleState)
    {
        ui->trButton->setVisible(false);
        ui->tableScroll->setVisible(true);
        //ui->dockWidget->setVisible(true);
        toggleState=false;
    }
    else
    {
        ui->tableScroll->setVisible(false);
        ui->trButton->setVisible(true);
        //ui->dockWidget->setVisible(false);
        toggleState=true;
    }
}

void CDpal::toggleDW2()
{
    if(toggleState2)
    {
        //ui->dockWidget_3->setVisible(true);
        ui->modelButton->setVisible(false);
        ui->modelScroll->setVisible(true);
        toggleState2=false;
        ui->tabWidget_2->sizePolicy().setVerticalPolicy(QSizePolicy::Minimum);
    }
    else
    {
        ui->modelButton->setVisible(true);
        //ui->dockWidget_3->setVisible(false);
        ui->modelScroll->setVisible(false);
        toggleState2=true;
        ui->tabWidget_2->sizePolicy().setVerticalPolicy(QSizePolicy::Expanding);
    }
}

void CDpal::helpEvent()
{
    helpDialog helpWin;
    helpWin.setWindowModality(Qt::ApplicationModal);
    if(helpWin.exec())
    {
    }
}

void CDpal::clearForm()
{
    int model = ui->tabWidget->currentIndex()+1;
    switch (model)
    {
    case 1:
        ui->intercept1Edit->setText("");
        ui->intercept2Edit->setText("");
        ui->slope1Edit->setText("");
        ui->slope2Edit->setText("");
        ui->deltaEdit->setText("");
        ui->tmEdit->setText("");
        if(chemical)
            ui->cpEdit->setText("25");
        else
            ui->cpEdit->setText("0");
        ui->cpBox->setChecked(true);
        ui->deltaBox->setChecked(false);
        ui->tmBox->setChecked(false);
        ui->intercept1Box->setChecked(false);
        ui->intercept2Box->setChecked(false);
        ui->slope1Box->setChecked(false);
        ui->slope2Box->setChecked(false);
        break;
    case 2:
        ui->deltaBox_2a->setChecked(false);
        ui->deltaBox_2b->setChecked(false);
        ui->deltaEdit_2a->setText("");
        ui->deltaEdit_2b->setText("");
        ui->tmBox_2a->setChecked(false);
        ui->tmBox_2b->setChecked(false);
        ui->tmEdit_2a->setText("");
        ui->tmEdit_2b->setText("");
        if(chemical)
            ui->cpEdit_2a->setText("25");
        else
            ui->cpEdit_2a->setText("0");
        ui->cpEdit_2b->setText("0");
        ui->cpBox_2a->setChecked(true);
        ui->cpBox_2b->setChecked(true);
        ui->interceptEditD_2->setText("");
        ui->interceptEditN_2->setText("");
        ui->interceptEditI_2->setText("");
        ui->interceptBoxD_2->setChecked(false);
        ui->interceptBoxN_2->setChecked(false);
        ui->interceptBoxI_2->setChecked(false);
        ui->slopeEditD_2->setText("");
        ui->slopeEditN_2->setText("");
        ui->slopeEditI_2->setText("");
        ui->slopeBoxD_2->setChecked(false);
        ui->slopeBoxN_2->setChecked(false);
        ui->slopeBoxI_2->setChecked(false);
        if(chemical)
        {
            ui->proteinBoxChemical->setText("");
            ui->proteinFixChemical->setChecked(true);
        }
        break;
    case 3:
        ui->deltaBox_3a->setChecked(false);
        ui->deltaBox_3b->setChecked(false);
        ui->deltaEdit_3a->setText("");
        ui->deltaEdit_3b->setText("");
        ui->tmBox_3a->setChecked(false);
        ui->tmBox_3b->setChecked(false);
        ui->tmEdit_3a->setText("");
        ui->tmEdit_3b->setText("");
        if(chemical)
            ui->cpEdit_3a->setText("25");
        else
            ui->cpEdit_3a->setText("0");
        ui->cpEdit_3b->setText("0");
        ui->cpBox_3a->setChecked(true);
        ui->cpBox_3b->setChecked(true);
        ui->interceptEditD_3->setText("");
        ui->interceptEditN_3->setText("");
        ui->interceptEditI_3->setText("");
        ui->interceptBoxD_3->setChecked(false);
        ui->interceptBoxN_3->setChecked(false);
        ui->interceptBoxI_3->setChecked(false);
        ui->slopeEditD_3->setText("");
        ui->slopeEditN_3->setText("");
        ui->slopeEditI_3->setText("");
        ui->slopeBoxD_3->setChecked(false);
        ui->slopeBoxN_3->setChecked(false);
        ui->slopeBoxI_3->setChecked(false);
        ui->proteinBox_3->setText("");
        ui->proteinFix3->setChecked(true);
        break;
    case 4:
        ui->deltaBox_4a->setChecked(false);
        ui->deltaBox_4b->setChecked(false);
        ui->deltaEdit_4a->setText("");
        ui->deltaEdit_4b->setText("");
        ui->tmBox_4a->setChecked(false);
        ui->tmBox_4b->setChecked(false);
        ui->tmEdit_4a->setText("");
        ui->tmEdit_4b->setText("");
        if(chemical)
            ui->cpEdit_4a->setText("0");
        else
            ui->cpEdit_4a->setText("0");
        ui->cpEdit_4b->setText("0");
        ui->cpBox_4a->setChecked(true);
        ui->cpBox_4b->setChecked(true);
        ui->interceptEditD_4->setText("");
        ui->interceptEditN_4->setText("");
        ui->interceptEditI_4->setText("");
        ui->interceptBoxD_4->setChecked(false);
        ui->interceptBoxN_4->setChecked(false);
        ui->interceptBoxI_4->setChecked(false);
        ui->slopeEditD_4->setText("");
        ui->slopeEditN_4->setText("");
        ui->slopeEditI_4->setText("");
        ui->slopeBoxD_4->setChecked(false);
        ui->slopeBoxN_4->setChecked(false);
        ui->slopeBoxI_4->setChecked(false);
        ui->proteinBox_4->setText("");
        ui->proteinFix4->setChecked(true);
        break;
    }
}

double CDpal::convertNotation(QString str)
{
    for(int i=0; i<str.length(); i++)
    {
        if(str[i]==',')
        {
            str[i]='.';
            break;
        }
    }
    return str.toDouble();
}

void CDpal::fitRegion(int state)//state=1 native, =2 unfolded, 3=intermediate
{
    extern QString matrixError;
    matrixError="";
    extern bool fitRes;
    fitRes=true;

    std::vector< double > a, x, y, errVal, params;
    std::vector< bool > fixed;
    extern int highlightGraph;
    if(highlightGraph==-1)
    {
        QMessageBox::StandardButton dialog;
        if(state==1)
            dialog = QMessageBox::warning(this, "CDpal",
                                          "Select a linear region of the native state before using \"Set\".",
                                          QMessageBox::Ok);
        else if(state==2)
            dialog = QMessageBox::warning(this, "CDpal",
                                          "Select a linear region of the unfolded state before using \"Set\".",
                                          QMessageBox::Ok);
        else
            dialog = QMessageBox::warning(this, "CDpal",
                                          "Select a linear region of the intermediate state before using \"Set\".",
                                          QMessageBox::Ok);
        if(dialog==QMessageBox::Ok)
            return;
    }
    const QCPDataMap *dataMap = ui->CDplot->graph(highlightGraph-1)->data();
    QMap<double, QCPData>::const_iterator j = dataMap->constBegin();
    int len =0;
    while (j != dataMap->constEnd())
    {
        j++;
        len++;
    }
    if(len==1)
    {
        QMessageBox::StandardButton dialog;
        dialog = QMessageBox::warning(this, "CDpal",
                                      "Select at least two data points to perform linear regression.",
                                      QMessageBox::Ok);
        if(QMessageBox::Ok==dialog)
            return;
    }
    x.resize(len);
    y.resize(len);
    errVal.resize(len);
    a.resize(2);
    a[0]=0;
    a[1]=1;
    params.resize(2);
    params[0]=a[0];
    params[1]=a[1];

    fixed.resize(2);
    for(int i=0; i<2; i++)
        fixed[i]=true;

    char *cfile=NULL;
    int dof(len);
    for(int i=0; i<2; i++)
        if(fixed[i]) --dof;

    QMap<double, QCPData>::const_iterator i = dataMap->constBegin();
    int iter =0;
    while (i != dataMap->constEnd())
    {
        x[iter]=i.value().key;
        y[iter]=i.value().value;
        errVal[iter]=1.0;
        i++;
        iter++;
    }

    void flin(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
    fitFunction fitData(x, y, errVal, params, fixed, flin);
    fitData.start();
    if(matrixError!="")
    {
        QMessageBox::StandardButton dialog3;
        dialog3 = QMessageBox::warning(this, "CDpal",
                                       "Linear regression failed. Please add or remove data points and try again. Aborting.",
                                       QMessageBox::Ok);
        if(QMessageBox::Ok==dialog3)
            matrixError="";
        return;
    }
    ErrorSim myerr(x, y, errVal, fitData.parVec, fixed, flin);
    myerr.simerror(); //jackknife

    Output myoutput(x, y, errVal, fitData.parVec, flin, myerr.jackerr,
                    fitData.variance, fitData.chi, dof, cfile, cfile);
    myoutput.print(true);
    myoutput.plot(false, true); //smooth plotting (many data points)
    extern std::string resultStr;
    std::istringstream iss(resultStr);
    std::string sub;
    iss >> sub;
    QString intercept = mconvert(sub);
    iss >> sub;
    QString slope = mconvert(sub);
    int model = ui->tabWidget->currentIndex()+1;
    switch(model)
    {
    case 1:
        if(state==1)
            ui->intercept1Edit->setText(intercept);
        else
            ui->intercept2Edit->setText(intercept);
        if(state==1)
            ui->slope1Edit->setText(slope);
        else
            ui->slope2Edit->setText(slope);
        break;
    case 2:
        if(state==1)
            ui->interceptEditN_2->setText(intercept);
        else if(state==2)
            ui->interceptEditD_2->setText(intercept);
        else
            ui->interceptEditI_2->setText(intercept);
        if(state==1)
            ui->slopeEditN_2->setText(slope);
        else if(state==2)
            ui->slopeEditD_2->setText(slope);
        else
            ui->slopeEditI_2->setText(slope);
        break;
    case 3:
        if(state==1)
            ui->interceptEditN_3->setText(intercept);
        else if(state==2)
            ui->interceptEditD_3->setText(intercept);
        else
            ui->interceptEditI_3->setText(intercept);
        if(state==1)
            ui->slopeEditN_3->setText(slope);
        else if(state==2)
            ui->slopeEditD_3->setText(slope);
        else
            ui->slopeEditI_3->setText(slope);
        break;
    case 4:
        if(state==1)
            ui->interceptEditN_4->setText(intercept);
        else if(state==2)
            ui->interceptEditD_4->setText(intercept);
        else
            ui->interceptEditI_4->setText(intercept);
        if(state==1)
            ui->slopeEditN_4->setText(slope);
        else if(state==2)
            ui->slopeEditD_4->setText(slope);
        else
            ui->slopeEditI_4->setText(slope);
        break;
    }
    fitRes=false;
}

void CDpal::on_helpButton_clicked()
{
    QMessageBox::StandardButton dialog;
    dialog = QMessageBox::warning(this, "CDpal",
                                  "Linear regression\nInstead of estimating the slope and intercept of your data you can set regions used for linear regression by utilizing this function.\n\n1. Select a graph that should be fitted and highlight the linear native region in the table.\n2. Click \"Set\".\n3. Repeat steps 1 and 2 for the linear denatured region.\n\nThe results from the linear regression will be displayed as the intercept and slope parameters for fitting.",
                                  QMessageBox::Ok);
    if(dialog==QMessageBox::Ok)
        return;
}

void CDpal::helpAdv()
{
    QMessageBox::StandardButton dialog;
    dialog = QMessageBox::warning(this, "CDpal",
                                  "Linear regression\nInstead of estimating the slope and intercept of your data you can set regions used for linear regression by utilizing this function.\n\n1. Select a graph that should be fitted and highlight the linear native region in the table.\n2. Click \"Set\".\n3. Repeat steps 1 and 2 for the linear intermediate and denatured regions.\n\nThe results from the linear regression will be displayed as the intercept and slope parameters for fitting.",
                                  QMessageBox::Ok);
    if(dialog==QMessageBox::Ok)
        return;
}

void CDpal::mergeGraphs()
{
    if (ui->CDplot->graphCount() > 1)
    {
        QMessageBox::StandardButton dialog;
        dialog = QMessageBox::warning(this, "CDpal",
                                      "Do you want to merge all data into one data set?\nMerging graphs will delete any curve fits.\nThis step cannot be undone.",
                                      QMessageBox::Yes | QMessageBox::No);
        if( dialog == QMessageBox::Yes)
        {
            std::vector<std::vector<std::string> > dataVec;
            for(int i=0; i<ui->CDplot->graphCount(); i++)
            {
                bool cont=true;
                if(ui->CDplot->graph(i)->name().length()>4)
                {
                    for(int k=0; k<ui->CDplot->graph(i)->name().length()-4; k++)
                    {
                        if(ui->CDplot->graph(i)->name()[k]=='(' && ui->CDplot->graph(i)->name()[k+1]=='f' && ui->CDplot->graph(i)->name()[k+2]=='i' && ui->CDplot->graph(i)->name()[k+3]=='t' && ui->CDplot->graph(i)->name()[k+4]==':')
                        {
                            cont =false;
                            break;
                        }
                    }
                    if(!cont)
                        continue;
                }
                const QCPDataMap *dataMap = ui->CDplot->graph(i)->data();
                QMap<double, QCPData>::const_iterator j = dataMap->constBegin();
                while (j != dataMap->constEnd())
                {
                    std::vector<std::string> tempVec;
                    std::string str = mconvert(QString::number(j.value().key));
                    tempVec.push_back(str);
                    str = mconvert(QString::number(j.value().value));
                    tempVec.push_back(str);
                    dataVec.push_back(tempVec);
                    j++;
                }
            }
            ui->CDplot->clearGraphs();
            ui->CDplot->replot();
            updateTable(0);
            extern std::vector< std::vector< std::string> > resultStrVec;
            resultStrVec.clear();
            //Disables functions when no data is present
            renderGraph(dataVec,0,0);
            ui->graphBox->clear();
            ui->graphBox->addItem(ui->CDplot->graph(0)->name());
            ui->graphBox_2->clear();
            ui->graphBox_2->addItem(ui->CDplot->graph(0)->name());
            ui->graphBox_3->clear();
            ui->graphBox_3->addItem(ui->CDplot->graph(0)->name());
            ui->graphBox_4->clear();
            ui->graphBox_4->addItem(ui->CDplot->graph(0)->name());
            ui->graphBox_4->clear();
            ui->graphBox_4->addItem(ui->CDplot->graph(0)->name());
            ui->graphBoxDiff->clear();
            ui->graphBoxDiff->addItem(ui->CDplot->graph(0)->name());
        }
    }
}

void CDpal::titleDoubleClick(QMouseEvent* event, QCPPlotTitle* title)
{
    Q_UNUSED(event)
    // Set the plot title by double clicking on it
    extern bool titleChanged;
    titleChanged=true;
    bool ok;
    QString newTitle = QInputDialog::getText(this, "CDpal", "New plot title:", QLineEdit::Normal, title->text(), &ok);
    if (ok&& newTitle!="")
    {
        extern QString titleName;
        titleName =newTitle;
        title->setText(newTitle);
        title->setFont(QFont("sans", 16, QFont::Bold));
        ui->CDplot->replot();
    }
}

void CDpal::changeOrnament()
{
    extern int activeGraph;
    if(activeGraph!=-1)
    {
        QString str(ui->CDplot->graph(activeGraph)->name());
        if(str.length()>4)
            for(int i=0; i<str.length()-4; i++)
            {
                if(str[i]=='(' && str[i+1]=='f' && str[i+2]=='i' && str[i+3]=='t' && str[i+4]==':')
                    return;
            }
        QVector<QCPScatterStyle::ScatterShape> shapes;
        shapes << QCPScatterStyle::ssCross;
        shapes << QCPScatterStyle::ssPlus;
        shapes << QCPScatterStyle::ssCircle;
        shapes << QCPScatterStyle::ssDisc;
        shapes << QCPScatterStyle::ssSquare;
        shapes << QCPScatterStyle::ssDiamond;
        shapes << QCPScatterStyle::ssStar;
        shapes << QCPScatterStyle::ssTriangle;
        shapes << QCPScatterStyle::ssTriangleInverted;
        shapes << QCPScatterStyle::ssCrossSquare;
        shapes << QCPScatterStyle::ssPlusSquare;
        shapes << QCPScatterStyle::ssCrossCircle;
        shapes << QCPScatterStyle::ssPlusCircle;
        shapes << QCPScatterStyle::ssPeace;
        QStringList items;
        items << tr("Cross") << tr("Plus") << tr("Circle") << tr("Disc") << tr("Square");
        items << tr("Diamond") << tr("Star") << tr("Triangle") << tr("Inverted Triangle");
        items << tr("Cross Square") << tr("Plus Square") << tr("Cross Circle") << tr("Plus Circle") << tr("Peace");
        bool ok;
        QString item = QInputDialog::getItem(this, tr("Change point style"), tr("Point style"),items,0,false,&ok);
        if(ok && !item.isEmpty())
        {
            if(item=="Cross")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(0), 10));
            else if(item=="Plus")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(1), 10));
            else if(item=="Circle")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(2), 10));
            else if(item=="Disc")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(3), 10));
            else if(item=="Square")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(4), 10));
            else if(item=="Diamond")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(5), 10));
            else if(item=="Star")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(6), 10));
            else if(item=="Triangle")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(7), 10));
            else if(item=="Inverted Triangle")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(8), 10));
            else if(item=="Cross Square")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(9), 10));
            else if(item=="Plus Square")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(10), 10));
            else if(item=="Cross Circle")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(11), 10));
            else if(item=="Plus Circle")
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(12), 10));
            else
                ui->CDplot->graph(activeGraph)->setScatterStyle(QCPScatterStyle(shapes.at(13), 10));
            ui->CDplot->replot();
        }
    }
}

void CDpal::changeWidth()
{
    extern int activeGraph;
    if(activeGraph!=-1)
    {
        bool ok;
        int width = QInputDialog::getInt(this, tr("Change pen width"), tr("Pen width"), 2, 0, 10, 1,&ok);
        QPen Pen = ui->CDplot->graph(activeGraph)->pen();
        Pen.setWidth(width);
        ui->CDplot->graph(activeGraph)->setPen(Pen);
        ui->CDplot->replot();
    }
}

void CDpal::colorGraph()
{
    extern int activeGraph;
    if(activeGraph!=-1)
    {
        QColor color = QColorDialog::getColor(Qt::red, this);
        if(color.isValid())
        {
            QPen pen;
            pen.setColor(color);
            pen.setWidth(ui->CDplot->graph(activeGraph)->pen().width());
            ui->CDplot->graph(activeGraph)->setPen(pen);
            ui->CDplot->graph(activeGraph)->setErrorPen(pen);
            ui->CDplot->replot();
        }
    }
}

void CDpal::autoScale()
{
    double xmin, xmax, ymin, ymax;
    xmin = ymin = 9999.0;
    xmax = ymax = -9999.0;
    if(ui->CDplot->graphCount()==0)
    {
        xmin = 20.0;
        xmax = 70.0;
        ymin = -0.0;
        ymax = 1.0;
    }
    for(int i=0; i<ui->CDplot->graphCount(); i++)
    {
        std::vector< std::vector<std::string> > dataVec;
        const QCPDataMap *dataMap = ui->CDplot->graph(i)->data();
        QMap<double, QCPData>::const_iterator j = dataMap->constBegin();
        while (j != dataMap->constEnd())
        {
            if(xmin>j.value().key)
                xmin=j.value().key;
            if(ymin>j.value().value)
                ymin=j.value().value;
            if(xmax<j.value().key)
                xmax=j.value().key;
            if(ymax<j.value().value)
                ymax=j.value().value;
            j++;
        }
    }
    ui->CDplot->xAxis->setRange(xmin-1, xmax+1);
    ui->CDplot->yAxis->setRange(ymin-0.1, ymax+0.1);
    ui->CDplot->replot();
}

void CDpal::scaleGraph()
{
    scaleDialog scaleWin;
    scaleWin.setWindowModality(Qt::ApplicationModal);
    if(scaleWin.exec())
    {
        //Ok Clicked
        extern int scaleIdx;
        if(scaleIdx==0)
        {
            autoScale();
        }
        else
        {
            extern double xmin;
            extern double xmax;
            extern double ymin;
            extern double ymax;
            ui->CDplot->xAxis->setRange(xmin, xmax);
            ui->CDplot->yAxis->setRange(ymin, ymax);
        }
        ui->CDplot->replot();
    }
}

void CDpal::removeHighlight()
{
    extern int highlightGraph;
    if(highlightGraph>-1)
    {
        ui->CDplot->removeGraph(highlightGraph-1);
        highlightGraph=-1;
        ui->CDplot->replot();
    }
}

void CDpal::on_actionQuit_triggered()
{
    QMessageBox::StandardButton dialog;
    dialog = QMessageBox::warning(this, "CDpal",
                                  "Do you want to quit?\nAny unsaved changes will be lost.",
                                  QMessageBox::Ok | QMessageBox::Cancel);
    if( dialog == QMessageBox::Ok)
        QApplication::quit();
}

void CDpal::childClosed()
{
    this->setEnabled(true);
}

void CDpal::axisLabelDoubleClick(QCPAxis *axis, QCPAxis::SelectablePart part)
{
    // Set an axis label by double clicking on it
    if (part == QCPAxis::spAxisLabel) // only react when the actual axis label is clicked, not tick label or axis backbone
    {
        bool ok;
        QString newLabel = QInputDialog::getText(this, "CDpal", "New axis label:", QLineEdit::Normal, axis->label(), &ok);
        if (ok && newLabel!="")
        {
            axis->setLabel(newLabel);
            axis->setLabelFont(QFont("sans", 12, QFont::Bold));
            ui->CDplot->replot();
        }
    }
}

void CDpal::legendDoubleClick(QCPLegend *legend, QCPAbstractLegendItem *item)
{
    // Rename a graph by double clicking on its legend item
    Q_UNUSED(legend)
    if (item) // only react if item was clicked (user could have clicked on border padding of legend where there is no item, then item is 0)
    {
        QCPPlottableLegendItem *plItem = qobject_cast<QCPPlottableLegendItem*>(item);
        QString str = plItem->plottable()->name();
        bool fit = false;
        if(str.length()>4)
            for(int i=0; i<str.length()-4; i++)
            {
                if(str[i]=='(' && str[i+1]=='f' && str[i+2]=='i' && str[i+3]=='t' && str[i+4]==':')
                    fit = true;
            }
        if(!fit)
        {
            bool ok;
            QString newName = QInputDialog::getText(this, "CDpal", "New graph name:", QLineEdit::Normal, plItem->plottable()->name(), &ok);
            if (ok && newName!="")
            {
                bool dup=false;
                for(int i=0; i<ui->CDplot->graphCount(); i++)
                {
                    if (newName==ui->CDplot->graph(i)->name())
                    {
                        dup=true;
                        break;
                    }
                }
                if(dup)
                    QMessageBox::warning(this, "Error","Graph name must be unique", QMessageBox::Ok);
                else
                {
                    if(newName.length()>4)
                        for(int i=0; i<newName.length()-4; i++)
                        {
                            if(newName[i]=='(' && newName[i+1]=='f' && newName[i+2]=='i' && newName[i+3]=='t' && newName[i+4]==':')
                                fit=true;
                        }
                    if(!fit)
                    {
                        plItem->plottable()->setName(newName);
                        QString str2 =str;
                        str2+="(fit:";
                        for(int i=0; i<ui->graphBox->count(); i++)
                        {
                            if(ui->graphBox->itemText(i)==str)
                            {
                                ui->graphBox->setItemText(i,newName);
                                ui->graphBox_2->setItemText(i,newName);
                                ui->graphBox_3->setItemText(i,newName);
                                ui->graphBox_4->setItemText(i,newName);
                                ui->graphBoxDiff->setItemText(i,newName);
                            }
                            else if(str2.length()<ui->graphBox->itemText(i).length())
                            {
                                if(str2==ui->graphBox->itemText(i).mid(0,str2.length()))
                                {
                                    QString newName2 = newName;
                                    newName2+="(fit:";
                                    newName2+=ui->graphBox->itemText(i).mid(str2.length());
                                    ui->graphBox->setItemText(i,newName2);
                                    ui->graphBox_2->setItemText(i,newName2);
                                    ui->graphBox_3->setItemText(i,newName2);
                                    ui->graphBox_4->setItemText(i,newName2);
                                    ui->graphBoxDiff->setItemText(i,newName2);
                                }
                            }
                        }
                        for(int i =0; i<ui->CDplot->plottableCount();i++)
                            if(str2.length()<ui->CDplot->plottable(i)->name().length())
                            {
                                if(str2==ui->CDplot->plottable(i)->name().mid(0,str2.length()))
                                {
                                    QString newName2 = newName;
                                    newName2+="(fit:";
                                    newName2+=ui->CDplot->plottable(i)->name().mid(str2.length());
                                    ui->CDplot->plottable(i)->setName(newName2);
                                    extern std::vector< std::vector< std::string> > resultStrVec;
                                    for(unsigned int i=0; i<resultStrVec.size(); i++)
                                        if(resultStrVec[i][1].length()>static_cast<unsigned int>(str.length()))
                                            if(mconvert(resultStrVec[i][1]).mid(0,str.length())==str)
                                            {
                                                resultStrVec[i][1]=mconvert(newName2);
                                                break;
                                            }
                                }
                            }
                        ui->CDplot->replot();
                    }
                    else if(fit)
                        QMessageBox::warning(this, "Error","Graph name is reserved for fitted graphs", QMessageBox::Ok);
                }
            }
        }
    }
}

void CDpal::selectionChanged()
{
    if(ui->CDplot->graphCount()==0)
        return;
    if(!ui->CDplot->legend->item(ui->CDplot->graphCount()-1)->selected())
        removeHighlight();
    /*
   normally, axis base line, axis tick labels and axis labels are selectable separately, but we want
   the user only to be able to select the axis as a whole, so we tie the selected states of the tick labels
   and the axis base line together. However, the axis label shall be selectable individually.

   The selection state of the left and right axes shall be synchronized as well as the state of the
   bottom and top axes.

   Further, we want to synchronize the selection of the graphs with the selection state of the respective
   legend item belonging to that graph. So the user can select a graph by either clicking on the graph itself
   or on its legend item.
  */

    // make top and bottom axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->CDplot->xAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->CDplot->xAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->CDplot->xAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->CDplot->xAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->CDplot->xAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->CDplot->xAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // make left and right axes be selected synchronously, and handle axis and tick labels as one selectable object:
    if (ui->CDplot->yAxis->selectedParts().testFlag(QCPAxis::spAxis) || ui->CDplot->yAxis->selectedParts().testFlag(QCPAxis::spTickLabels) ||
            ui->CDplot->yAxis2->selectedParts().testFlag(QCPAxis::spAxis) || ui->CDplot->yAxis2->selectedParts().testFlag(QCPAxis::spTickLabels))
    {
        ui->CDplot->yAxis2->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
        ui->CDplot->yAxis->setSelectedParts(QCPAxis::spAxis|QCPAxis::spTickLabels);
    }
    // synchronize selection of graphs with selection of corresponding legend items:
    bool found=false;
    bool connected=false;
    extern int highlightGraph;
    for (int i=0; i<ui->CDplot->graphCount(); ++i)
    {
        if(i==highlightGraph-1 || i==highlightGraph)
            i++;
        if(i>=ui->CDplot->graphCount())
            break;
        QCPGraph *graph = ui->CDplot->graph(i);
        if (graph->selected())
        {
            graph->setSelected(true);

            {
                QCPPlottableLegendItem *item = ui->CDplot->legend->itemWithPlottable(graph);
                item->setSelected(true);
            }
            updateTable(i);
            connected = true;
            found=true;
            if(graph->name().length()>4)
            {
                for(int j=0; j<graph->name().length()-4; j++)
                {
                    if(graph->name()[j]=='(' && graph->name()[j+1]=='f' && graph->name()[j+2]=='i' && graph->name()[j+3]=='t' && graph->name()[j+4]==':')
                    {
                        QString str = graph->name();
                        extern std::vector< std::vector< std::string> > resultStrVec;
                        for(unsigned int k=0; k<resultStrVec.size(); k++)
                        {
                            if(mconvert(resultStrVec[k][1])==str)
                            {
                                std::istringstream iss(resultStrVec[k][2]);
                                std::string sub;
                                int cc=1;
                                iss >> sub;
                                int model = atoi(sub.c_str());
                                loadLabels(model);
                                fillLabels(k, model);
                                std::string pC;
                                bool pCheck(true);
                                if(model>2 && model!=5)
                                {
                                    iss>>sub;
                                    pC= sub;
                                    iss>>sub;
                                    if(sub!="true")
                                        pCheck=false;
                                }
                                while(iss>>sub)
                                {
                                    switch(model)
                                    {
                                    case 1:
                                    {
                                        ui->tabWidget->setCurrentIndex(0);
                                        switch (cc)
                                        {
                                        case 1:
                                            ui->deltaEdit->setText(mconvert(sub));
                                            break;
                                        case 2:
                                            if(sub=="true")
                                                ui->deltaBox->setChecked(true);
                                            else
                                                ui->deltaBox->setChecked(false);
                                            break;
                                        case 3:
                                            ui->tmEdit->setText(mconvert(sub));
                                            break;
                                        case 4:
                                            if(sub=="true")
                                                ui->tmBox->setChecked(true);
                                            else
                                                ui->tmBox->setChecked(false);
                                            break;
                                        case 5:
                                            ui->cpEdit->setText(mconvert(sub));
                                            break;
                                        case 6:
                                            if(sub=="true")
                                                ui->cpBox->setChecked(true);
                                            else
                                                ui->cpBox->setChecked(false);
                                            break;
                                        case 7:
                                            ui->slope1Edit->setText(mconvert(sub));
                                            break;
                                        case 8:
                                            if(sub=="true")
                                                ui->slope1Box->setChecked(true);
                                            else
                                                ui->slope1Box->setChecked(false);
                                            break;
                                        case 9:
                                            ui->intercept1Edit->setText(mconvert(sub));
                                            break;
                                        case 10:
                                            if(sub=="true")
                                                ui->intercept1Box->setChecked(true);
                                            else
                                                ui->intercept1Box->setChecked(false);
                                            break;
                                        case 11:
                                            ui->slope2Edit->setText(mconvert(sub));
                                            break;
                                        case 12:
                                            if(sub=="true")
                                                ui->slope2Box->setChecked(true);
                                            else
                                                ui->slope2Box->setChecked(false);
                                            break;
                                        case 13:
                                            ui->intercept2Edit->setText(mconvert(sub));
                                            break;
                                        case 14:
                                            if(sub=="true")
                                                ui->intercept2Box->setChecked(true);
                                            else
                                                ui->intercept2Box->setChecked(false);
                                            break;
                                        }
                                        break;
                                    }
                                    case 2:
                                    {
                                        ui->tabWidget->setCurrentIndex(1);
                                        switch (cc)
                                        {
                                        case 1:
                                            ui->deltaEdit_2a->setText(mconvert(sub));
                                            break;
                                        case 2:
                                            if(sub=="true")
                                                ui->deltaBox_2a->setChecked(true);
                                            else
                                                ui->deltaBox_2a->setChecked(false);
                                            break;
                                        case 3:
                                            ui->deltaEdit_2b->setText(mconvert(sub));
                                            break;
                                        case 4:
                                            if(sub=="true")
                                                ui->deltaBox_2b->setChecked(true);
                                            else
                                                ui->deltaBox_2b->setChecked(false);
                                            break;
                                        case 5:
                                            ui->tmEdit_2a->setText(mconvert(sub));
                                            break;
                                        case 6:
                                            if(sub=="true")
                                                ui->tmBox_2a->setChecked(true);
                                            else
                                                ui->tmBox_2a->setChecked(false);
                                            break;
                                        case 7:
                                            ui->tmEdit_2b->setText(mconvert(sub));
                                            break;
                                        case 8:
                                            if(sub=="true")
                                                ui->tmBox_2b->setChecked(true);
                                            else
                                                ui->tmBox_2b->setChecked(false);
                                            break;
                                        case 9:
                                            ui->cpEdit_2a->setText(mconvert(sub));
                                            break;
                                        case 10:
                                            if(sub=="true")
                                                ui->cpBox_2a->setChecked(true);
                                            else
                                                ui->cpBox_2a->setChecked(false);
                                            break;
                                        case 11:
                                            if(chemical)
                                                ui->proteinBoxChemical->setText(mconvert(sub));
                                            else
                                                ui->cpEdit_2b->setText(mconvert(sub));
                                            break;
                                        case 12:
                                            if(sub=="true")
                                            {
                                                if(chemical)
                                                    ui->proteinFixChemical->setChecked(true);
                                                else
                                                    ui->cpBox_2b->setChecked(true);
                                            }
                                            else
                                            {
                                                if(chemical)
                                                    ui->proteinFixChemical->setChecked(false);
                                                else
                                                    ui->cpBox_2b->setChecked(false);
                                            }
                                            break;
                                        case 13:
                                            ui->slopeEditN_2->setText(mconvert(sub));
                                            break;
                                        case 14:
                                            if(sub=="true")
                                                ui->slopeBoxN_2->setChecked(true);
                                            else
                                                ui->slopeBoxN_2->setChecked(false);
                                            break;
                                        case 15:
                                            ui->interceptEditN_2->setText(mconvert(sub));
                                            break;
                                        case 16:
                                            if(sub=="true")
                                                ui->interceptBoxN_2->setChecked(true);
                                            else
                                                ui->interceptBoxN_2->setChecked(false);
                                            break;
                                        case 17:
                                            ui->slopeEditI_2->setText(mconvert(sub));
                                            break;
                                        case 18:
                                            if(sub=="true")
                                                ui->slopeBoxI_2->setChecked(true);
                                            else
                                                ui->slopeBoxI_2->setChecked(false);
                                            break;
                                        case 19:
                                            ui->interceptEditI_2->setText(mconvert(sub));
                                            break;
                                        case 20:
                                            if(sub=="true")
                                                ui->interceptBoxI_2->setChecked(true);
                                            else
                                                ui->interceptBoxI_2->setChecked(false);
                                            break;
                                        case 21:
                                            ui->slopeEditD_2->setText(mconvert(sub));
                                            break;
                                        case 22:
                                            if(sub=="true")
                                                ui->slopeBoxD_2->setChecked(true);
                                            else
                                                ui->slopeBoxD_2->setChecked(false);
                                            break;
                                        case 23:
                                            ui->interceptEditD_2->setText(mconvert(sub));
                                            break;
                                        case 24:
                                            if(sub=="true")
                                                ui->interceptBoxD_2->setChecked(true);
                                            else
                                                ui->interceptBoxD_2->setChecked(false);
                                            break;
                                        }
                                        break;
                                    }
                                    case 3:
                                    {
                                        ui->tabWidget->setCurrentIndex(2);
                                        switch (cc)
                                        {
                                        case 1:
                                            ui->proteinBox_3->setText(mconvert(pC));
                                            ui->proteinFix3->setChecked(pCheck);
                                            ui->deltaEdit_3a->setText(mconvert(sub));
                                            break;
                                        case 2:
                                            if(sub=="true")
                                                ui->deltaBox_3a->setChecked(true);
                                            else
                                                ui->deltaBox_3a->setChecked(false);
                                            break;
                                        case 3:
                                            ui->deltaEdit_3b->setText(mconvert(sub));
                                            break;
                                        case 4:
                                            if(sub=="true")
                                                ui->deltaBox_3b->setChecked(true);
                                            else
                                                ui->deltaBox_3b->setChecked(false);
                                            break;
                                        case 5:
                                            ui->tmEdit_3a->setText(mconvert(sub));
                                            break;
                                        case 6:
                                            if(sub=="true")
                                                ui->tmBox_3a->setChecked(true);
                                            else
                                                ui->tmBox_3a->setChecked(false);
                                            break;
                                        case 7:
                                            ui->tmEdit_3b->setText(mconvert(sub));
                                            break;
                                        case 8:
                                            if(sub=="true")
                                                ui->tmBox_3b->setChecked(true);
                                            else
                                                ui->tmBox_3b->setChecked(false);
                                            break;
                                        case 9:
                                            ui->cpEdit_3a->setText(mconvert(sub));
                                            break;
                                        case 10:
                                            if(sub=="true")
                                                ui->cpBox_3a->setChecked(true);
                                            else
                                                ui->cpBox_3a->setChecked(false);
                                            break;
                                        case 11:
                                            ui->cpEdit_3b->setText(mconvert(sub));
                                            break;
                                        case 12:
                                            if(sub=="true")
                                                ui->cpBox_3b->setChecked(true);
                                            else
                                                ui->cpBox_3b->setChecked(false);
                                            break;
                                        case 13:
                                            ui->slopeEditN_3->setText(mconvert(sub));
                                            break;
                                        case 14:
                                            if(sub=="true")
                                                ui->slopeBoxN_3->setChecked(true);
                                            else
                                                ui->slopeBoxN_3->setChecked(false);
                                            break;
                                        case 15:
                                            ui->interceptEditN_3->setText(mconvert(sub));
                                            break;
                                        case 16:
                                            if(sub=="true")
                                                ui->interceptBoxN_3->setChecked(true);
                                            else
                                                ui->interceptBoxN_3->setChecked(false);
                                            break;
                                        case 17:
                                            ui->slopeEditI_3->setText(mconvert(sub));
                                            break;
                                        case 18:
                                            if(sub=="true")
                                                ui->slopeBoxI_3->setChecked(true);
                                            else
                                                ui->slopeBoxI_3->setChecked(false);
                                            break;
                                        case 19:
                                            ui->interceptEditI_3->setText(mconvert(sub));
                                            break;
                                        case 20:
                                            if(sub=="true")
                                                ui->interceptBoxI_3->setChecked(true);
                                            else
                                                ui->interceptBoxI_3->setChecked(false);
                                            break;
                                        case 21:
                                            ui->slopeEditD_3->setText(mconvert(sub));
                                            break;
                                        case 22:
                                            if(sub=="true")
                                                ui->slopeBoxD_3->setChecked(true);
                                            else
                                                ui->slopeBoxD_3->setChecked(false);
                                            break;
                                        case 23:
                                            ui->interceptEditD_3->setText(mconvert(sub));
                                            break;
                                        case 24:
                                            if(sub=="true")
                                                ui->interceptBoxD_3->setChecked(true);
                                            else
                                                ui->interceptBoxD_3->setChecked(false);
                                            break;
                                        case 25:
                                            if(sub=="true")
                                                ui->proteinFix3->setChecked(true);
                                            else
                                                ui->proteinFix3->setChecked(false);
                                            break;
                                        }
                                        break;
                                    }
                                    case 4:
                                    {
                                        ui->tabWidget->setCurrentIndex(3);
                                        switch (cc)
                                        {
                                        case 1:
                                            ui->proteinBox_4->setText(mconvert(pC));
                                            ui->proteinFix4->setChecked(pCheck);
                                            ui->deltaEdit_4a->setText(mconvert(sub));
                                            break;
                                        case 2:
                                            if(sub=="true")
                                                ui->deltaBox_4a->setChecked(true);
                                            else
                                                ui->deltaBox_4a->setChecked(false);
                                            break;
                                        case 3:
                                            ui->deltaEdit_4b->setText(mconvert(sub));
                                            break;
                                        case 4:
                                            if(sub=="true")
                                                ui->deltaBox_4b->setChecked(true);
                                            else
                                                ui->deltaBox_4b->setChecked(false);
                                            break;
                                        case 5:
                                            ui->tmEdit_4a->setText(mconvert(sub));
                                            break;
                                        case 6:
                                            if(sub=="true")
                                                ui->tmBox_4a->setChecked(true);
                                            else
                                                ui->tmBox_4a->setChecked(false);
                                            break;
                                        case 7:
                                            ui->tmEdit_4b->setText(mconvert(sub));
                                            break;
                                        case 8:
                                            if(sub=="true")
                                                ui->tmBox_4b->setChecked(true);
                                            else
                                                ui->tmBox_4b->setChecked(false);
                                            break;
                                        case 9:
                                            ui->cpEdit_4a->setText(mconvert(sub));
                                            break;
                                        case 10:
                                            if(sub=="true")
                                                ui->cpBox_4a->setChecked(true);
                                            else
                                                ui->cpBox_4a->setChecked(false);
                                            break;
                                        case 11:
                                            ui->cpEdit_4b->setText(mconvert(sub));
                                            break;
                                        case 12:
                                            if(sub=="true")
                                                ui->cpBox_4b->setChecked(true);
                                            else
                                                ui->cpBox_4b->setChecked(false);
                                            break;
                                        case 13:
                                            ui->slopeEditN_4->setText(mconvert(sub));
                                            break;
                                        case 14:
                                            if(sub=="true")
                                                ui->slopeBoxN_4->setChecked(true);
                                            else
                                                ui->slopeBoxN_4->setChecked(false);
                                            break;
                                        case 15:
                                            ui->interceptEditN_4->setText(mconvert(sub));
                                            break;
                                        case 16:
                                            if(sub=="true")
                                                ui->interceptBoxN_4->setChecked(true);
                                            else
                                                ui->interceptBoxN_4->setChecked(false);
                                            break;
                                        case 17:
                                            ui->slopeEditI_4->setText(mconvert(sub));
                                            break;
                                        case 18:
                                            if(sub=="true")
                                                ui->slopeBoxI_4->setChecked(true);
                                            else
                                                ui->slopeBoxI_4->setChecked(false);
                                            break;
                                        case 19:
                                            ui->interceptEditI_4->setText(mconvert(sub));
                                            break;
                                        case 20:
                                            if(sub=="true")
                                                ui->interceptBoxI_4->setChecked(true);
                                            else
                                                ui->interceptBoxI_4->setChecked(false);
                                            break;
                                        case 21:
                                            ui->slopeEditD_4->setText(mconvert(sub));
                                            break;
                                        case 22:
                                            if(sub=="true")
                                                ui->slopeBoxD_4->setChecked(true);
                                            else
                                                ui->slopeBoxD_4->setChecked(false);
                                            break;
                                        case 23:
                                            ui->interceptEditD_4->setText(mconvert(sub));
                                            break;
                                        case 24:
                                            if(sub=="true")
                                                ui->interceptBoxD_4->setChecked(true);
                                            else
                                                ui->interceptBoxD_4->setChecked(false);
                                            break;
                                        case 25:
                                            if(sub=="true")
                                                ui->proteinFix4->setChecked(true);
                                            else
                                                ui->proteinFix4->setChecked(false);
                                            break;
                                        }
                                        break;
                                    }
                                    case 5:
                                    {
                                        switch (cc)
                                        {
                                        case 1:
                                            ui->deltaEditDiff->setText(mconvert(sub));
                                            break;
                                        case 2:
                                            if(sub=="true")
                                                ui->deltaBoxDiff->setChecked(true);
                                            else
                                                ui->deltaBoxDiff->setChecked(false);
                                            break;
                                        case 3:
                                            ui->tmEditDiff->setText(mconvert(sub));
                                            break;
                                        case 4:
                                            if(sub=="true")
                                                ui->tmBoxDiff->setChecked(true);
                                            else
                                                ui->tmBoxDiff->setChecked(false);
                                            break;
                                        case 5:
                                            ui->aEditDiff->setText(mconvert(sub));
                                            break;
                                        case 6:
                                            if(sub=="true")
                                                ui->aBoxDiff->setChecked(true);
                                            else
                                                ui->aBoxDiff->setChecked(false);
                                            break;
                                        default:
                                            break;
                                        }
                                        break;
                                    }
                                    }
                                    cc++;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    if(found==false)
    {
        bool selected =false;
        for (int i=0; i<ui->CDplot->graphCount(); ++i)
        {
            QCPGraph *graph = ui->CDplot->graph(i);
            QCPPlottableLegendItem *item = ui->CDplot->legend->itemWithPlottable(graph);
            if(i==highlightGraph-1 ||highlightGraph==i)
            {
                if (item->selected())
                {
                    extern int activeGraph;
                    activeGraph=-1;
                    break;
                }
                i++;
            }
            if(i>=ui->CDplot->graphCount())
                break;
            if (item->selected())
            {
                connected=true;
                selected = true;
                graph->setSelected(true);
                item->setSelected(true);
                updateTable(i);
                if(graph->name().contains("(fit:"))
                {
                    QString str = graph->name();
                    extern std::vector< std::vector< std::string> > resultStrVec;
                    for(unsigned int k=0; k<resultStrVec.size(); k++)
                    {
                        if(mconvert(resultStrVec[k][1])==str)
                        {
                            std::istringstream iss(resultStrVec[k][2]);
                            std::string sub;
                            int cc=1;
                            iss >> sub;
                            int model = atoi(sub.c_str());
                            loadLabels(model);
                            fillLabels(k, model);
                            std::string pC;
                            bool pCheck(true);
                            if(model>2 && model !=5)
                            {
                                iss>>sub;
                                pC= sub;
                                iss>>sub;
                                if(sub!="true")
                                    pCheck=false;
                            }
                            while(iss>>sub)
                            {
                                switch(model)
                                {
                                case 1:
                                {
                                    ui->tabWidget->setCurrentIndex(0);
                                    switch (cc)
                                    {
                                    case 1:
                                        ui->deltaEdit->setText(mconvert(sub));
                                        break;
                                    case 2:
                                        if(sub=="true")
                                            ui->deltaBox->setChecked(true);
                                        else
                                            ui->deltaBox->setChecked(false);
                                        break;
                                    case 3:
                                        ui->tmEdit->setText(mconvert(sub));
                                        break;
                                    case 4:
                                        if(sub=="true")
                                            ui->tmBox->setChecked(true);
                                        else
                                            ui->tmBox->setChecked(false);
                                        break;
                                    case 5:
                                        ui->cpEdit->setText(mconvert(sub));
                                        break;
                                    case 6:
                                        if(sub=="true")
                                            ui->cpBox->setChecked(true);
                                        else
                                            ui->cpBox->setChecked(false);
                                        break;
                                    case 7:
                                        ui->slope1Edit->setText(mconvert(sub));
                                        break;
                                    case 8:
                                        if(sub=="true")
                                            ui->slope1Box->setChecked(true);
                                        else
                                            ui->slope1Box->setChecked(false);
                                        break;
                                    case 9:
                                        ui->intercept1Edit->setText(mconvert(sub));
                                        break;
                                    case 10:
                                        if(sub=="true")
                                            ui->intercept1Box->setChecked(true);
                                        else
                                            ui->intercept1Box->setChecked(false);
                                        break;
                                    case 11:
                                        ui->slope2Edit->setText(mconvert(sub));
                                        break;
                                    case 12:
                                        if(sub=="true")
                                            ui->slope2Box->setChecked(true);
                                        else
                                            ui->slope2Box->setChecked(false);
                                        break;
                                    case 13:
                                        ui->intercept2Edit->setText(mconvert(sub));
                                        break;
                                    case 14:
                                        if(sub=="true")
                                            ui->intercept2Box->setChecked(true);
                                        else
                                            ui->intercept2Box->setChecked(false);
                                        break;
                                    }
                                    break;
                                }
                                case 2:
                                {
                                    ui->tabWidget->setCurrentIndex(1);
                                    switch (cc)
                                    {
                                    case 1:
                                        ui->deltaEdit_2a->setText(mconvert(sub));
                                        break;
                                    case 2:
                                        if(sub=="true")
                                            ui->deltaBox_2a->setChecked(true);
                                        else
                                            ui->deltaBox_2a->setChecked(false);
                                        break;
                                    case 3:
                                        ui->deltaEdit_2b->setText(mconvert(sub));
                                        break;
                                    case 4:
                                        if(sub=="true")
                                            ui->deltaBox_2b->setChecked(true);
                                        else
                                            ui->deltaBox_2b->setChecked(false);
                                        break;
                                    case 5:
                                        ui->tmEdit_2a->setText(mconvert(sub));
                                        break;
                                    case 6:
                                        if(sub=="true")
                                            ui->tmBox_2a->setChecked(true);
                                        else
                                            ui->tmBox_2a->setChecked(false);
                                        break;
                                    case 7:
                                        ui->tmEdit_2b->setText(mconvert(sub));
                                        break;
                                    case 8:
                                        if(sub=="true")
                                            ui->tmBox_2b->setChecked(true);
                                        else
                                            ui->tmBox_2b->setChecked(false);
                                        break;
                                    case 9:
                                        ui->cpEdit_2a->setText(mconvert(sub));
                                        break;
                                    case 10:
                                        if(sub=="true")
                                            ui->cpBox_2a->setChecked(true);
                                        else
                                            ui->cpBox_2a->setChecked(false);
                                        break;
                                    case 11:
                                        if(chemical)
                                            ui->proteinBoxChemical->setText(mconvert(sub));
                                        else
                                            ui->cpEdit_2b->setText(mconvert(sub));
                                        break;
                                    case 12:
                                        if(chemical)
                                        {
                                            if(sub=="true")
                                                ui->proteinFixChemical->setChecked(true);
                                            else
                                                ui->proteinFixChemical->setChecked(false);
                                        }
                                        else
                                        {
                                            if(sub=="true")
                                                ui->cpBox_2b->setChecked(true);
                                            else
                                                ui->cpBox_2b->setChecked(false);
                                        }
                                        break;
                                    case 13:
                                        ui->slopeEditN_2->setText(mconvert(sub));
                                        break;
                                    case 14:
                                        if(sub=="true")
                                            ui->slopeBoxN_2->setChecked(true);
                                        else
                                            ui->slopeBoxN_2->setChecked(false);
                                        break;
                                    case 15:
                                        ui->interceptEditN_2->setText(mconvert(sub));
                                        break;
                                    case 16:
                                        if(sub=="true")
                                            ui->interceptBoxN_2->setChecked(true);
                                        else
                                            ui->interceptBoxN_2->setChecked(false);
                                        break;
                                    case 17:
                                        ui->slopeEditI_2->setText(mconvert(sub));
                                        break;
                                    case 18:
                                        if(sub=="true")
                                            ui->slopeBoxI_2->setChecked(true);
                                        else
                                            ui->slopeBoxI_2->setChecked(false);
                                        break;
                                    case 19:
                                        ui->interceptEditI_2->setText(mconvert(sub));
                                        break;
                                    case 20:
                                        if(sub=="true")
                                            ui->interceptBoxI_2->setChecked(true);
                                        else
                                            ui->interceptBoxI_2->setChecked(false);
                                        break;
                                    case 21:
                                        ui->slopeEditD_2->setText(mconvert(sub));
                                        break;
                                    case 22:
                                        if(sub=="true")
                                            ui->slopeBoxD_2->setChecked(true);
                                        else
                                            ui->slopeBoxD_2->setChecked(false);
                                        break;
                                    case 23:
                                        ui->interceptEditD_2->setText(mconvert(sub));
                                        break;
                                    case 24:
                                        if(sub=="true")
                                            ui->interceptBoxD_2->setChecked(true);
                                        else
                                            ui->interceptBoxD_2->setChecked(false);
                                        break;
                                    }
                                    break;
                                }
                                case 3:
                                {
                                    ui->tabWidget->setCurrentIndex(2);
                                    switch (cc)
                                    {
                                    case 1:
                                        ui->proteinBox_3->setText(mconvert(pC));
                                        ui->proteinFix3->setChecked(pCheck);
                                        ui->deltaEdit_3a->setText(mconvert(sub));
                                        break;
                                    case 2:
                                        if(sub=="true")
                                            ui->deltaBox_3a->setChecked(true);
                                        else
                                            ui->deltaBox_3a->setChecked(false);
                                        break;
                                    case 3:
                                        ui->deltaEdit_3b->setText(mconvert(sub));
                                        break;
                                    case 4:
                                        if(sub=="true")
                                            ui->deltaBox_3b->setChecked(true);
                                        else
                                            ui->deltaBox_3b->setChecked(false);
                                        break;
                                    case 5:
                                        ui->tmEdit_3a->setText(mconvert(sub));
                                        break;
                                    case 6:
                                        if(sub=="true")
                                            ui->tmBox_3a->setChecked(true);
                                        else
                                            ui->tmBox_3a->setChecked(false);
                                        break;
                                    case 7:
                                        ui->tmEdit_3b->setText(mconvert(sub));
                                        break;
                                    case 8:
                                        if(sub=="true")
                                            ui->tmBox_3b->setChecked(true);
                                        else
                                            ui->tmBox_3b->setChecked(false);
                                        break;
                                    case 9:
                                        ui->cpEdit_3a->setText(mconvert(sub));
                                        break;
                                    case 10:
                                        if(sub=="true")
                                            ui->cpBox_3a->setChecked(true);
                                        else
                                            ui->cpBox_3a->setChecked(false);
                                        break;
                                    case 11:
                                        ui->cpEdit_3b->setText(mconvert(sub));
                                        break;
                                    case 12:
                                        if(sub=="true")
                                            ui->cpBox_3b->setChecked(true);
                                        else
                                            ui->cpBox_3b->setChecked(false);
                                        break;
                                    case 13:
                                        ui->slopeEditN_3->setText(mconvert(sub));
                                        break;
                                    case 14:
                                        if(sub=="true")
                                            ui->slopeBoxN_3->setChecked(true);
                                        else
                                            ui->slopeBoxN_3->setChecked(false);
                                        break;
                                    case 15:
                                        ui->interceptEditN_3->setText(mconvert(sub));
                                        break;
                                    case 16:
                                        if(sub=="true")
                                            ui->interceptBoxN_3->setChecked(true);
                                        else
                                            ui->interceptBoxN_3->setChecked(false);
                                        break;
                                    case 17:
                                        ui->slopeEditI_3->setText(mconvert(sub));
                                        break;
                                    case 18:
                                        if(sub=="true")
                                            ui->slopeBoxI_3->setChecked(true);
                                        else
                                            ui->slopeBoxI_3->setChecked(false);
                                        break;
                                    case 19:
                                        ui->interceptEditI_3->setText(mconvert(sub));
                                        break;
                                    case 20:
                                        if(sub=="true")
                                            ui->interceptBoxI_3->setChecked(true);
                                        else
                                            ui->interceptBoxI_3->setChecked(false);
                                        break;
                                    case 21:
                                        ui->slopeEditD_3->setText(mconvert(sub));
                                        break;
                                    case 22:
                                        if(sub=="true")
                                            ui->slopeBoxD_3->setChecked(true);
                                        else
                                            ui->slopeBoxD_3->setChecked(false);
                                        break;
                                    case 23:
                                        ui->interceptEditD_3->setText(mconvert(sub));
                                        break;
                                    case 24:
                                        if(sub=="true")
                                            ui->interceptBoxD_3->setChecked(true);
                                        else
                                            ui->interceptBoxD_3->setChecked(false);
                                        break;
                                    }
                                    break;
                                }
                                case 4:
                                {
                                    ui->tabWidget->setCurrentIndex(3);
                                    switch (cc)
                                    {
                                    case 1:
                                        ui->proteinBox_4->setText(mconvert(pC));
                                        ui->proteinFix4->setChecked(pCheck);
                                        ui->deltaEdit_4a->setText(mconvert(sub));
                                        break;
                                    case 2:
                                        if(sub=="true")
                                            ui->deltaBox_4a->setChecked(true);
                                        else
                                            ui->deltaBox_4a->setChecked(false);
                                        break;
                                    case 3:
                                        ui->deltaEdit_4b->setText(mconvert(sub));
                                        break;
                                    case 4:
                                        if(sub=="true")
                                            ui->deltaBox_4b->setChecked(true);
                                        else
                                            ui->deltaBox_4b->setChecked(false);
                                        break;
                                    case 5:
                                        ui->tmEdit_4a->setText(mconvert(sub));
                                        break;
                                    case 6:
                                        if(sub=="true")
                                            ui->tmBox_4a->setChecked(true);
                                        else
                                            ui->tmBox_4a->setChecked(false);
                                        break;
                                    case 7:
                                        ui->tmEdit_4b->setText(mconvert(sub));
                                        break;
                                    case 8:
                                        if(sub=="true")
                                            ui->tmBox_4b->setChecked(true);
                                        else
                                            ui->tmBox_4b->setChecked(false);
                                        break;
                                    case 9:
                                        ui->cpEdit_4a->setText(mconvert(sub));
                                        break;
                                    case 10:
                                        if(sub=="true")
                                            ui->cpBox_4a->setChecked(true);
                                        else
                                            ui->cpBox_4a->setChecked(false);
                                        break;
                                    case 11:
                                        ui->cpEdit_4b->setText(mconvert(sub));
                                        break;
                                    case 12:
                                        if(sub=="true")
                                            ui->cpBox_4b->setChecked(true);
                                        else
                                            ui->cpBox_4b->setChecked(false);
                                        break;
                                    case 13:
                                        ui->slopeEditN_4->setText(mconvert(sub));
                                        break;
                                    case 14:
                                        if(sub=="true")
                                            ui->slopeBoxN_4->setChecked(true);
                                        else
                                            ui->slopeBoxN_4->setChecked(false);
                                        break;
                                    case 15:
                                        ui->interceptEditN_4->setText(mconvert(sub));
                                        break;
                                    case 16:
                                        if(sub=="true")
                                            ui->interceptBoxN_4->setChecked(true);
                                        else
                                            ui->interceptBoxN_4->setChecked(false);
                                        break;
                                    case 17:
                                        ui->slopeEditI_4->setText(mconvert(sub));
                                        break;
                                    case 18:
                                        if(sub=="true")
                                            ui->slopeBoxI_4->setChecked(true);
                                        else
                                            ui->slopeBoxI_4->setChecked(false);
                                        break;
                                    case 19:
                                        ui->interceptEditI_4->setText(mconvert(sub));
                                        break;
                                    case 20:
                                        if(sub=="true")
                                            ui->interceptBoxI_4->setChecked(true);
                                        else
                                            ui->interceptBoxI_4->setChecked(false);
                                        break;
                                    case 21:
                                        ui->slopeEditD_4->setText(mconvert(sub));
                                        break;
                                    case 22:
                                        if(sub=="true")
                                            ui->slopeBoxD_4->setChecked(true);
                                        else
                                            ui->slopeBoxD_4->setChecked(false);
                                        break;
                                    case 23:
                                        ui->interceptEditD_4->setText(mconvert(sub));
                                        break;
                                    case 24:
                                        if(sub=="true")
                                            ui->interceptBoxD_4->setChecked(true);
                                        else
                                            ui->interceptBoxD_4->setChecked(false);
                                        break;
                                    }
                                    break;
                                }
                                case 5:
                                {
                                    switch (cc)
                                    {
                                    case 1:
                                        ui->deltaEditDiff->setText(mconvert(sub));
                                        break;
                                    case 2:
                                        if(sub=="true")
                                            ui->deltaBoxDiff->setChecked(true);
                                        else
                                            ui->deltaBoxDiff->setChecked(false);
                                        break;
                                    case 3:
                                        ui->tmEditDiff->setText(mconvert(sub));
                                        break;
                                    case 4:
                                        if(sub=="true")
                                            ui->tmBoxDiff->setChecked(true);
                                        else
                                            ui->tmBoxDiff->setChecked(false);
                                        break;
                                    case 5:
                                        ui->aEditDiff->setText(mconvert(sub));
                                        break;
                                    case 6:
                                        if(sub=="true")
                                            ui->aBoxDiff->setChecked(true);
                                        else
                                            ui->aBoxDiff->setChecked(false);
                                        break;
                                    default:
                                        break;
                                    }
                                    break;
                                }
                                }
                                cc++;
                            }
                            break;
                        }
                    }
                }
                break;
            }
            else
            {
                updateTable(ui->CDplot->graphCount()-1);

            }
        }
        if(selected==false)
        {
            disconnect(ui->actionColor,SIGNAL(triggered()),this,SLOT(colorGraph()));
            disconnect(ui->actionChange_style,SIGNAL(triggered()),this,SLOT(changeOrnament()));
            disconnect(ui->actionChange_pen_width,SIGNAL(triggered()),this,SLOT(changeWidth()));
            ui->actionChange_style->setDisabled(true);
            ui->actionChange_pen_width->setDisabled(true);
            ui->actionColor->setDisabled(true);
            disconnect(ui->actionDelete_graph,SIGNAL(triggered()),this,SLOT(removeSelectedGraph()));
            ui->actionDelete_graph->setDisabled(true);
            updateTable(ui->CDplot->graphCount()-1);
        }
    }
    for(int i=0; i<ui->CDplot->graphCount(); i++)
    {
        if(ui->CDplot->graph(i)->selected() && i<ui->graphBox->count())
        {
            ui->graphBox->setCurrentIndex(i);
            ui->graphBox_2->setCurrentIndex(i);
            ui->graphBox_3->setCurrentIndex(i);
            ui->graphBox_4->setCurrentIndex(i);
            ui->graphBoxDiff->setCurrentIndex(i);
        }
    }
    if(connected)
    {
        disconnect(ui->actionColor,SIGNAL(triggered()),this,SLOT(colorGraph()));
        disconnect(ui->actionChange_style,SIGNAL(triggered()),this,SLOT(changeOrnament()));
        disconnect(ui->actionChange_pen_width,SIGNAL(triggered()),this,SLOT(changeWidth()));
        ui->actionChange_style->setDisabled(true);
        ui->actionChange_pen_width->setDisabled(true);
        ui->actionColor->setDisabled(true);
        disconnect(ui->actionDelete_graph,SIGNAL(triggered()),this,SLOT(removeSelectedGraph()));
        ui->actionDelete_graph->setDisabled(true);
        connect(ui->actionColor,SIGNAL(triggered()),this,SLOT(colorGraph()));
        ui->actionColor->setEnabled(true);
        connect(ui->actionChange_style,SIGNAL(triggered()),this,SLOT(changeOrnament()));
        connect(ui->actionChange_pen_width,SIGNAL(triggered()),this,SLOT(changeWidth()));
        ui->actionChange_style->setEnabled(true);
        ui->actionChange_pen_width->setEnabled(true);
        connect(ui->actionDelete_graph,SIGNAL(triggered()),this,SLOT(removeSelectedGraph()));
        ui->actionDelete_graph->setEnabled(true);
        ui->actionDelete_all_graphs->setEnabled(true);
        ui->actionDelete_fitted_graphs->setEnabled(true);
    }
}

void CDpal::updateTable(int graphNo)
{
    disconnect(ui->table, SIGNAL(itemSelectionChanged()), this, SLOT(highlight()));
    if(ui->CDplot->selectedGraphs().count() != 0)
    {
        extern int activeGraph;
        activeGraph=graphNo;
        QString label="Dataset: ";
        label+=ui->CDplot->graph(activeGraph)->name();
        ui->activeLabel->setText(label);
        ui->activeLabel->setFont (QFont ("Verdana", 8));
#ifdef Q_OS_MAC
        ui->activeLabel->setFont(QFont( "Arial", 12));
#endif
        ui->table->setRowCount(0);
        ui->table->setColumnCount(0);
        const QCPDataMap *dataMap = ui->CDplot->graph(graphNo)->data();
        QMap<double, QCPData>::const_iterator j = dataMap->constBegin();
        while (j != dataMap->constEnd())
        {
            if(j.value().valueErrorPlus!=0)
            {
                ui->table->setColumnCount(3);
                break;
            }
            j++;
        }
        if(ui->table->columnCount()==0)
            ui->table->setColumnCount(2);
        QMap<double, QCPData>::const_iterator i = dataMap->constBegin();
        while (i != dataMap->constEnd())
        {
            ui->table->insertRow(ui->table->rowCount());

            QString str = QString::number(i.value().key);
            QTableWidgetItem *item;
            item = new QTableWidgetItem;
            item->setText(str);
            ui->table->setItem(ui->table->rowCount()-1,0,item);
            str = QString::number(i.value().value);
            item = new QTableWidgetItem;
            item->setText(str);
            ui->table->setItem(ui->table->rowCount()-1,1,item);
            if(ui->table->columnCount()==3)
            {
                str = QString::number(i.value().valueErrorPlus);
                item = new QTableWidgetItem;
                item->setText(str);
                ui->table->setItem(ui->table->rowCount()-1,2,item);
            }
            i++;
        }
        ui->table->setHorizontalHeaderItem(0,new QTableWidgetItem(ui->CDplot->xAxis->label()));
        ui->table->setHorizontalHeaderItem(1,new QTableWidgetItem(ui->CDplot->yAxis->label()));
        if(ui->table->columnCount()==3)
        {
            QString str = ui->CDplot->yAxis->label();
            str+= " Err";
            ui->table->setHorizontalHeaderItem(2,new QTableWidgetItem(str));
        }
        ui->table->horizontalHeader()->setStretchLastSection(true);
    }
    else
    {
        ui->table->setRowCount(0);
        ui->table->setColumnCount(0);
        extern int activeGraph;
        activeGraph=-1;
    }
    connect(ui->table, SIGNAL(itemSelectionChanged()), this, SLOT(highlight()));
}

void CDpal::mousePress()
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if (ui->CDplot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->CDplot->axisRect()->setRangeDrag(ui->CDplot->xAxis->orientation());
    else if (ui->CDplot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->CDplot->axisRect()->setRangeDrag(ui->CDplot->yAxis->orientation());
    else
        ui->CDplot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void CDpal::mouseWheel()
{
    // if an axis is selected, only allow the direction of that axis to be zoomed
    // if no axis is selected, both directions may be zoomed

    if (ui->CDplot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->CDplot->axisRect()->setRangeZoom(ui->CDplot->xAxis->orientation());
    else if (ui->CDplot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->CDplot->axisRect()->setRangeZoom(ui->CDplot->yAxis->orientation());
    else
        ui->CDplot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void CDpal::removeSelectedGraph()
{
    extern int activeGraph;
    extern int highlightGraph;
    if(activeGraph!=-1)
    {
        QMessageBox msgBox;
        msgBox.setText("Remove the selected graph and all its data?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Cancel);
        qApp->setQuitOnLastWindowClosed(false);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Ok:
        {
            if (ui->CDplot->selectedGraphs().size() > 0)
            {
                ui->CDplot->removeGraph(ui->CDplot->selectedGraphs().first());
                ui->CDplot->replot();
            }
            if(ui->CDplot->graphCount()==0)
            {
                ui->graphBox->clear();
                ui->graphBox_2->clear();
                ui->graphBox_3->clear();
                ui->graphBox_4->clear();
                ui->graphBoxDiff->clear();
            }
            for(int j=0; j<ui->CDplot->graphCount(); j++)
            {
                if(ui->CDplot->graph(j)->name()!=ui->graphBox->itemText(j))
                {
                    ui->graphBox->removeItem(j);
                    ui->graphBox_2->removeItem(j);
                    ui->graphBox_3->removeItem(j);
                    ui->graphBox_4->removeItem(j);
                    ui->graphBoxDiff->removeItem(j);
                    break;
                }
                else if(j==ui->CDplot->graphCount()-1 && ui->graphBox->count()>ui->CDplot->graphCount())
                {
                    ui->graphBox->removeItem(j+1);
                    ui->graphBox_2->removeItem(j+1);
                    ui->graphBox_3->removeItem(j+1);
                    ui->graphBox_4->removeItem(j+1);
                    ui->graphBoxDiff->removeItem(j+1);
                }
            }
            if(activeGraph<highlightGraph-1 && highlightGraph!=-1)
                ui->CDplot->removeGraph(highlightGraph-2);
            else if(highlightGraph!=-1)
                ui->CDplot->removeGraph(highlightGraph-1);
            highlightGraph=-1;
            ui->CDplot->replot();
            updateTable(0);
            extern std::vector< std::vector< std::string> > resultStrVec;
            extern std::vector< std::vector< std::string> > rV2;
            for(unsigned int i=0; i<resultStrVec.size();i++)
                for(int j=0; j<ui->CDplot->graphCount(); j++)
                {
                    if(ui->CDplot->graph(j)->name()==mconvert(resultStrVec[i][1]))
                        break;
                    else if(j==ui->CDplot->graphCount()-1)
                    {
                        resultStrVec[i].erase(resultStrVec[i].begin() + i);
                        rV2[i].erase(rV2[i].begin() + i);
                    }
                }
            //Disables functions if no data is present
            if(ui->CDplot->graphCount()==0)
            {
                ui->fitDiff->setEnabled(false);
                ui->autofitAllDiff->setEnabled(false);
                ui->autoFitDiff->setEnabled(false);
                disconnect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
                disconnect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
                disconnect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
                disconnect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
                disconnect(ui->actionFit,SIGNAL(triggered()),this,SLOT(fitData()));
                disconnect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveResults()));
                disconnect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
                disconnect(ui->actionDelete_graph,SIGNAL(triggered()),this,SLOT(removeSelectedGraph()));
                disconnect(ui->actionDelete_all_graphs,SIGNAL(triggered()),this,SLOT(removeAllGraphs()));
                disconnect(ui->actionDelete_fitted_graphs,SIGNAL(triggered()),this,SLOT(removeFittedGraphs()));
                disconnect(ui->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
                disconnect(ui->actionLoad_style_preset_2, SIGNAL(triggered()), this, SLOT(loadStyle()));
                disconnect(ui->actionSave_style_preset, SIGNAL(triggered()), this, SLOT(saveStyle()));
                ui->actionSave_Project->setDisabled(true);
                ui->actionLoad_style_preset_2->setDisabled(true);
                ui->actionSave_style_preset->setDisabled(true);
                ui->actionDelete_graph->setDisabled(true);
                ui->actionDelete_all_graphs->setDisabled(true);
                ui->actionDelete_fitted_graphs->setDisabled(true);
                disconnect(ui->actionColor,SIGNAL(triggered()),this,SLOT(colorGraph()));
                disconnect(ui->actionChange_style,SIGNAL(triggered()),this,SLOT(changeOrnament()));
                disconnect(ui->actionChange_pen_width,SIGNAL(triggered()),this,SLOT(changeWidth()));
                disconnect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
                disconnect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
                ui->fitButton->setDisabled(true);
                ui->fitButton_2->setDisabled(true);
                ui->fitButton_3->setDisabled(true);
                ui->fitButton_4->setDisabled(true);
                ui->actionSave->setDisabled(true);
                ui->actionColor->setDisabled(true);
                ui->actionExport_data->setDisabled(true);
                ui->actionChange_style->setDisabled(true);
                ui->actionChange_pen_width->setDisabled(true);
                disconnect(ui->actionF_test, SIGNAL(triggered()), this, SLOT(fTest()));
            }

            break;
        }
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
        qApp->setQuitOnLastWindowClosed(true);
    }
}

void CDpal::removeFittedGraphs()
{
    QMessageBox msgBox;
    msgBox.setText("Remove all fitted graphs and their data?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    qApp->setQuitOnLastWindowClosed(false);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Ok:
    {
        for(int i=0; i<ui->CDplot->graphCount();i++)
        {
            QString str= ui->CDplot->graph(i)->name();
            if(str.length()>4)
                for(int j=0; j<str.length()-4; j++)
                {
                    if(str[j]=='(' && str[j+1]=='f' && str[j+2]=='i' && str[j+3]=='t' && str[j+4]==':')
                    {
                        ui->CDplot->removeGraph(i);
                        ui->graphBox->removeItem(i);
                        ui->graphBox_2->removeItem(i);
                        ui->graphBox_3->removeItem(i);
                        ui->graphBox_4->removeItem(i);
                        ui->graphBoxDiff->removeItem(i);
                        i--;
                        break;
                    }
                }
        }
        ui->CDplot->replot();
        updateTable(0);
        extern std::vector< std::vector< std::string> > resultStrVec;
        resultStrVec.clear();
        extern std::vector< std::vector< std::string> > rV2;
        rV2.clear();
        clearResults();
        removeHighlight();
        //Disables functions when no data is present
        if(ui->CDplot->graphCount()==0)
        {
            disconnect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
            disconnect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
            disconnect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
            disconnect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
            disconnect(ui->actionFit,SIGNAL(triggered()),this,SLOT(fitData()));
            disconnect(ui->actionSave,SIGNAL(triggered()),this,SLOT(saveData()));
            disconnect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
            disconnect(ui->actionDelete_graph,SIGNAL(triggered()),this,SLOT(removeSelectedGraph()));
            disconnect(ui->actionDelete_all_graphs,SIGNAL(triggered()),this,SLOT(removeAllGraphs()));
            disconnect(ui->actionDelete_fitted_graphs,SIGNAL(triggered()),this,SLOT(removeFittedGraphs()));
            disconnect(ui->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
            disconnect(ui->actionLoad_style_preset_2, SIGNAL(triggered()), this, SLOT(loadStyle()));
            disconnect(ui->actionSave_style_preset, SIGNAL(triggered()), this, SLOT(saveStyle()));
            ui->actionSave_Project->setDisabled(true);
            ui->actionLoad_style_preset_2->setDisabled(true);
            ui->actionSave_style_preset->setDisabled(true);
            ui->actionDelete_graph->setDisabled(true);
            ui->actionDelete_all_graphs->setDisabled(true);
            ui->actionDelete_fitted_graphs->setDisabled(true);
            disconnect(ui->actionColor,SIGNAL(triggered()),this,SLOT(colorGraph()));
            disconnect(ui->actionChange_style,SIGNAL(triggered()),this,SLOT(changeOrnament()));
            disconnect(ui->actionChange_pen_width,SIGNAL(triggered()),this,SLOT(changeWidth()));
            disconnect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
            disconnect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
            ui->actionColor->setDisabled(true);
            ui->fitButton->setDisabled(true);
            ui->fitButton_2->setDisabled(true);
            ui->fitButton_3->setDisabled(true);
            ui->fitButton_4->setDisabled(true);
            ui->actionSave->setDisabled(true);
            ui->actionExport_data->setDisabled(true);
            ui->actionChange_style->setDisabled(true);
            ui->actionChange_pen_width->setDisabled(true);
            ui->graphBox->clear();
            ui->graphBox_2->clear();
            ui->graphBox_3->clear();
            ui->graphBox_4->clear();
            ui->graphBoxDiff->clear();
            ui->fitDiff->setEnabled(false);
            ui->autofitAllDiff->setEnabled(false);
            ui->autoFitDiff->setEnabled(false);
        }
        break;
    }
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }
    qApp->setQuitOnLastWindowClosed(true);
}

void CDpal::removeAllGraphs()
{
    QMessageBox msgBox;
    msgBox.setText("Remove all graphs and their data?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    qApp->setQuitOnLastWindowClosed(false);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Ok:
    {
        ui->CDplot->clearGraphs();
        ui->CDplot->replot();
        updateTable(0);
        clearResults();
        extern std::vector< std::vector< std::string> > rV2;
        extern std::vector< std::vector< std::string> > resultStrVec;
        resultStrVec.clear();
        rV2.clear();
        //Disables functions when no data is present
        disconnect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
        disconnect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
        disconnect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
        disconnect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
        disconnect(ui->actionFit,SIGNAL(triggered()),this,SLOT(fitData()));
        disconnect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveResults()));
        disconnect(ui->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
        disconnect(ui->actionSave_style_preset, SIGNAL(triggered()), this, SLOT(saveStyle()));
        disconnect(ui->actionLoad_style_preset_2, SIGNAL(triggered()), this, SLOT(loadStyle()));
        ui->actionSave_Project->setDisabled(true);
        ui->actionSave_style_preset->setDisabled(true);
        ui->actionLoad_style_preset_2->setDisabled(true);
        disconnect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
        disconnect(ui->actionDelete_graph,SIGNAL(triggered()),this,SLOT(removeSelectedGraph()));
        disconnect(ui->actionDelete_all_graphs,SIGNAL(triggered()),this,SLOT(removeAllGraphs()));
        disconnect(ui->actionDelete_fitted_graphs,SIGNAL(triggered()),this,SLOT(removeFittedGraphs()));
        ui->actionDelete_graph->setDisabled(true);
        ui->actionDelete_all_graphs->setDisabled(true);
        ui->actionDelete_fitted_graphs->setDisabled(true);
        disconnect(ui->actionColor,SIGNAL(triggered()),this,SLOT(colorGraph()));
        disconnect(ui->actionChange_style,SIGNAL(triggered()),this,SLOT(changeOrnament()));
        disconnect(ui->actionChange_pen_width,SIGNAL(triggered()),this,SLOT(changeWidth()));
        disconnect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
        disconnect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
        ui->actionColor->setDisabled(true);
        ui->fitButton->setDisabled(true);
        ui->fitButton_2->setDisabled(true);
        ui->fitButton_3->setDisabled(true);
        ui->fitButton_4->setDisabled(true);
        ui->actionSave->setDisabled(true);
        ui->actionExport_data->setDisabled(true);
        ui->actionChange_style->setDisabled(true);
        ui->actionChange_pen_width->setDisabled(true);
        ui->graphBox->clear();
        ui->graphBox_2->clear();
        ui->graphBox_3->clear();
        ui->graphBox_4->clear();
        ui->graphBoxDiff->clear();
        ui->fitDiff->setEnabled(false);
        ui->autofitAllDiff->setEnabled(false);
        ui->autoFitDiff->setEnabled(false);
        disconnect(ui->actionF_test, SIGNAL(triggered()), this, SLOT(fTest()));
        //
        break;
    }
    case QMessageBox::Cancel:
        break;
    default:
        break;
    }
    qApp->setQuitOnLastWindowClosed(true);
}

void CDpal::contextMenuRequest(QPoint pos)
{
    QMenu *menu = new QMenu(this);
    menu->setAttribute(Qt::WA_DeleteOnClose);

    if (ui->CDplot->legend->selectTest(pos, false) >= 0) // context menu on legend requested
    {
        menu->addAction("Move to top left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignLeft));
        menu->addAction("Move to top center", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignHCenter));
        menu->addAction("Move to top right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignTop|Qt::AlignRight));
        menu->addAction("Move to bottom right", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignRight));
        menu->addAction("Move to bottom left", this, SLOT(moveLegend()))->setData((int)(Qt::AlignBottom|Qt::AlignLeft));
    } else  // general context menu on graphs requested
    {
        if (ui->CDplot->selectedPlottables().size() > 0)
            menu->addAction("Remove selected graph", this, SLOT(removeSelectedGraph()));
        if (ui->CDplot->graphCount() > 1)
            menu->addAction("Merge graphs into one dataset", this, SLOT(mergeGraphs()));
        if (ui->CDplot->graphCount() > 0)
            menu->addAction("Remove all graphs", this, SLOT(removeAllGraphs()));
        if (ui->CDplot->graphCount() > 0)
            menu->addAction("Remove all fitted graphs", this, SLOT(removeFittedGraphs()));
    }

    menu->popup(ui->CDplot->mapToGlobal(pos));
}

void CDpal::moveLegend()
{
    if (QAction* contextAction = qobject_cast<QAction*>(sender())) // make sure this slot is really called by a context menu action, so it carries the data we need
    {
        bool ok;
        int dataInt = contextAction->data().toInt(&ok);
        if (ok)
        {
            ui->CDplot->axisRect()->insetLayout()->setInsetAlignment(0, (Qt::Alignment)dataInt);
            ui->CDplot->replot();
        }
    }
}

void CDpal::graphClicked(QCPAbstractPlottable *plottable)
{
    ui->statusbar->showMessage(QString("Clicked on graph '%1'.").arg(plottable->name()), 1000);
}

QPen CDpal::changePen(QPen pen, int i)
{
    switch(i)
    {
    case 0: pen.setColor("black");
        break;
    case 1: pen.setColor("red");
        break;
    case 2: pen.setColor("green");
        break;
    case 3: pen.setColor("blue");
        break;
    case 4: pen.setColor("brown");
        break;
    }

    return pen;
}

CDpal::~CDpal()
{
    delete ui;
}

void CDpal::highlight()
{
    {
        extern int activeGraph;
        extern int highlightGraph;
        if(highlightGraph!=-1)
            ui->CDplot->removeGraph(highlightGraph-1);
        if(activeGraph==ui->CDplot->graphCount())
            activeGraph--;
        if(activeGraph!=-1)
        {
            const QCPDataMap *dataMap = ui->CDplot->graph(activeGraph)->data();
            QMap<double, QCPData>::const_iterator j = dataMap->constBegin();
            QVector<double> x, y, yerr;
            for(short s=0; s < ui->table->rowCount(); s++)
            {
                if(ui->table->item(s,0)->isSelected())
                {
                    x.push_back(j.value().key);
                    y.push_back(j.value().value);
                    if(ui->table->columnCount()==3)
                        yerr.push_back(j.value().valueErrorPlus);
                }
                j++;
            }
            ui->CDplot->addGraph();
            QPen pen;
            pen.setColor(QColor(200,0,0));
            ui->CDplot->graph()->setPen(pen);
            QVector<QCPScatterStyle::ScatterShape> shapes;
            shapes << QCPScatterStyle::ssCustom;
            if(ui->table->columnCount()==2)
                ui->CDplot->graph()->setData(x, y);
            else if(ui->table->columnCount()==3)
                ui->CDplot->graph()->setDataValueError(x, y, yerr);
            QString str = "Selected: ";
            str+=ui->CDplot->graph(activeGraph)->name();
            ui->CDplot->graph()->setName(str);
            ui->CDplot->graph()->setLineStyle(QCPGraph::lsNone);
            if(ui->table->columnCount()==3)
            {
                ui->CDplot->graph()->setErrorType(QCPGraph::etValue);
                ui->CDplot->graph()->setErrorPen(pen);
            }
            QPainterPath customScatterPath;
            for (int i=0; i<6; ++i)
                customScatterPath.cubicTo(qCos(2*M_PI*i/6.0)*9, qSin(2*M_PI*i/6.0)*9, qCos(2*M_PI*(i+0.9)/6.0)*9, qSin(2*M_PI*(i+0.9)/6.0)*9, 0, 0);
            ui->CDplot->graph()->setScatterStyle(QCPScatterStyle(customScatterPath, QPen(), QColor(40, 70, 255, 50), 10));

            ui->statusbar->clearMessage();
            ui->CDplot->replot();
            highlightGraph = ui->CDplot->graphCount();
        }
    }
}

QString CDpal::checkFormat(std::string f)
{
    //Check input data format
    std::ifstream file;
    file.open(f.c_str(), std::ios::in);
    std::string line;
    bool passed =false;
    while(getline(file, line))
    {
        if(line=="CircularDichroism")
        {
            passed=true;
            break;
        }
    }
    if(passed)
    {
        passed=false;
        int j=0;
        while(getline(file, line))
        {
            j++;
            if(j==2)
            {
                passed=true;
                break;
            }
        }
        if(passed)
        {
            int i=0;
            while(getline(file, line))
            {
                i++;
                std::istringstream iss(line);
                std::string sub;
                while(iss >> sub)
                {
                    QString str = mconvert(sub);
                    bool isNumeric = false;
                    str.toDouble(&isNumeric);
                    if(!isNumeric)
                    {
                        passed=false;
                        break;
                    }
                }
            }
            if(i==0)
                passed=false;
        }
    }
    file.clear();
    file.close();
    if(!passed)
        return "The submitted file is not of a correct format. Aborting.";
    else
        return "";
}

QString CDpal::checkCustomFormat(std::string f, int h, int c, int t, int sr, int pb, QString text)
{
    Q_UNUSED(c);
    Q_UNUSED(t);
    //Check custom data format
    std::ifstream file;
    file.open(f.c_str(), std::ios::in);
    std::string line;
    bool passed =false;
    QString err("");
    int hC=0, skipCounter=0;

    if(text!="EMPTY")
    {
        while(getline(file, line))
        {
            if(pb==1)
            {
                if(line==mconvert(text))
                {
                    if(skipCounter==sr)
                    {
                        passed=true;
                        break;
                    }
                    skipCounter++;
                }
            }
            else
            {
                std::stringstream iss(line);
                std::string sub;
                iss >> sub;
                if(sub==mconvert(text))
                {
                    if(skipCounter==sr)
                    {
                        passed=true;
                        break;
                    }
                    skipCounter++;
                }
            }
        }
    }
    else
        passed=true;
    if(passed)
    {
        passed =false;
        if(h>0)
            while(getline(file, line))
            {
                hC++;
                if(hC==h)
                {
                    passed=true;
                    break;
                }
            }
        else
            passed=true;
        if(!passed)
            err="Number of header lines exceed file size. Aborting.";
    }
    else
    {
        QString number = QString::number(sr+1);
        err="Could not find \""+text+"\" "+number+" time(s) in the submitted file. Aborting.";
    }
    file.clear();
    file.close();
    return err;
}

void CDpal::AutofitAll()
{
    int type;
    if(ui->actionND->isChecked())
        type=1;
    else if(ui->actionNID->isChecked())
        type=2;
    else
        type=3;
    disconnect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
    if(ui->graphBox->count()==0)
    {
        connect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
        return;
    }
    if(type!=2)
    {
        ui->tabWidget->setCurrentIndex(0);
        for(int i=0; i<ui->graphBox->count(); i++)
        {
            bool cont=false;
            ui->graphBox->setCurrentIndex(i);
            ui->graphBox_2->setCurrentIndex(i);
            ui->graphBox_3->setCurrentIndex(i);
            ui->graphBox_4->setCurrentIndex(i);
            ui->graphBoxDiff->setCurrentIndex(i);
            QString str = ui->graphBox->currentText();
            if(str.length()>4)
            {
                for(int i=0; i<str.length()-4; i++)
                {
                    if(str[i]=='(' && str[i+1]=='f' && str[i+2]=='i' && str[i+3]=='t' && str[i+4]==':')
                    {
                        cont=true;
                        break;
                    }
                }
                if(cont==true)
                    continue;
            }
            Autofit();
        }
    }
    if(type!=1)
    {
        ui->tabWidget->setCurrentIndex(1);
        for(int i=0; i<ui->graphBox_2->count(); i++)
        {
            bool cont=false;
            ui->graphBox->setCurrentIndex(i);
            ui->graphBox_2->setCurrentIndex(i);
            ui->graphBox_3->setCurrentIndex(i);
            ui->graphBox_4->setCurrentIndex(i);
            ui->graphBoxDiff->setCurrentIndex(i);
            QString str = ui->graphBox_2->currentText();
            if(str.length()>4)
            {
                for(int i=0; i<str.length()-4; i++)
                {
                    if(str[i]=='(' && str[i+1]=='f' && str[i+2]=='i' && str[i+3]=='t' && str[i+4]==':')
                    {
                        cont=true;
                        break;
                    }
                }
                if(cont==true)
                    continue;
            }
            Autofit();
        }
    }
    connect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
}

void CDpal::Autofit()
{
    disconnect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
    if(ui->tabWidget->currentIndex()>1)
    {
        QMessageBox::StandardButton dialog;
        dialog = QMessageBox::warning(this, "CDpal",
                                      "Autofit can only be performed on the \"N→D\" and the \"N→I→D\" model.",
                                      QMessageBox::Ok);
        if(dialog==QMessageBox::Ok)
        {
            connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
            return;
        }
    }
    if(ui->tabWidget->currentIndex()==0)
    {
        if(ui->deltaBox->isChecked())
            ui->deltaBox->toggle();
        if(ui->tmBox->isChecked())
            ui->tmBox->toggle();
        if(ui->slope1Box->isChecked())
            ui->slope1Box->toggle();
        if(ui->slope2Box->isChecked())
            ui->slope2Box->toggle();
        if(ui->intercept1Box->isChecked())
            ui->intercept1Box->toggle();
        if(ui->intercept2Box->isChecked())
            ui->intercept2Box->toggle();
        if(!ui->cpBox->isChecked())
            ui->cpBox->toggle();
        if(ui->graphBox->count()==0)
        {
            connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
            return;
        }
        QString str = ui->graphBox->currentText();
        if(str.length()>4)
            for(int i=0; i<str.length()-4; i++)
            {
                if(str[i]=='(' && str[i+1]=='f' && str[i+2]=='i' && str[i+3]=='t' && str[i+4]==':')
                {
                    QMessageBox::StandardButton dialog;
                    dialog = QMessageBox::warning(this, "CDpal",
                                                  "Cannot fit curve fitted data.\nPlease select an experimental dataset.",
                                                  QMessageBox::Ok);
                    if(dialog==QMessageBox::Ok)
                    {
                        connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
                        return;
                    }
                }
            }
        std::vector< double > xV, yV, xV2, yV2, tmp1, tmp2;
        const QCPDataMap *dataMap2 =new QCPDataMap;
        dataMap2= ui->CDplot->graph(ui->graphBox->currentIndex())->data();
        QMap<double, QCPData>::const_iterator k = dataMap2->constBegin();
        int len =0;
        while (k != dataMap2->constEnd())
        {
            tmp1.push_back(k.value().key);
            tmp2.push_back(k.value().value);
            k++;
            len++;
        }
        if(len<10)
        {
            QMessageBox::StandardButton dialog;
            dialog = QMessageBox::warning(this, "CDpal",
                                          "Too few data points for automatic fitting.",
                                          QMessageBox::Ok);
            if(dialog==QMessageBox::Ok)
            {
                connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
                return;
            }
        }
        xV.push_back(tmp1[0]);
        xV.push_back(tmp1[1]);
        xV.push_back(tmp1[2]);
        xV.push_back(tmp1[3]);
        yV.push_back(tmp2[0]);
        yV.push_back(tmp2[1]);
        yV.push_back(tmp2[2]);
        yV.push_back(tmp2[3]);
        xV2.push_back(tmp1[len-4]);
        xV2.push_back(tmp1[len-3]);
        xV2.push_back(tmp1[len-2]);
        xV2.push_back(tmp1[len-1]);
        yV2.push_back(tmp2[len-4]);
        yV2.push_back(tmp2[len-3]);
        yV2.push_back(tmp2[len-2]);
        yV2.push_back(tmp2[len-1]);

        AutofitTm(tmp1, tmp2);
        if(chemical)
        {
            Autofitm();
            bool isInt;
            ui->cpEdit->text().toInt(&isInt); //Ensure that temperature is integer value
            if(!isInt)
                ui->cpEdit->setText("25");
        }
        else
        {
            AutofitDeltaH();
            AutofitDeltaCp();
        }
        AutofitRegion(1, len, xV, yV);
        extern QString matrixError;
        if(matrixError!="")
        {
            QMessageBox::StandardButton dialog3;
            dialog3 = QMessageBox::warning(this, "CDpal",
                                           "Autofit failed.",
                                           QMessageBox::Ok);
            if(QMessageBox::Ok==dialog3)
                matrixError="";
            connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
            return;
        }
        AutofitRegion(2, len, xV2, yV2);
        if(matrixError!="")
        {
            QMessageBox::StandardButton dialog3;
            dialog3 = QMessageBox::warning(this, "CDpal",
                                           "Autofit failed.",
                                           QMessageBox::Ok);
            if(QMessageBox::Ok==dialog3)
                matrixError="";
            connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
            return;
        }
        fitData();
        if(chemical)
        {
            QString temp(ui->cpEdit_2a->text());
            clearForm();
            ui->cpEdit_2a->setText(temp);
        }
        else clearForm();
    }
    else
    {
        if(ui->deltaBox_2a->isChecked())
            ui->deltaBox_2a->toggle();
        if(ui->deltaBox_2b->isChecked())
            ui->deltaBox_2b->toggle();
        if(ui->tmBox_2a->isChecked())
            ui->tmBox_2a->toggle();
        if(ui->tmBox_2b->isChecked())
            ui->tmBox_2b->toggle();
        if(ui->slopeBoxD_2->isChecked())
            ui->slopeBoxD_2->toggle();
        if(ui->slopeBoxI_2->isChecked())
            ui->slopeBoxI_2->toggle();
        if(ui->slopeBoxN_2->isChecked())
            ui->slopeBoxN_2->toggle();
        if(ui->interceptBoxD_2->isChecked())
            ui->interceptBoxD_2->toggle();
        if(ui->interceptBoxN_2->isChecked())
            ui->interceptBoxN_2->toggle();
        if(ui->interceptBoxI_2->isChecked())
            ui->interceptBoxI_2->toggle();
        if(!ui->cpBox_2a->isChecked())
            ui->cpBox_2a->toggle();
        if(!ui->cpBox_2b->isChecked())
            ui->cpBox_2b->toggle();
        if(ui->graphBox_2->count()==0)
        {
            connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
            return;
        }
        QString str = ui->graphBox_2->currentText();
        if(str.length()>4)
            for(int i=0; i<str.length()-4; i++)
            {
                if(str[i]=='(' && str[i+1]=='f' && str[i+2]=='i' && str[i+3]=='t' && str[i+4]==':')
                {
                    QMessageBox::StandardButton dialog;
                    dialog = QMessageBox::warning(this, "CDpal",
                                                  "Cannot fit curve fitted data.\nPlease select an experimental dataset.",
                                                  QMessageBox::Ok);
                    if(dialog==QMessageBox::Ok)
                    {
                        connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
                        return;
                    }
                }
            }
        std::vector< double > xV, yV, xV2, yV2, xVi, yVi, tmp1, tmp2;
        const QCPDataMap *dataMap2 =new QCPDataMap;
        dataMap2= ui->CDplot->graph(ui->graphBox_2->currentIndex())->data();
        QMap<double, QCPData>::const_iterator k = dataMap2->constBegin();
        int len =0;
        while (k != dataMap2->constEnd())
        {
            tmp1.push_back(k.value().key);
            tmp2.push_back(k.value().value);
            k++;
            len++;
        }
        if(len<10)
        {
            QMessageBox::StandardButton dialog;
            dialog = QMessageBox::warning(this, "CDpal",
                                          "Too few data points for automatic fitting.",
                                          QMessageBox::Ok);
            if(dialog==QMessageBox::Ok)
            {
                connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
                return;
            }
        }
        double derivate(9e99);
        for(int u(0); u<4; u++)
        {
            xVi.push_back(0.0);
            yVi.push_back(0.0);
        }
        double limitI(abs(tmp1[tmp1.size()-1]-tmp1[0])/10.0);
        for(unsigned int u(0); u<tmp1.size(); u++)
        {
            if(u%4==0 && tmp1[u]>tmp1[0]+limitI && tmp1[u]<tmp1[tmp1.size()-1]-limitI)
            {
                if(tmp1[u]-tmp1[u-3] > 0.0)
                {
                    if((tmp2[u]-tmp2[u-3])/(tmp1[u]-tmp1[u-3]) <derivate)
                    {
                        derivate=(tmp2[u]-tmp2[u-3])/(tmp1[u]-tmp1[u-3]);
                        xVi[0]=tmp1[u-3];
                        xVi[1]=tmp1[u-2];
                        xVi[2]=tmp1[u-1];
                        xVi[3]=tmp1[u];
                        yVi[0]=tmp2[u-3];
                        yVi[1]=tmp2[u-2];
                        yVi[2]=tmp2[u-1];
                        yVi[3]=tmp2[u];
                    }
                }
            }
        }
        xV.push_back(tmp1[0]);
        xV.push_back(tmp1[1]);
        xV.push_back(tmp1[2]);
        xV.push_back(tmp1[3]);
        yV.push_back(tmp2[0]);
        yV.push_back(tmp2[1]);
        yV.push_back(tmp2[2]);
        yV.push_back(tmp2[3]);
        xV2.push_back(tmp1[len-4]);
        xV2.push_back(tmp1[len-3]);
        xV2.push_back(tmp1[len-2]);
        xV2.push_back(tmp1[len-1]);
        yV2.push_back(tmp2[len-4]);
        yV2.push_back(tmp2[len-3]);
        yV2.push_back(tmp2[len-2]);
        yV2.push_back(tmp2[len-1]);

        Autofit2Tm(tmp1, tmp2);
        if(chemical)
        {
            Autofit2m();
            bool isInt;
            ui->cpEdit_2a->text().toInt(&isInt); //Ensure that temperature is integer value
            if(!isInt)
                ui->cpEdit_2a->setText("25");
        }
        else
        {
            Autofit2DeltaH();
            Autofit2DeltaCp();
        }
        Autofit2Region(1, len, xV, yV);
        extern QString matrixError;
        if(matrixError!="")
        {
            QMessageBox::StandardButton dialog3;
            dialog3 = QMessageBox::warning(this, "CDpal",
                                           "Autofit failed.",
                                           QMessageBox::Ok);
            if(QMessageBox::Ok==dialog3)
                matrixError="";
            connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
            return;
        }
        Autofit2Region(3, len, xVi, yVi);
        if(matrixError!="")
        {
            QMessageBox::StandardButton dialog3;
            dialog3 = QMessageBox::warning(this, "CDpal",
                                           "Autofit failed.",
                                           QMessageBox::Ok);
            if(QMessageBox::Ok==dialog3)
                matrixError="";
            connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
            return;
        }
        Autofit2Region(2, len, xV2, yV2);
        if(matrixError!="")
        {
            QMessageBox::StandardButton dialog3;
            dialog3 = QMessageBox::warning(this, "CDpal",
                                           "Autofit failed.",
                                           QMessageBox::Ok);
            if(QMessageBox::Ok==dialog3)
                matrixError="";
            connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
            return;
        }
        fitData();
        if(chemical)
        {
            QString temp(ui->cpEdit_2a->text());
            clearForm();
            ui->cpEdit_2a->setText(temp);
        }
        else
            clearForm();
    }
    connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
}
void CDpal::AutofitTm(std::vector< double > xV, std::vector< double > yV)
{
    double x1,x2,y1,y2;
    x1=x2=y1=y2=0;
    double derivate=0.0;
    double tm=0.0;
    bool first=true;    for(unsigned int y=0; y<static_cast<unsigned int>(xV.size()); y++)
    {
        if(y%2==0)
        {
            if(first)
            {
                x1=xV[y];
                y1=yV[y];
                if(x2-x1!=0 && y>0)
                {
                    if(derivate<(y2-y1)/(x2-x1))
                    {
                        derivate=(y2-y1)/(x2-x1);
                        tm = (x2+x1)/2;
                    }
                }
                first=false;
            }
            else
            {
                x2=xV[y];
                y2=yV[y];
                if(x2-x1!=0)
                {
                    if(derivate<(y2-y1)/(x2-x1))
                    {
                        derivate=(y2-y1)/(x2-x1);
                        tm = (x2+x1)/2;
                    }
                }
                first=true;
            }
        }
    }
    ui->tmEdit->setText(QString::number(tm));
}
void CDpal::Autofit2Tm(std::vector< double > xV, std::vector< double > yV)
{
    //Finding multiple Tm's
    double x1,x2,y1,y2;
    x1=x2=y1=y2=0;
    double derivate=0.0;
    double tm1(0.0), tm2(0.0);
    double xTm1((xV[xV.size()-1]-xV[0])/10.0);
    bool first=true;
    for(unsigned int y=0; y<static_cast<unsigned int>(xV.size()); y++)
    {
        if(y%2==0)
        {
            if(first)
            {
                x1=xV[y];
                y1=yV[y];
                if(x2-x1!=0 && y>0)
                {
                    if(derivate<(y2-y1)/(x2-x1))
                    {
                        derivate=(y2-y1)/(x2-x1);
                        tm1 = (x2+x1)/2;
                    }
                }
                first=false;
            }
            else
            {
                x2=xV[y];
                y2=yV[y];
                if(x2-x1!=0)
                {
                    if(derivate<(y2-y1)/(x2-x1))
                    {
                        derivate=(y2-y1)/(x2-x1);
                        tm1 = (x2+x1)/2;
                    }
                }
                first=true;
            }
        }
    }
    x1=x2=y1=y2=0;
    derivate =0;
    first=true;
    for(unsigned int y=0; y<static_cast<unsigned int>(xV.size()); y++)
    {
        if(y%2==0)
        {
            if(first)
            {
                x1=xV[y];
                y1=yV[y];
                if(x2-x1!=0 && y>0 && (tm1-xTm1 > (x2+x1)/2 || tm1+xTm1 < (x2+x1)/2))
                {
                    if(derivate<(y2-y1)/(x2-x1))
                    {
                        derivate=(y2-y1)/(x2-x1);
                        tm2 = (x2+x1)/2;
                    }
                }
                first=false;
            }
            else
            {
                x2=xV[y];
                y2=yV[y];
                if(x2-x1!=0 && (tm1-xTm1 > (x2+x1)/2 || tm1+xTm1 < (x2+x1)/2))
                {
                    if(derivate<(y2-y1)/(x2-x1))
                    {
                        derivate=(y2-y1)/(x2-x1);
                        tm2 = (x2+x1)/2;
                    }
                }
                first=true;
            }
        }
    }
    if(tm1>tm2)
    {
        ui->tmEdit_2a->setText(QString::number(tm2));
        ui->tmEdit_2b->setText(QString::number(tm1));
    }
    else
    {
        ui->tmEdit_2a->setText(QString::number(tm1));
        ui->tmEdit_2b->setText(QString::number(tm2));
    }
}

void CDpal::AutofitDeltaH()
{
    ui->deltaEdit->setText("350");
}
void CDpal::Autofit2DeltaH()
{
    ui->deltaEdit_2a->setText("100");
    ui->deltaEdit_2b->setText("350");
}
void CDpal::Autofitm()
{
    ui->deltaEdit->setText("10"); //Good value
}
void CDpal::Autofit2m()
{
    ui->deltaEdit_2a->setText("10");
    ui->deltaEdit_2b->setText("20"); //Good value
}
void CDpal::AutofitDeltaCp()
{
    ui->cpEdit->setText("0");
}
void CDpal::Autofit2DeltaCp()
{
    ui->cpEdit_2a->setText("0");
    ui->cpEdit_2b->setText("0");
}
void CDpal::Autofit2Region(int state, int len, std::vector< double > x, std::vector< double > y)
{
    extern bool fitRes;
    fitRes=true;
    extern QString matrixError;
    matrixError="";
    std::vector< double > a, errVal, params;
    std::vector< bool > fixed;
    errVal.resize(4);
    errVal[0]=1.0;
    errVal[1]=1.0;
    errVal[2]=1.0;
    errVal[3]=1.0;
    a.resize(2);
    a[0]=0;
    a[1]=1;
    params.resize(2);
    params[0]=a[0];
    params[1]=a[1];
    fixed.resize(4);
    for(int i=0; i<4; i++)
        fixed[i]=true;
    char *cfile=NULL;
    int dof(len);
    for(int i=0; i<4; i++)
        if(fixed[i]) --dof;
    void flin(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
    fitFunction fitData(x, y, errVal, params, fixed, flin); // Use default tolerance 1.0e-3
    fitData.start();
    if(matrixError!="")
        return;
    ErrorSim myerr(x, y, errVal, fitData.parVec, fixed, flin);
    myerr.simerror(); //jackknife
    Output myoutput(x, y, errVal, fitData.parVec, flin, myerr.jackerr,
                    fitData.variance, fitData.chi, dof, cfile, cfile);
    myoutput.print(true);
    myoutput.plot(false, true); //smooth plotting (many data points)
    extern std::string resultStr;
    std::istringstream iss(resultStr);
    std::string sub;
    iss >> sub;
    if(state==1)
        ui->interceptEditN_2->setText(mconvert(sub));
    else if(state==2)
        ui->interceptEditD_2->setText(mconvert(sub));
    else
        ui->interceptEditI_2->setText(mconvert(sub));
    iss >> sub;
    if(state==1)
        ui->slopeEditN_2->setText(mconvert(sub));
    else if(state==2)
        ui->slopeEditD_2->setText(mconvert(sub));
    else
        ui->slopeEditI_2->setText(mconvert(sub));
    fitRes=false;
}
void CDpal::AutofitRegion(int state, int len, std::vector< double > x, std::vector< double > y)
{
    extern bool fitRes;
    fitRes=true;
    extern QString matrixError;
    matrixError="";
    std::vector< double > a, errVal, params;
    std::vector< bool > fixed;
    errVal.resize(4);
    errVal[0]=1.0;
    errVal[1]=1.0;
    errVal[2]=1.0;
    errVal[3]=1.0;
    a.resize(2);
    a[0]=0;
    a[1]=1;
    params.resize(2);
    params[0]=a[0];
    params[1]=a[1];
    fixed.resize(4);
    for(int i=0; i<4; i++)
        fixed[i]=true;
    char *cfile=NULL;
    int dof(len);
    for(int i=0; i<4; i++)
        if(fixed[i]) --dof;
    void flin(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
    fitFunction fitData(x, y, errVal, params, fixed, flin); // Use default tolerance 1.0e-3
    fitData.start();
    if(matrixError!="")
        return;
    ErrorSim myerr(x, y, errVal, fitData.parVec, fixed, flin);
    myerr.simerror(); //jackknife
    Output myoutput(x, y, errVal, fitData.parVec, flin, myerr.jackerr,
                    fitData.variance, fitData.chi, dof, cfile, cfile);
    myoutput.print(true);
    myoutput.plot(false, true); //smooth plotting (many data points)
    extern std::string resultStr;
    std::istringstream iss(resultStr);
    std::string sub;
    iss >> sub;
    if(state==1)
        ui->intercept1Edit->setText(mconvert(sub));
    else
        ui->intercept2Edit->setText(mconvert(sub));
    iss >> sub;
    if(state==1)
        ui->slope1Edit->setText(mconvert(sub));
    else
        ui->slope2Edit->setText(mconvert(sub));
    fitRes=false;
}

void CDpal::readData(QStringList list, int normalize, QString item) //ChiraScan
{
    Q_UNUSED(item)
    extern QStringList files;
    files.clear();
    files = list;
    extern QStringList takenNames;
    takenNames.clear();
    for(int i(0); i<ui->CDplot->graphCount();i++)
        takenNames.push_back(ui->CDplot->graph(i)->name());
    nameFiles nameWin;
    nameWin.setWindowFlags(nameWin.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    nameWin.setWindowModality(Qt::ApplicationModal);
    extern bool customName;
    customName=false;
    if(nameWin.exec())
        customName=true;
    {
        customFormat customWin;
        customWin.setWindowFlags(customWin.windowFlags() & ~Qt::WindowContextHelpButtonHint);
        customWin.setWindowModality(Qt::ApplicationModal);
        if(customWin.exec())
        {
            QMessageBox::StandardButton dialog2;
            dialog2 = QMessageBox::warning(this, "CDpal",
                                           "Do you want to normalize the imported data?",
                                           QMessageBox::Yes | QMessageBox::No);
            if( dialog2 == QMessageBox::Yes)
            {
                normalize=1;
                ui->CDplot->yAxis->setLabel("Fractional change");
                ui->CDplot->yAxis->setLabelFont(QFont("sans", 12, QFont::Bold));
            }
            else
                normalize=0;
            //Using global variables instead of settings.txt
            bool enable2(false);
            if(ui->CDplot->graphCount()==0)
                enable2=true;
            extern std::vector< std::vector<std::vector<std::string> > >storedData;
            for(unsigned int i=0; i<storedData.size(); i++)
            {
                std::vector<std::vector<std::string> > dataVec;
                dataVec = storedData[i];
                if(dataVec.size()==0)
                    continue;
                if(normalize==1)
                {
                    double max=-1.0e99;
                    double min=1.0e99;
                    for (unsigned int i=0; i<dataVec.size(); i++)
                    {
                        if(atof(dataVec[i][1].c_str())>max)
                            max=atof(dataVec[i][1].c_str());
                        if(atof(dataVec[i][1].c_str())<min)
                            min=atof(dataVec[i][1].c_str());
                    }
                    for (unsigned int i=0; i<dataVec.size(); i++)
                    {
                        dataVec[i][1]=mconvert((atof(dataVec[i][1].c_str())-min)/(max-min));
                    }
                }
                if(dataVec.size()>1)
                {
                    if(customName)
                    {
                        extern QStringList graphNames;
                        extern QString currentName;
                        currentName = graphNames.at(i);
                    }
                    renderGraph(dataVec,0,0);
                }
            }
            if(normalize==1)
                ui->CDplot->yAxis->setRange(-0.1, 1.1);
            extern double minXG;
            extern double maxXG;
            ui->CDplot->xAxis->setRange(minXG-1.0,maxXG+1.0);
            ui->CDplot->replot();
            if(enable2==true && ui->CDplot->graphCount()>0)
            {
                ui->fitDiff->setEnabled(true);
                ui->autofitAllDiff->setEnabled(true);
                ui->autoFitDiff->setEnabled(true);
                disconnect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
                disconnect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
                disconnect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
                disconnect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
                disconnect(ui->actionFit,SIGNAL(triggered()),this,SLOT(fitData()));
                connect(ui->actionFit,SIGNAL(triggered()),this,SLOT(fitData()));
                connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
                ui->fitButton->setEnabled(true);
                connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
                ui->fitButton_2->setEnabled(true);
                connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
                ui->fitButton_3->setEnabled(true);
                connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
                ui->fitButton_4->setEnabled(true);
                disconnect(ui->actionSave_style_preset, SIGNAL(triggered()), this, SLOT(saveStyle()));
                connect(ui->actionSave_style_preset, SIGNAL(triggered()), this, SLOT(saveStyle()));
                ui->actionSave_style_preset->setEnabled(true);
                disconnect(ui->actionLoad_style_preset_2, SIGNAL(triggered()), this, SLOT(loadStyle()));
                connect(ui->actionLoad_style_preset_2, SIGNAL(triggered()), this, SLOT(loadStyle()));
                ui->actionLoad_style_preset_2->setEnabled(true);
                disconnect(ui->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
                connect(ui->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
                ui->actionSave_Project->setEnabled(true);
                disconnect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveResults()));
                connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveResults()));
                ui->actionSave->setEnabled(true);
                disconnect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
                connect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
                ui->actionExport_data->setEnabled(true);
                disconnect(ui->actionDelete_all_graphs,SIGNAL(triggered()),this,SLOT(removeAllGraphs()));
                disconnect(ui->actionDelete_fitted_graphs,SIGNAL(triggered()),this,SLOT(removeFittedGraphs()));
                connect(ui->actionDelete_all_graphs,SIGNAL(triggered()),this,SLOT(removeAllGraphs()));
                connect(ui->actionDelete_fitted_graphs,SIGNAL(triggered()),this,SLOT(removeFittedGraphs()));
                ui->actionDelete_all_graphs->setEnabled(true);
                ui->actionDelete_fitted_graphs->setEnabled(true);
                disconnect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
                disconnect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
                connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
                connect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
                disconnect(ui->actionF_test, SIGNAL(triggered()), this, SLOT(fTest()));
                connect(ui->actionF_test, SIGNAL(triggered()), this, SLOT(fTest()));

            }
        }
    }
    customName=false;
}

void CDpal::closeEvent(QCloseEvent *event)
{
    QMessageBox::StandardButton dialog;
    dialog = QMessageBox::warning(this, "CDpal",
                                  "Do you want to quit?\nAny unsaved changes will be lost.",
                                  QMessageBox::Ok | QMessageBox::Cancel);
    if( dialog == QMessageBox::Ok)
        QApplication::quit();
    else
        event->ignore();
}

void CDpal::omitData()
{
    extern int activeGraph;
    if(activeGraph!=-1)
    {
        QString str = ui->CDplot->graph(activeGraph)->name();
        bool ok=true;
        if(str.length()>4)
            for(int j=0; j<str.length()-4; j++)
            {
                if(str[j]=='(' && str[j+1]=='f' && str[j+2]=='i' && str[j+3]=='t' && str[j+4]==':')
                {
                    QMessageBox::warning(this, "CDpal","Fitted data cannot be omitted. Aborting.", QMessageBox::Ok);
                    ok=false;
                }
            }
        if(ok)
        {
            const QCPDataMap *dataMap = ui->CDplot->graph(activeGraph)->data();
            QMap<double, QCPData>::const_iterator j = dataMap->constBegin();
            QVector<double> x, y, yerr, x1, y1, yerr1;
            while (j != dataMap->constEnd())
            {
                x.push_back(j.value().key);
                y.push_back(j.value().value);
                if(ui->table->columnCount()==3)
                    yerr.push_back(j.value().valueErrorPlus);
                j++;
            }
            for(short s=0; s < ui->table->rowCount(); s++)
            {
                if(ui->table->item(s,0)->isSelected())
                {}
                else
                {
                    x1.push_back(x[s]);
                    y1.push_back(y[s]);
                    if(ui->table->columnCount()==3)
                        yerr1.push_back(yerr[s]);
                }
            }
            if(ui->table->columnCount()==2)
                ui->CDplot->graph(activeGraph)->setData(x1, y1);
            else if(ui->table->columnCount()==3)
                ui->CDplot->graph(activeGraph)->setDataValueError(x1, y1, yerr1);
        }
    }
    ui->CDplot->replot();
    updateTable(activeGraph);
    highlight();
    ui->CDplot->replot();
}

void CDpal::renderGraph(std::vector< std::vector<std::string> > dataVec, int mode, int graphNo) //mode, 0=For reading data; 1=For fitted graphs, 2=For residuals; graphNo = number of fitted/res graph
{
    removeHighlight();
    ui->CDplot->legend->setVisible(true);
    ui->CDplot->legend->setFont(QFont("Helvetica", 9));
    ui->CDplot->legend->setRowSpacing(-3);
    QVector<QCPScatterStyle::ScatterShape> shapes;
    shapes << QCPScatterStyle::ssCross;
    shapes << QCPScatterStyle::ssPlus;
    shapes << QCPScatterStyle::ssCircle;
    shapes << QCPScatterStyle::ssDisc;
    shapes << QCPScatterStyle::ssSquare;
    shapes << QCPScatterStyle::ssDiamond;
    shapes << QCPScatterStyle::ssStar;
    shapes << QCPScatterStyle::ssTriangle;
    shapes << QCPScatterStyle::ssTriangleInverted;
    shapes << QCPScatterStyle::ssCrossSquare;
    shapes << QCPScatterStyle::ssPlusSquare;
    shapes << QCPScatterStyle::ssCrossCircle;
    shapes << QCPScatterStyle::ssPlusCircle;
    shapes << QCPScatterStyle::ssPeace;
    extern QPen faucetPen;
    extern int faucetInt;
    extern int faucetShape;
    if(mode!=1)
        faucetPen = changePen(faucetPen, faucetInt);
    else
        faucetPen.setColor(ui->CDplot->graph(graphNo)->pen().color());
    faucetPen.setWidth(1);
    faucetInt++;
    faucetShape++;
    if(faucetInt>4)
        faucetInt=0;
    if(faucetShape>=shapes.size())
        faucetShape=0;
    for (int i=0; i<1; ++i)
    {
        ui->CDplot->addGraph();

        QVector<double> x1(dataVec.size()), y1(dataVec.size());
        for (unsigned int i=0; i<dataVec.size(); ++i)
        {
            x1[i] = atof(dataVec[i][0].c_str());
            y1[i] = atof(dataVec[i][1].c_str());
        }
        if(dataVec[0].size()>2)
        {
            QVector<double> y1err(dataVec.size());
            for (unsigned int i=0; i<dataVec.size(); ++i)
                y1err[i] = atof(dataVec[i][2].c_str());
            ui->CDplot->graph()->setDataValueError(x1, y1, y1err);
        }
        else
            ui->CDplot->graph()->setData(x1, y1);
        ui->CDplot->graph()->rescaleAxes(true);
        ui->CDplot->graph()->setPen(faucetPen);
        QString grName;
        if(mode==0)
        {
            extern bool customName;
            if(customName)
            {
                extern QString currentName;
                grName = currentName;
            }
            else
            {
                grName = "Graph ";
                //int grNo = ui->CDplot->graphCount()-1;
                int grNo = 0;
                for(int i=0; i<ui->CDplot->graphCount();i++)
                {
                    QString tmp = "Graph ";
                    tmp += QString::number(grNo);
                    if(tmp==ui->CDplot->graph(i)->name())
                    {
                        i=-1;
                        grNo++;
                    }
                    else if(ui->CDplot->graph(i)->name().length()>=tmp.length())
                        for(int j=0; j<tmp.length(); j++)
                        {
                            if(tmp[j]!=ui->CDplot->graph(i)->name()[j])
                                break;
                            else if(j==tmp.length()-1)
                            {
                                i=-1;
                                grNo++;
                            }
                        }
                }
                grName += QString::number(grNo);
            }
        }
        else if(mode==1)
        {
            grName = ui->CDplot->graph(graphNo)->name();
            int grNo=1;
            for(int i=0; i<ui->CDplot->graphCount();i++)
            {
                QString tmp = grName;
                tmp += "(fit:";
                tmp += QString::number(grNo);
                tmp += ")";
                if(tmp==ui->CDplot->graph(i)->name())
                {
                    i=-1;
                    grNo++;
                }
            }
            grName+="(fit:";
            grName+= QString::number(grNo);
            grName+=")";
        }
        else
        {
            grName = ui->CDplot->graph(graphNo)->name();
            int grNo=1;
            for(int i=0; i<ui->CDplot->graphCount();i++)
            {
                QString tmp = grName;
                tmp += "(res:";
                tmp += QString::number(grNo);
                tmp += ")";
                if(tmp==ui->CDplot->graph(i)->name())
                {
                    i=-1;
                    grNo++;
                }
            }
            grName+="(res:";
            grName+= QString::number(grNo);
            grName+=")";
        }
        ui->CDplot->graph()->setName(grName);
        ui->graphBox->addItem(grName);
        ui->graphBox_2->addItem(grName);
        ui->graphBox_3->addItem(grName);
        ui->graphBox_4->addItem(grName);
        ui->graphBoxDiff->addItem(grName);

        extern bool drawLine;
        if(drawLine==true)
            ui->CDplot->graph()->setLineStyle(QCPGraph::lsLine);
        else if(mode==2)
            ui->CDplot->graph()->setLineStyle(QCPGraph::lsImpulse);
        else
            ui->CDplot->graph()->setLineStyle(QCPGraph::lsNone);
        if(dataVec[0].size()>2)
        {
            ui->CDplot->graph()->setErrorType(QCPGraph::etValue);
            ui->CDplot->graph()->setErrorPen(faucetPen);
        }
        //set scatter style:
        if(drawLine==true || mode==2)
            ui->CDplot->graph()->setScatterStyle(QCPScatterStyle::ssNone);
        else
            ui->CDplot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(faucetShape),10));
        drawLine=false;
    }
    // set blank axis lines:
    ui->CDplot->rescaleAxes();
    ui->CDplot->xAxis->setTicks(true);
    ui->CDplot->yAxis->setTicks(true);
    ui->CDplot->xAxis->setTickLabels(true);
    ui->CDplot->yAxis->setTickLabels(true);
    // make top right axes clones of bottom left axes:
    ui->CDplot->axisRect()->setupFullAxesBox();
    autoScale();
}

void CDpal::fitData()
{
    disconnect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
    disconnect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
    disconnect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
    disconnect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));

    int model =1;
    if(ui->tabWidget->currentIndex()==1)
        model=2;
    else if(ui->tabWidget->currentIndex()==2)
        model=3;
    else if(ui->tabWidget->currentIndex()==3)
        model=4;

    QString str;
    switch (model)
    {
    case 1: str = ui->graphBox->currentText();
        ui->graphBox_2->setCurrentIndex(ui->graphBox->currentIndex());
        ui->graphBox_3->setCurrentIndex(ui->graphBox->currentIndex());
        ui->graphBox_4->setCurrentIndex(ui->graphBox->currentIndex());
        ui->graphBoxDiff->setCurrentIndex(ui->graphBox->currentIndex());
        break;
    case 2: str = ui->graphBox_2->currentText();
        ui->graphBox->setCurrentIndex(ui->graphBox_2->currentIndex());
        ui->graphBox_3->setCurrentIndex(ui->graphBox_2->currentIndex());
        ui->graphBox_4->setCurrentIndex(ui->graphBox_2->currentIndex());
        ui->graphBoxDiff->setCurrentIndex(ui->graphBox_2->currentIndex());
        break;
    case 3: str = ui->graphBox_3->currentText();
        ui->graphBox->setCurrentIndex(ui->graphBox_3->currentIndex());
        ui->graphBox_2->setCurrentIndex(ui->graphBox_3->currentIndex());
        ui->graphBox_4->setCurrentIndex(ui->graphBox_3->currentIndex());
        ui->graphBoxDiff->setCurrentIndex(ui->graphBox_3->currentIndex());
        break;
    case 4: str = ui->graphBox_4->currentText();
        ui->graphBox->setCurrentIndex(ui->graphBox_4->currentIndex());
        ui->graphBox_3->setCurrentIndex(ui->graphBox_4->currentIndex());
        ui->graphBox_2->setCurrentIndex(ui->graphBox_4->currentIndex());
        ui->graphBoxDiff->setCurrentIndex(ui->graphBox_4->currentIndex());
        break;
    }
    if(str.length()>4)
        for(int i=0; i<str.length()-4; i++)
        {
            if(str[i]=='(' && str[i+1]=='f' && str[i+2]=='i' && str[i+3]=='t' && str[i+4]==':')
            {
                QMessageBox::StandardButton dialog;
                dialog = QMessageBox::warning(this, "CDpal",
                                              "Cannot fit curve fitted data.\nPlease select an experimental dataset.",
                                              QMessageBox::Ok);
                if(dialog==QMessageBox::Ok)
                {
                    connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
                    connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
                    connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
                    connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
                    return;
                }
            }
        }

    std::vector< double > a, x, y, errVal, params;
    std::vector< bool > fixed;
    int index=0;
    switch (model)
    {
    case 1: index = ui->graphBox->currentIndex();
        break;
    case 2: index = ui->graphBox_2->currentIndex();
        break;
    case 3: index = ui->graphBox_3->currentIndex();
        break;
    case 4: index = ui->graphBox_4->currentIndex();
        break;
    }

    const QCPDataMap *dataMap = ui->CDplot->graph(index)->data();
    QMap<double, QCPData>::const_iterator j = dataMap->constBegin();
    int len =0;
    while (j != dataMap->constEnd())
    {
        j++;
        len++;
    }
    x.resize(len);
    y.resize(len);
    errVal.resize(len);
    int paramSize(13);
    if(chemical)
        paramSize--;
    switch (model)
    {
    case 1: a.resize(7);
        params.resize(7);
        fixed.resize(7);
        break;
    case 2:
        if(!chemical)
        {
            a.resize(12);
            params.resize(12);
            fixed.resize(12);
        }
        else
        {
            a.resize(11);
            params.resize(11);
            fixed.resize(11);
        }
        break;
    default: a.resize(paramSize);
        params.resize(paramSize);
        fixed.resize(paramSize);
        break;
    }
    switch(model)
    {                                                       // Temp or Chem
    case 1: a[0]=convertNotation(ui->deltaEdit->text());    // deltaH or m
        a[0]*=1000.0;
        a[1]=convertNotation(ui->tmEdit->text());           // Tm or Cm
        a[2]=convertNotation(ui->intercept1Edit->text());
        a[3]=convertNotation(ui->intercept2Edit->text());
        a[4]=convertNotation(ui->slope1Edit->text());
        a[5]=convertNotation(ui->slope2Edit->text());
        a[6]=convertNotation(ui->cpEdit->text());           //deltaCp or Temp
        break;
    case 2: a[0]=convertNotation(ui->deltaEdit_2a->text()); //deltaH or m
        a[0]*=1000.0;
        a[1]=convertNotation(ui->tmEdit_2a->text());        //Tm or Cm
        a[2]=convertNotation(ui->interceptEditN_2->text());
        a[3]=convertNotation(ui->interceptEditD_2->text());
        a[4]=convertNotation(ui->slopeEditN_2->text());
        a[5]=convertNotation(ui->slopeEditD_2->text());
        a[6]=convertNotation(ui->cpEdit_2a->text());        //deltaCp or Temp
        a[7]=convertNotation(ui->deltaEdit_2b->text());     //deltaH or m
        a[7]*=1000.0;
        a[8]=convertNotation(ui->tmEdit_2b->text());        //Tm or Cm
        a[9]=convertNotation(ui->interceptEditI_2->text());
        a[10]=convertNotation(ui->slopeEditI_2->text());
        if(!chemical)
            a[11]=convertNotation(ui->cpEdit_2b->text());
        break;
    case 3: a[0]=convertNotation(ui->deltaEdit_3a->text());
        a[0]*=1000.0;
        a[1]=convertNotation(ui->tmEdit_3a->text());
        a[2]=convertNotation(ui->interceptEditN_3->text());
        a[3]=convertNotation(ui->interceptEditD_3->text());
        a[4]=convertNotation(ui->slopeEditN_3->text());
        a[5]=convertNotation(ui->slopeEditD_3->text());
        a[6]=convertNotation(ui->cpEdit_3a->text());
        a[7]=convertNotation(ui->deltaEdit_3b->text());
        a[7]*=1000.0;
        a[8]=convertNotation(ui->tmEdit_3b->text());
        a[9]=convertNotation(ui->interceptEditI_3->text());
        a[10]=convertNotation(ui->slopeEditI_3->text());
        if(chemical)
        {
            a[11]=convertNotation(ui->proteinBox_3->text());
            a[11]/=1000000.0;
        }
        else
        {
            a[11]=convertNotation(ui->cpEdit_3b->text());
            a[12]=convertNotation(ui->proteinBox_3->text());
            a[12]/=1000000.0;
        }
        break;
    case 4: a[0]=convertNotation(ui->deltaEdit_4a->text());
        a[0]*=1000.0;
        a[1]=convertNotation(ui->tmEdit_4a->text());
        a[2]=convertNotation(ui->interceptEditN_4->text());
        a[3]=convertNotation(ui->interceptEditD_4->text());
        a[4]=convertNotation(ui->slopeEditN_4->text());
        a[5]=convertNotation(ui->slopeEditD_4->text());
        a[6]=convertNotation(ui->cpEdit_4a->text());
        a[7]=convertNotation(ui->deltaEdit_4b->text());
        a[7]*=1000.0;
        a[8]=convertNotation(ui->tmEdit_4b->text());
        a[9]=convertNotation(ui->interceptEditI_4->text());
        a[10]=convertNotation(ui->slopeEditI_4->text());
        if(chemical)
        {
            a[11]=convertNotation(ui->proteinBox_4->text());
            a[11]/=1000000.0;
        }
        else
        {
            a[11]=convertNotation(ui->cpEdit_4b->text());
            a[12]=convertNotation(ui->proteinBox_4->text());
            a[12]/=1000000.0;
        }
        break;
    }

    for(unsigned int i=0; i<a.size(); i++)
        params[i]=a[i];

    for(unsigned int i=0; i<fixed.size(); i++)
        fixed[i]=true;
    switch (model)
    {
    case 1: if(ui->deltaBox->isChecked())
            fixed[0]=false;
        if(ui->tmBox->isChecked())
            fixed[1]=false;
        if(ui->intercept1Box->isChecked())
            fixed[2]=false;
        if(ui->intercept2Box->isChecked())
            fixed[3]=false;
        if(ui->slope1Box->isChecked())
            fixed[4]=false;
        if(ui->slope2Box->isChecked())
            fixed[5]=false;
        if(ui->cpBox->isChecked() || chemical)
            fixed[6]=false;
        break;
    case 2: if(ui->deltaBox_2a->isChecked())
            fixed[0]=false;
        if(ui->tmBox_2a->isChecked())
            fixed[1]=false;
        if(ui->interceptBoxN_2->isChecked())
            fixed[2]=false;
        if(ui->interceptBoxD_2->isChecked())
            fixed[3]=false;
        if(ui->slopeBoxN_2->isChecked())
            fixed[4]=false;
        if(ui->slopeBoxD_2->isChecked())
            fixed[5]=false;
        if(ui->cpBox_2a->isChecked() || chemical)
            fixed[6]=false;
        if(ui->deltaBox_2b->isChecked())
            fixed[7]=false;
        if(ui->tmBox_2b->isChecked())
            fixed[8]=false;
        if(ui->interceptBoxI_2->isChecked())
            fixed[9]=false;
        if(ui->slopeBoxI_2->isChecked())
            fixed[10]=false;
        if(chemical)
        {
            if(ui->proteinFixChemical->isChecked())
                fixed[11]=false;
        }
        else
        {
            if(ui->cpBox_2b->isChecked())
                fixed[11]=false;
        }
        break;
    case 3: if(ui->deltaBox_3a->isChecked())
            fixed[0]=false;
        if(ui->tmBox_3a->isChecked())
            fixed[1]=false;
        if(ui->interceptBoxN_3->isChecked())
            fixed[2]=false;
        if(ui->interceptBoxD_3->isChecked())
            fixed[3]=false;
        if(ui->slopeBoxN_3->isChecked())
            fixed[4]=false;
        if(ui->slopeBoxD_3->isChecked())
            fixed[5]=false;
        if(ui->cpBox_3a->isChecked() || chemical)
            fixed[6]=false;
        if(ui->deltaBox_3b->isChecked())
            fixed[7]=false;
        if(ui->tmBox_3b->isChecked())
            fixed[8]=false;
        if(ui->interceptBoxI_3->isChecked())
            fixed[9]=false;
        if(ui->slopeBoxI_3->isChecked())
            fixed[10]=false;
        if(chemical)
        {
            if(ui->proteinFix3->isChecked())
                fixed[11]=false;
        }
        else
        {
            if(ui->cpBox_3b->isChecked())
                fixed[11]=false;
            if(ui->proteinFix3->isChecked())
                fixed[12]=false;
        }
        break;
    case 4: if(ui->deltaBox_4a->isChecked())
            fixed[0]=false;
        if(ui->tmBox_4a->isChecked())
            fixed[1]=false;
        if(ui->interceptBoxN_4->isChecked())
            fixed[2]=false;
        if(ui->interceptBoxD_4->isChecked())
            fixed[3]=false;
        if(ui->slopeBoxN_4->isChecked())
            fixed[4]=false;
        if(ui->slopeBoxD_4->isChecked())
            fixed[5]=false;
        if(ui->cpBox_4a->isChecked() || chemical)
            fixed[6]=false;
        if(ui->deltaBox_4b->isChecked())
            fixed[7]=false;
        if(ui->tmBox_4b->isChecked())
            fixed[8]=false;
        if(ui->interceptBoxI_4->isChecked())
            fixed[9]=false;
        if(ui->slopeBoxI_4->isChecked())
            fixed[10]=false;
        if(chemical)
        {
            if(ui->proteinFix4->isChecked())
                fixed[11]=false;
        }
        else
        {
            if(ui->cpBox_4b->isChecked())
                fixed[11]=false;
            if(ui->proteinFix4->isChecked())
                fixed[12]=false;
        }
        break;
    }
    for(unsigned int p=0; p<fixed.size(); p++)
    {
        if(params[p]>0)
            continue;
        if(fixed[p])
            params[p]=0.00000001;
    }
    char *cfile=NULL;
    int dof(len);
    for(unsigned int i=0; i<fixed.size(); i++)
        if(fixed[i])
            --dof;
    QMap<double, QCPData>::const_iterator i = dataMap->constBegin();
    int iter =0;
    while (i != dataMap->constEnd())
    {
        x[iter]=i.value().key;
        y[iter]=i.value().value;
        errVal[iter]=1.0;
        i++;
        iter++;
    }

    if(chemical)
    {
        switch (model)
        {
        case 1:
        {
            void fitfunc_two_state_chem(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            fitFunction fitData(x, y, errVal, params, fixed, fitfunc_two_state_chem);
            fitData.start();
            extern QString matrixError;
            if(matrixError!="")
            {
                QMessageBox::StandardButton dialog3;
                dialog3 = QMessageBox::warning(this, "CDpal",
                                               matrixError,
                                               QMessageBox::Ok);
                if(QMessageBox::Ok==dialog3)
                    matrixError="";
                connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
                return;
            }
            ErrorSim myerr(x, y, errVal, fitData.parVec, fixed, fitfunc_two_state_chem);
            myerr.simerror(); //jackknife

            Output myoutput(x, y, errVal, fitData.parVec, fitfunc_two_state_chem, myerr.jackerr,
                            fitData.variance, fitData.chi, dof, cfile, cfile);
            myoutput.print(true);
            myoutput.plot(false, true); //smooth plotting (many data points)
            plotfit(index);
            break;
        }
        case 2:
        {
            void fitfunc_three_state_chem(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            fitFunction fitData(x, y, errVal, params, fixed, fitfunc_three_state_chem);
            fitData.start();
            extern QString matrixError;
            if(matrixError!="")
            {
                QMessageBox::StandardButton dialog3;
                dialog3 = QMessageBox::warning(this, "CDpal",
                                               matrixError,
                                               QMessageBox::Ok);
                if(QMessageBox::Ok==dialog3)
                    matrixError="";
                connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
                return;
            }
            ErrorSim myerr(x, y, errVal, fitData.parVec, fixed, fitfunc_three_state_chem);
            myerr.simerror(); //jackknife

            Output myoutput(x, y, errVal, fitData.parVec, fitfunc_three_state_chem, myerr.jackerr,
                            fitData.variance, fitData.chi, dof, cfile, cfile);
            myoutput.print(true);
            myoutput.plot(false, true); //smooth plotting (many data points)
            plotfit(index);
            break;
        }
        case 3:
        {
            void fitfunc_three_state_dimer1_chem(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            fitFunction fitData(x, y, errVal, params, fixed, fitfunc_three_state_dimer1_chem);
            fitData.start();
            extern QString matrixError;
            if(matrixError!="")
            {
                QMessageBox::StandardButton dialog3;
                dialog3 = QMessageBox::warning(this, "CDpal",
                                               matrixError,
                                               QMessageBox::Ok);
                if(QMessageBox::Ok==dialog3)
                    matrixError="";
                connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
                return;
            }
            ErrorSim myerr(x, y, errVal, fitData.parVec, fixed, fitfunc_three_state_dimer1_chem);
            myerr.simerror(); //jackknife

            Output myoutput(x, y, errVal, fitData.parVec, fitfunc_three_state_dimer1_chem, myerr.jackerr,
                            fitData.variance, fitData.chi, dof, cfile, cfile);
            myoutput.print(true);
            myoutput.plot(false, true); //smooth plotting (many data points)
            plotfit(index);
            break;
        }
        case 4:
        {
            void fitfunc_three_state_dimer2_chem(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            fitFunction fitData(x, y, errVal, params, fixed, fitfunc_three_state_dimer2_chem);
            fitData.start();
            extern QString matrixError;
            if(matrixError!="")
            {
                QMessageBox::StandardButton dialog3;
                dialog3 = QMessageBox::warning(this, "CDpal",
                                               matrixError,
                                               QMessageBox::Ok);
                if(QMessageBox::Ok==dialog3)
                    matrixError="";
                connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
                return;
            }
            ErrorSim myerr(x, y, errVal, fitData.parVec, fixed, fitfunc_three_state_dimer2_chem);
            myerr.simerror(); //jackknife

            Output myoutput(x, y, errVal, fitData.parVec, fitfunc_three_state_dimer2_chem, myerr.jackerr,
                            fitData.variance, fitData.chi, dof, cfile, cfile);
            myoutput.print(true);
            myoutput.plot(false, true); //smooth plotting (many data points)
            plotfit(index);
            break;
        }
        }
    }
    else
    {
        switch (model)
        {
        case 1:
        {
            void function(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            fitFunction fitData(x, y, errVal, params, fixed, function);
            fitData.start();
            extern QString matrixError;
            if(matrixError!="")
            {
                QMessageBox::StandardButton dialog3;
                dialog3 = QMessageBox::warning(this, "CDpal",
                                               matrixError,
                                               QMessageBox::Ok);
                if(QMessageBox::Ok==dialog3)
                    matrixError="";
                connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
                return;
            }
            ErrorSim myerr(x, y, errVal, fitData.parVec, fixed, function);
            myerr.simerror(); //jackknife

            Output myoutput(x, y, errVal, fitData.parVec, function, myerr.jackerr,
                            fitData.variance, fitData.chi, dof, cfile, cfile);
            myoutput.print(true);
            myoutput.plot(false, true); //smooth plotting (many data points)
            plotfit(index);
            break;
        }
        case 2:
        {
            void fitfunc_three_state(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            fitFunction fitData(x, y, errVal, params, fixed, fitfunc_three_state);
            fitData.start();
            extern QString matrixError;
            if(matrixError!="")
            {
                QMessageBox::StandardButton dialog3;
                dialog3 = QMessageBox::warning(this, "CDpal",
                                               matrixError,
                                               QMessageBox::Ok);
                if(QMessageBox::Ok==dialog3)
                    matrixError="";
                connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
                return;
            }
            ErrorSim myerr(x, y, errVal, fitData.parVec, fixed, fitfunc_three_state);
            myerr.simerror(); //jackknife

            Output myoutput(x, y, errVal, fitData.parVec, fitfunc_three_state, myerr.jackerr,
                            fitData.variance, fitData.chi, dof, cfile, cfile);
            myoutput.print(true);
            myoutput.plot(false, true); //smooth plotting (many data points)
            plotfit(index);
            break;
        }
        case 3:
        {
            void fitfunc_three_state_dimer1(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            fitFunction fitData(x, y, errVal, params, fixed, fitfunc_three_state_dimer1);
            fitData.start();
            extern QString matrixError;
            if(matrixError!="")
            {
                QMessageBox::StandardButton dialog3;
                dialog3 = QMessageBox::warning(this, "CDpal",
                                               matrixError,
                                               QMessageBox::Ok);
                if(QMessageBox::Ok==dialog3)
                    matrixError="";
                connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
                return;
            }
            ErrorSim myerr(x, y, errVal, fitData.parVec, fixed, fitfunc_three_state_dimer1);
            myerr.simerror(); //jackknife

            Output myoutput(x, y, errVal, fitData.parVec, fitfunc_three_state_dimer1, myerr.jackerr,
                            fitData.variance, fitData.chi, dof, cfile, cfile);
            myoutput.print(true);
            myoutput.plot(false, true); //smooth plotting (many data points)
            plotfit(index);
            break;
        }
        case 4:
        {
            void fitfunc_three_state_dimer2(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            fitFunction fitData(x, y, errVal, params, fixed, fitfunc_three_state_dimer2);
            fitData.start();
            extern QString matrixError;
            if(matrixError!="")
            {
                QMessageBox::StandardButton dialog3;
                dialog3 = QMessageBox::warning(this, "CDpal",
                                               matrixError,
                                               QMessageBox::Ok);
                if(QMessageBox::Ok==dialog3)
                    matrixError="";
                connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
                connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
                return;
            }
            ErrorSim myerr(x, y, errVal, fitData.parVec, fixed, fitfunc_three_state_dimer2);
            myerr.simerror(); //jackknife

            Output myoutput(x, y, errVal, fitData.parVec, fitfunc_three_state_dimer2, myerr.jackerr,
                            fitData.variance, fitData.chi, dof, cfile, cfile);
            myoutput.print(true);
            myoutput.plot(false, true); //smooth plotting (many data points)
            plotfit(index);
            break;
        }
        }
    }
    extern std::vector< std::vector< std::string> > resultStrVec;
    int fitNo=1;
    for(unsigned int u=0; u<resultStrVec.size(); u++)
    {
        QString str = ui->graphBox->itemText(index)+"(fit:"+QString::number(fitNo)+")";
        if(resultStrVec[u][1] == mconvert(str))
        {
            fitNo++;
            u=-1;
        }
    }
    QString nN = ui->graphBox->itemText(index) + "(fit:" + QString::number(fitNo) + ")";
    std::vector<std::string> tmpStrVec;
    extern std::string resultStr;
    tmpStrVec.push_back(resultStr);
    tmpStrVec.push_back(mconvert(nN));
    //Store fitting parameters for display upon selection
    QString parameters;
    switch (model)
    {
    case 1:
        if(ui->deltaEdit->text()!="")
            parameters="1 "+ui->deltaEdit->text()+" ";
        else
            parameters="1 0 ";
        if(ui->deltaBox->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->tmEdit->text()!="")
            parameters+=ui->tmEdit->text()+" ";
        else
            parameters+="0 ";
        if(ui->tmBox->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->cpEdit->text()!="")
            parameters+=ui->cpEdit->text()+" ";
        else
            parameters+="0 ";
        if(ui->cpBox->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->slope1Edit->text()!="")
            parameters+=ui->slope1Edit->text()+" ";
        else
            parameters+="0 ";
        if(ui->slope1Box->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->intercept1Edit->text()!="")
            parameters+=ui->intercept1Edit->text()+" ";
        else
            parameters+="0 ";
        if(ui->intercept1Box->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->slope2Edit->text()!="")
            parameters+=ui->slope2Edit->text()+" ";
        else
            parameters+="0 ";
        if(ui->slope2Box->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->intercept2Edit->text()!="")
            parameters+=ui->intercept2Edit->text()+" ";
        else
            parameters+="0 ";
        if(ui->intercept2Box->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        break;
    case 2:
        if(ui->deltaEdit_2a->text()!="")
            parameters="2 "+ui->deltaEdit_2a->text()+" ";
        else
            parameters="2 0 ";
        if(ui->deltaBox_2a->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->deltaEdit_2b->text()!="")
            parameters+=ui->deltaEdit_2b->text()+" ";
        else
            parameters+="0 ";
        if(ui->deltaBox_2b->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->tmEdit_2a->text()!="")
            parameters+=ui->tmEdit_2a->text()+" ";
        else
            parameters+="0 ";
        if(ui->tmBox_2a->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->tmEdit_2b->text()!="")
            parameters+=ui->tmEdit_2b->text()+" ";
        else
            parameters+="0 ";
        if(ui->tmBox_2b->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->cpEdit_2a->text()!="")
            parameters+=ui->cpEdit_2a->text()+" ";
        else
            parameters+="0 ";
        if(ui->cpBox_2a->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(chemical)
        {
            if(ui->proteinBoxChemical->text()!="")
                parameters+=ui->proteinBoxChemical->text()+" ";
            else
                parameters+="0 ";
            if(ui->proteinFixChemical->isChecked())
                parameters+="true ";
            else
                parameters+="false ";
        }
        else
        {
            if(ui->cpEdit_2b->text()!="")
                parameters+=ui->cpEdit_2b->text()+" ";
            else
                parameters+="0 ";
            if(ui->cpBox_2b->isChecked())
                parameters+="true ";
            else
                parameters+="false ";
        }
        if(ui->slopeEditN_2->text()!="")
            parameters+=ui->slopeEditN_2->text()+" ";
        else
            parameters+="0 ";
        if(ui->slopeBoxN_2->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->interceptEditN_2->text()!="")
            parameters+=ui->interceptEditN_2->text()+" ";
        else
            parameters+="0 ";
        if(ui->interceptBoxN_2->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->slopeEditI_2->text()!="")
            parameters+=ui->slopeEditI_2->text()+" ";
        else
            parameters+="0 ";
        if(ui->slopeBoxI_2->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->interceptEditI_2->text()!="")
            parameters+=ui->interceptEditI_2->text()+" ";
        else
            parameters+="0 ";
        if(ui->interceptBoxI_2->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->slopeEditD_2->text()!="")
            parameters+=ui->slopeEditD_2->text()+" ";
        else
            parameters+="0 ";
        if(ui->slopeBoxD_2->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->interceptEditD_2->text()!="")
            parameters+=ui->interceptEditD_2->text()+" ";
        else
            parameters+="0 ";
        if(ui->interceptBoxD_2->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        break;
    case 3:
        if(ui->proteinBox_3->text()!="")
            parameters="3 "+ui->proteinBox_3->text()+" ";
        else
            parameters="3 0 ";
        if(ui->proteinFix3->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->deltaEdit_3a->text()!="")
            parameters+=ui->deltaEdit_3a->text()+" ";
        else
            parameters+="0 ";
        if(ui->deltaBox_3a->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->deltaEdit_3b->text()!="")
            parameters+=ui->deltaEdit_3b->text()+" ";
        else
            parameters+="0 ";
        if(ui->deltaBox_3b->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->tmEdit_3a->text()!="")
            parameters+=ui->tmEdit_3a->text()+" ";
        else
            parameters+="0 ";
        if(ui->tmBox_3a->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->tmEdit_3b->text()!="")
            parameters+=ui->tmEdit_3b->text()+" ";
        else
            parameters+="0 ";
        if(ui->tmBox_3b->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->cpEdit_3a->text()!="")
            parameters+=ui->cpEdit_3a->text()+" ";
        else
            parameters+="0 ";
        if(ui->cpBox_3a->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->cpEdit_3b->text()!="")
            parameters+=ui->cpEdit_3b->text()+" ";
        else
            parameters+="0 ";
        if(ui->cpBox_3b->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->slopeEditN_3->text()!="")
            parameters+=ui->slopeEditN_3->text()+" ";
        else
            parameters+="0 ";
        if(ui->slopeBoxN_3->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->interceptEditN_3->text()!="")
            parameters+=ui->interceptEditN_3->text()+" ";
        else
            parameters+="0 ";
        if(ui->interceptBoxN_3->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->slopeEditI_3->text()!="")
            parameters+=ui->slopeEditI_3->text()+" ";
        else
            parameters+="0 ";
        if(ui->slopeBoxI_3->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->interceptEditI_3->text()!="")
            parameters+=ui->interceptEditI_3->text()+" ";
        else
            parameters+="0 ";
        if(ui->interceptBoxI_3->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->slopeEditD_3->text()!="")
            parameters+=ui->slopeEditD_3->text()+" ";
        else
            parameters+="0 ";
        if(ui->slopeBoxD_3->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->interceptEditD_3->text()!="")
            parameters+=ui->interceptEditD_3->text()+" ";
        else
            parameters+="0 ";
        if(ui->interceptBoxD_3->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->proteinFix3->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        break;
    case 4:
        if(ui->proteinBox_4->text()!="")
            parameters="4 "+ui->proteinBox_4->text()+" ";
        else
            parameters="4 0 ";
        if(ui->proteinFix4->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->deltaEdit_4a->text()!="")
            parameters+=ui->deltaEdit_4a->text()+" ";
        else
            parameters+="0 ";
        if(ui->deltaBox_4a->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->deltaEdit_4b->text()!="")
            parameters+=ui->deltaEdit_4b->text()+" ";
        else
            parameters+="0 ";
        if(ui->deltaBox_4b->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->tmEdit_4a->text()!="")
            parameters+=ui->tmEdit_4a->text()+" ";
        else
            parameters+="0 ";
        if(ui->tmBox_4a->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->tmEdit_4b->text()!="")
            parameters+=ui->tmEdit_4b->text()+" ";
        else
            parameters+="0 ";
        if(ui->tmBox_4b->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->cpEdit_4a->text()!="")
            parameters+=ui->cpEdit_4a->text()+" ";
        else
            parameters+="0 ";
        if(ui->cpBox_4a->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->cpEdit_4b->text()!="")
            parameters+=ui->cpEdit_4b->text()+" ";
        else
            parameters+="0 ";
        if(ui->cpBox_4b->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->slopeEditN_4->text()!="")
            parameters+=ui->slopeEditN_4->text()+" ";
        else
            parameters+="0 ";
        if(ui->slopeBoxN_4->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->interceptEditN_4->text()!="")
            parameters+=ui->interceptEditN_4->text()+" ";
        else
            parameters+="0 ";
        if(ui->interceptBoxN_4->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->slopeEditI_4->text()!="")
            parameters+=ui->slopeEditI_4->text()+" ";
        else
            parameters+="0 ";
        if(ui->slopeBoxI_4->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->interceptEditI_4->text()!="")
            parameters+=ui->interceptEditI_4->text()+" ";
        else
            parameters+="0 ";
        if(ui->interceptBoxI_4->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->slopeEditD_4->text()!="")
            parameters+=ui->slopeEditD_4->text()+" ";
        else
            parameters+="0 ";
        if(ui->slopeBoxD_4->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->interceptEditD_4->text()!="")
            parameters+=ui->interceptEditD_4->text()+" ";
        else
            parameters+="0 ";
        if(ui->interceptBoxD_4->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        if(ui->proteinFix4->isChecked())
            parameters+="true ";
        else
            parameters+="false ";
        break;
    }
    tmpStrVec.push_back(mconvert(parameters));
    //
    resultStrVec.push_back(tmpStrVec);
    extern std::vector< std::string> rV;
    extern std::vector< std::vector< std::string> > rV2;
    for(int o=0; o<7; o++)
        if(!fixed[o])
            rV[4+o*2]="Fixed";
    if(model>1)
    {
        for(int o=7; o<12; o++)
            if(!fixed[o])
                rV[4+o*2]="Fixed";
        if(model>2 && !chemical)
        {
            if(!fixed[12])
                rV[28]="Fixed";
        }

    }
    rV2.push_back(rV);
    //Enable correct lineEdits and labels for corresponding model
    loadLabels(model);
    fillLabels(resultStrVec.size()-1, model);
    //Change to result tab after fit
    ui->tabWidget_2->setCurrentIndex(1);
    connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
    connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
    connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
    connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
}

void CDpal::loadLabels(int model)
{
    //Enable labels for correct model
    switch(model)
    {
    case 1:
        //Hidden
        ui->lP->setVisible(false);
        ui->fP->setVisible(false);
        ui->errP->setVisible(false);
        ui->lH2->setVisible(false);
        ui->fH2->setVisible(false);
        ui->errH2->setVisible(false);
        ui->lTm2->setVisible(false);
        ui->fTm2->setVisible(false);
        ui->errTm2->setVisible(false);
        ui->lCp_2->setVisible(false);
        ui->fCp_2->setVisible(false);
        ui->errCp_2->setVisible(false);
        ui->lIi->setVisible(false);
        ui->fIi->setVisible(false);
        ui->errIi->setVisible(false);
        ui->lKi->setVisible(false);
        ui->fKi->setVisible(false);
        ui->errKi->setVisible(false);
        //Other labels always visible
        break;
    case 2:
        ui->lP->setVisible(false);
        ui->fP->setVisible(false);
        ui->errP->setVisible(false);
        ui->lH2->setVisible(true);
        ui->fH2->setVisible(true);
        ui->errH2->setVisible(true);
        ui->lTm2->setVisible(true);
        ui->fTm2->setVisible(true);
        ui->errTm2->setVisible(true);
        ui->lCp_2->setVisible(true);
        if(chemical)
            ui->lCp_2->setText("<html><font color=\"black\">[P]</font> (µM)</html>");
        ui->fCp_2->setVisible(true);
        ui->errCp_2->setVisible(true);
        ui->lIi->setVisible(true);
        ui->fIi->setVisible(true);
        ui->errIi->setVisible(true);
        ui->lKi->setVisible(true);
        ui->fKi->setVisible(true);
        ui->errKi->setVisible(true);
        break;
    case 5:
        break;
    default:
        ui->lP->setVisible(true);
        ui->fP->setVisible(true);
        ui->errP->setVisible(true);
        ui->lH2->setVisible(true);
        ui->fH2->setVisible(true);
        ui->errH2->setVisible(true);
        ui->lTm2->setVisible(true);
        ui->fTm2->setVisible(true);
        ui->errTm2->setVisible(true);
        ui->lCp_2->setVisible(true);
        ui->fCp_2->setVisible(true);
        ui->errCp_2->setVisible(true);
        ui->lIi->setVisible(true);
        ui->fIi->setVisible(true);
        ui->errIi->setVisible(true);
        ui->lKi->setVisible(true);
        ui->fKi->setVisible(true);
        ui->errKi->setVisible(true);
        break;
    }
}

void CDpal::fillLabels(int no, int model)
{
    //Put fitted parameters in the result tab
    extern std::vector< std::vector< std::string> > rV2;
    extern std::vector< std::vector< std::string> > resultStrVec;
    if(model == 5)
    {
        ui->e1->setText(mconvert(resultStrVec[no][1]));
        ui->e2->setText(mconvert(rV2[no][0]));
        ui->e3->setText(mconvert(rV2[no][1]));
        ui->e4->setText(mconvert(rV2[no][2]));

        ui->fH1->setText(mconvert(rV2[no][3]));
        ui->errH1->setText(mconvert(rV2[no][4]));
        ui->fTm1->setText(mconvert(rV2[no][5]));
        ui->errTm1->setText(mconvert(rV2[no][6]));
        ui->fscale->setText(mconvert(rV2[no][7]));
        ui->errscale->setText(mconvert(rV2[no][8]));
        return;
    }

    if(chemical)
    {
        ui->lP->setVisible(false);
        ui->fP->setVisible(false);
        ui->errP->setVisible(false);
    }
    switch(model)
    {
    case 1: ui->modelEdit->setText("N-D");
        break;
    case 2: ui->modelEdit->setText("N-I-D");
        break;
    case 3: ui->modelEdit->setText("N2-2I-2D");
        break;
    case 4: ui->modelEdit->setText("N2-I2-2D");
        break;
    }
    ui->e1->setText(mconvert(resultStrVec[no][1]));
    ui->e2->setText(mconvert(rV2[no][0]));
    ui->e3->setText(mconvert(rV2[no][1]));
    ui->e4->setText(mconvert(rV2[no][2]));
    ui->fH1->setText(mconvert(rV2[no][3]));
    ui->errH1->setText(mconvert(rV2[no][4]));
    ui->fTm1->setText(mconvert(rV2[no][5]));
    ui->errTm1->setText(mconvert(rV2[no][6]));
    ui->fIn->setText(mconvert(rV2[no][7]));
    ui->errIn->setText(mconvert(rV2[no][8]));
    ui->fId->setText(mconvert(rV2[no][9]));
    ui->errId->setText(mconvert(rV2[no][10]));
    ui->fKn->setText(mconvert(rV2[no][11]));
    ui->errKn->setText(mconvert(rV2[no][12]));
    ui->fKd->setText(mconvert(rV2[no][13]));
    ui->errKd->setText(mconvert(rV2[no][14]));
    ui->fCp->setText(mconvert(rV2[no][15]));
    ui->errCp->setText(mconvert(rV2[no][16]));
    if(model==1)
    {
        if(chemical)
        {
            //For chemical denaturation deltaG at 0 M denaturant is calculated
            bool ok(true), ok2(true);
            double Cm(ui->fTm1->text().toDouble(&ok));
            double m(ui->fH1->text().toDouble(&ok2));
            if(!ok || !ok2)
            {
                ui->fS->setText("N/A");
                ui->errS->setText("N/A");
            }
            else //Cm and m are doubles
            {
                ui->fS->setText(calcSG(1,1,m,Cm,0.0,0.0));
                double dCm(ui->errTm1->text().toDouble(&ok));
                double dm(ui->errH1->text().toDouble(&ok2));
                if(!ok && !ok2) //Fixed values for both Cm and dm
                    ui->errS->setText("N/A");
                else if(!ok)//Fixed value for Cm
                    ui->errS->setText(calcdSdG(1,3,0,1,m,Cm,0.0,0.0,dm,0.0,0.0,0.0));
                else if(!ok2)//Fixed value for m
                    ui->errS->setText(calcdSdG(1,2,0,1,m,Cm,0.0,0.0,0.0,dCm,0.0,0.0));
                else //Errors are doubles
                    ui->errS->setText(calcdSdG(1,1,0,1,m,Cm,0.0,0.0,dm,dCm,0.0,0.0));
            }
        }
        else //Thermal denaturation
        {
            bool ok(true), ok2(true);
            double Tm(ui->fTm1->text().toDouble(&ok));
            double H(ui->fH1->text().toDouble(&ok2));
            if(!ok || !ok2)
            {
                ui->fS->setText("N/A");
                ui->errS->setText("N/A");
            }
            else //Tm and H are doubles
            {
                ui->fS->setText(calcSG(1,0,H,Tm,0.0,0.0));
                double dTm(ui->errTm1->text().toDouble(&ok));
                double dH(ui->errH1->text().toDouble(&ok2));
                if(!ok && !ok2) //Fixed values for both Tm and H
                    ui->errS->setText("N/A");
                else if(!ok)//Fixed value for Tm
                    ui->errS->setText(calcdSdG(1,3,0,0,H,Tm,0.0,0.0,dH,0.0,0.0,0.0));
                else if(!ok2)//Fixed value for H
                    ui->errS->setText(calcdSdG(1,2,0,0,H,Tm,0.0,0.0,0.0,dTm,0.0,0.0));
                else //Errors are doubles
                    ui->errS->setText(calcdSdG(1,1,0,0,H,Tm,0.0,0.0,dH,dTm,0.0,0.0));
            }
        }
        return;
    }
    ui->fH2->setText(mconvert(rV2[no][17]));
    ui->errH2->setText(mconvert(rV2[no][18]));
    ui->fTm2->setText(mconvert(rV2[no][19]));
    ui->errTm2->setText(mconvert(rV2[no][20]));
    ui->fIi->setText(mconvert(rV2[no][21]));
    ui->errIi->setText(mconvert(rV2[no][22]));
    ui->fKi->setText(mconvert(rV2[no][23]));
    ui->errKi->setText(mconvert(rV2[no][24]));
    if(chemical && model>2)
    {
        ui->fCp_2->setText(QString::number(convertNotation(mconvert(rV2[no][25]))*1000000.0));
        if(mconvert(rV2[no][26])=="Fixed")
            ui->errCp_2->setText(mconvert(rV2[no][26]));
        else
            ui->errCp_2->setText(QString::number(convertNotation(mconvert(rV2[no][26]))*1000000.0));
    }
    else if(!chemical)
    {
        ui->fCp_2->setText(mconvert(rV2[no][25]));
        ui->errCp_2->setText(mconvert(rV2[no][26]));
    }
    else
    {
        ui->fCp_2->setVisible(false);
        ui->errCp_2->setVisible(false);
        ui->lCp_2->setVisible(false);
    }
    if(chemical)
    {
        //For chemical denaturation deltaG at 0 M denaturant is calculated
        bool ok(true), ok2(true);
        double Cm(ui->fTm1->text().toDouble(&ok));
        double m(ui->fH1->text().toDouble(&ok2));
        bool ok3(true), ok4(true);
        double Cm2(ui->fTm2->text().toDouble(&ok3));
        double m2(ui->fH2->text().toDouble(&ok4));
        if(!ok || !ok2 || !ok3 || !ok4)
        {
            ui->fS->setText("N/A");
            ui->errS->setText("N/A");
        }
        else //Cm and m are doubles
        {
            ui->fS->setText(calcSG(2,1,m,Cm,m2,Cm2));
            double dCm(ui->errTm1->text().toDouble(&ok));
            double dm(ui->errH1->text().toDouble(&ok2));
            double dCm2(ui->errTm2->text().toDouble(&ok3));
            double dm2(ui->errH2->text().toDouble(&ok4));
            int submodel(0),submodel2(0);

            if(!ok && !ok2)//Cm1, m1 fixed
            {
                dCm=0.0;
                dm=0.0;
                submodel=0;
            }
            else if(!ok)//Cm1 fixed
            {
                dCm=0.0;
                submodel=3;
            }
            else if(!ok2)//m1 fixed
            {
                dm=0.0;
                submodel=2;
            }
            else //No parameter fixed
                submodel=1;

            if(!ok3 && !ok4)//Cm2, m2 fixed
            {
                dCm2=0.0;
                dm2=0.0;
                submodel2=0;
            }
            else if(!ok3)//Cm2 fixed
            {
                dCm2=0.0;
                submodel2=3;
            }
            else if(!ok4)//m2 fixed
            {
                dm2=0.0;
                submodel2=2;
            }
            else //No parameter fixed
                submodel2=1;
            ui->errS->setText(calcdSdG(2,submodel,submodel2,1,m,Cm,m2,Cm2,dm,dCm,dm2,dCm2));
        }
        return;
    }
    else //Thermal
    {
        bool ok(true), ok2(true);
        double Tm(ui->fTm1->text().toDouble(&ok));
        double H(ui->fH1->text().toDouble(&ok2));
        bool ok3(true), ok4(true);
        double Tm2(ui->fTm2->text().toDouble(&ok3));
        double H2(ui->fH2->text().toDouble(&ok4));
        if(!ok || !ok2 || !ok3 || !ok4)
        {
            ui->fS->setText("N/A");
            ui->errS->setText("N/A");
        }
        else //Tm and H are doubles
        {
            ui->fS->setText(calcSG(2,0,H,Tm,H2,Tm2));
            double dTm(ui->errTm1->text().toDouble(&ok));
            double dH(ui->errH1->text().toDouble(&ok2));
            double dTm2(ui->errTm2->text().toDouble(&ok3));
            double dH2(ui->errH2->text().toDouble(&ok4));
            int submodel(0),submodel2(0);

            if(!ok && !ok2)//Tm1, H1 fixed
            {
                dTm=0.0;
                dH=0.0;
                submodel=0;
            }
            else if(!ok)//Tm1 fixed
            {
                dTm=0.0;
                submodel=3;
            }
            else if(!ok2)//H1 fixed
            {
                dH=0.0;
                submodel=2;
            }
            else //No parameter fixed
                submodel=1;

            if(!ok3 && !ok4)//Tm2, H2 fixed
            {
                dTm2=0.0;
                dH2=0.0;
                submodel2=0;
            }
            else if(!ok3)//Tm2 fixed
            {
                dTm2=0.0;
                submodel2=3;
            }
            else if(!ok4)//H2 fixed
            {
                dH2=0.0;
                submodel2=2;
            }
            else //No parameter fixed
                submodel2=1;
            ui->errS->setText(calcdSdG(2,submodel,submodel2,0,H,Tm,H2,Tm2,dH,dTm,dH2,dTm2));
        }
    }
    if(model==2)
        return;
    ui->fP->setText(mconvert(rV2[no][27]));
    ui->errP->setText(mconvert(rV2[no][28]));
}

void CDpal::plotfit(int graphNo)
{
    extern std::vector< std::string > xplotfit, yplotfit;
    std::vector< std::vector<std::string> > datavec;
    std::vector<std::string> temp;
    for(unsigned int i=0; i<xplotfit.size(); i++)
    {
        temp.push_back(xplotfit[i]);
        temp.push_back(yplotfit[i]);
        datavec.push_back(temp);
        temp.clear();
    }
    extern bool drawLine;
    drawLine=true;
    renderGraph(datavec,1,graphNo);
    datavec.clear();
}

void CDpal::loadData()
{
    if(diffMode)
    {
        QMessageBox::StandardButton dialog;
        dialog = QMessageBox::warning(this, "Warning",
                                      "Importing a new data set will delete all current data sets.\n"
                                      "This step cannot be undone.",
                                      QMessageBox::Ok | QMessageBox::Cancel);
        if( dialog == QMessageBox::Cancel)
            return;
        diffMode = false;
        changeDiffMode(false);
        ui->CDplot->clearGraphs();
        ui->CDplot->replot();
        updateTable(0);
        clearResults();
        extern std::vector< std::vector< std::string> > rV2;
        extern std::vector< std::vector< std::string> > resultStrVec;
        resultStrVec.clear();
        rV2.clear();
        ui->graphBox->clear();
        ui->graphBox_2->clear();
        ui->graphBox_3->clear();
        ui->graphBox_4->clear();
        ui->graphBoxDiff->clear();
    }
    QFileDialog dialog(this);
    extern QString dirString;
    if(dirString=="")
        dialog.setDirectory(QDir::homePath());
    else
        dialog.setDirectory(dirString);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(trUtf8("(*.txt)"));
    if(dialog.exec())
    {
        dirString = dialog.selectedFiles().at(0);
        for(unsigned int i = dirString.size()-1; i>0; i--)
            if(dirString[i]=='/' || dirString[i]=='\\')
            {
                dirString = dirString.mid(0,i);
                break;
            }
        readData(dialog.selectedFiles(),0, "");
    }
}

void CDpal::fTest()
{
    extern QStringList itemLabels;
    itemLabels.clear();
    extern int highlightGraph;
    for(int i=0; i<ui->CDplot->graphCount();i++)
    {
        if(i==highlightGraph-1)
            continue;
        itemLabels << ui->CDplot->graph(i)->name();
    }
    ftest fDialog;
    fDialog.setWindowModality(Qt::ApplicationModal);
    if(fDialog.exec())
    {
    }
}
void CDpal::exportResults()
{
    extern QStringList itemLabels;
    itemLabels.clear();
    extern int highlightGraph;
    for(int i=0; i<ui->CDplot->graphCount();i++)
    {
        if(i==highlightGraph-1)
            continue;
        itemLabels << ui->CDplot->graph(i)->name();
    }
    exportDialog dialog_exp;
    dialog_exp.setWindowModality(Qt::ApplicationModal);
    if(dialog_exp.exec())
    {
        //Saves results
        QString path;
        QFileDialog dialog(this);
        dialog.setFileMode(QFileDialog::Directory);
        path = QFileDialog::getExistingDirectory(
                    this,
                    "Choose a directory",
                    QString::null, QFileDialog::ShowDirsOnly);
        if(path.isNull() == false)
        {
            path+="/";
            path = convSlash(path);
        }
        else
            return;
        QMessageBox::StandardButton dialog2;
        dialog2 = QMessageBox::warning(this, "CDpal",
                                       "CDpal will overwrite any file with the same name as the outputfile, i.e. Graph 0 has the output name \"Graph 0.txt\"\nIt is recommended to save your files in an empty folder.\nAre you sure you want to export data to the selected folder?",
                                       QMessageBox::Yes | QMessageBox::No);
        if(dialog2==QMessageBox::No)
            return;
        extern QStringList exportList;
        QStringListIterator it(exportList);
        while(it.hasNext())
        {
            QString tmp =path;
            extern QString resFileName;
            std::string fname2 = mconvert(tmp) +mconvert(resFileName);
            QString iterate = it.next();
            // ADD SAVE OF RESULTS IF SAVERES==TRUE
            extern bool saveRes;
            if(saveRes)
            {
                for(int j=0; j<iterate.length()-4; j++)
                {
                    if(iterate[j]=='(' && iterate[j+1]=='f' && iterate[j+2]=='i' && iterate[j+3]=='t' && iterate[j+4]==':')
                    {
                        QString str = iterate;
                        extern std::vector< std::vector< std::string> > resultStrVec;
                        for(unsigned int k=0; k<resultStrVec.size(); k++)
                        {
                            if(mconvert(resultStrVec[k][1])==str)
                            {
                                std::istringstream iss(resultStrVec[k][2]);
                                std::string sub;
                                iss >> sub;
                                int model = atoi(sub.c_str());
                                fillLabels(k, model);
                                extern std::vector< std::vector< std::string> > rV2;
                                std::ofstream file2;
                                file2.open(fname2.c_str(), std::ios::app);
                                file2<<"#Results\n";
                                file2<<"Inspecting: "<<resultStrVec[k][1]<<"\n";
                                switch(model){
                                case 1: file2<<"Model: N-D\n";
                                    break;
                                case 2: file2<<"Model: N-I-D\n";
                                    break;
                                case 3: file2<<"Model: N2-2I-2D\n";
                                    break;
                                case 4: file2<<"Model: N2-I2-2D\n";
                                    break;
                                case 5: file2<<"Model: First derivative\n";
                                    break;
                                }
                                file2<<"Number of points: "<<rV2[k][0]<<"\n";
                                file2<<"Degrees of freedom: "<<rV2[k][1]<<"\n";
                                file2<<"Sum of residuals: "<<rV2[k][2]<<"\n";
                                if(chemical)
                                {
                                    file2<<"m: "<<rV2[k][3]<<"\n";
                                    file2<<"m error: "<<rV2[k][4]<<"\n";
                                    file2<<"Cm1: "<<rV2[k][5]<<"\n";
                                    file2<<"Cm1 error: "<<rV2[k][6]<<"\n";
                                }
                                else
                                {
                                    file2<<"Delta H1: "<<rV2[k][3]<<"\n";
                                    file2<<"Delta H1 error: "<<rV2[k][4]<<"\n";
                                    file2<<"Tm1: "<<rV2[k][5]<<"\n";
                                    file2<<"Tm1 error: "<<rV2[k][6]<<"\n";
                                }
                                if(model == 5)
                                {
                                    file2<<"a (Scaling factor): "<<rV2[k][7]<<"\n";
                                    file2<<"a (Scaling factor) error: "<<rV2[k][8]<<"\n";
                                    file2.close();
                                    continue;
                                }
                                file2<<"Native intercept: "<<rV2[k][7]<<"\n";
                                file2<<"Native intercept error: "<<rV2[k][8]<<"\n";
                                file2<<"Denatured intercept: "<<rV2[k][9]<<"\n";
                                file2<<"Denatured intercept error: "<<rV2[k][10]<<"\n";
                                file2<<"Native slope: "<<rV2[k][11]<<"\n";
                                file2<<"Native slope error: "<<rV2[k][12]<<"\n";
                                file2<<"Denatured slope: "<<rV2[k][13]<<"\n";
                                file2<<"Denatured slope error: "<<rV2[k][14]<<"\n";
                                if(chemical)
                                {
                                    file2<<"Temperature: "<<rV2[k][15]<<"\n";

                                }
                                else
                                {
                                    file2<<"Delta Cp1: "<<rV2[k][15]<<"\n";
                                    file2<<"Delta Cp1 error: "<<rV2[k][16]<<"\n";
                                }
                                if(model==1)
                                {
                                    if(chemical)
                                    {
                                        file2<<"Delta G: "<<rV2[k][17]<<"\n";
                                        file2<<"Delta G error: "<<rV2[k][18]<<"\n";
                                    }
                                    else
                                    {
                                        file2<<"Delta S: "<<rV2[k][17]<<"\n";
                                        file2<<"Delta S error: "<<rV2[k][18]<<"\n";
                                    }
                                }
                                else
                                {
                                    if(chemical)
                                    {
                                        file2<<"m2: "<<rV2[k][17]<<"\n";
                                        file2<<"m2 error: "<<rV2[k][18]<<"\n";
                                        file2<<"Cm2: "<<rV2[k][19]<<"\n";
                                        file2<<"Cm2 error: "<<rV2[k][20]<<"\n";
                                        file2<<"Intermediate intercept: "<<rV2[k][21]<<"\n";
                                        file2<<"Intermediate intercept error: "<<rV2[k][22]<<"\n";
                                        file2<<"Intermediate slope: "<<rV2[k][23]<<"\n";
                                        file2<<"Intermediate slope error: "<<rV2[k][24]<<"\n";
                                        if(model>2)
                                        {
                                            file2<<"Protein concentration, µM: "<<rV2[k][25]<<"\n";
                                            file2<<"Protein concentration error, µM: "<<rV2[k][26]<<"\n";
                                        }
                                    }
                                    else
                                    {
                                        file2<<"Delta H2: "<<rV2[k][17]<<"\n";
                                        file2<<"Delta H2 error: "<<rV2[k][18]<<"\n";
                                        file2<<"Tm2: "<<rV2[k][19]<<"\n";
                                        file2<<"Tm2 error: "<<rV2[k][20]<<"\n";
                                        file2<<"Intermediate intercept: "<<rV2[k][21]<<"\n";
                                        file2<<"Intermediate intercept error: "<<rV2[k][22]<<"\n";
                                        file2<<"Intermediate slope: "<<rV2[k][23]<<"\n";
                                        file2<<"Intermediate slope error: "<<rV2[k][24]<<"\n";
                                        file2<<"Delta Cp2: "<<rV2[k][25]<<"\n";
                                        file2<<"Delta Cp2 error: "<<rV2[k][26]<<"\n";
                                    }
                                    if(model==2)
                                    {
                                        if(chemical)
                                        {
                                            file2<<"Delta G: "<<mconvert(ui->fS->text())<<"\n";
                                            file2<<"Delta G error: "<<mconvert(ui->errS->text())<<"\n";
                                        }
                                        else
                                        {
                                            file2<<"Delta S: "<<mconvert(ui->fS->text())<<"\n";
                                            file2<<"Delta S error: "<<mconvert(ui->errS->text())<<"\n";
                                        }
                                    }
                                    else
                                    {
                                        if(!chemical)
                                        {
                                            file2<<"Protein concentration, µM: "<<rV2[k][27]<<"\n";
                                            file2<<"Protein concentration error, µM: "<<rV2[k][28]<<"\n";
                                            file2<<"Delta S: "<<mconvert(ui->fS->text())<<"\n";
                                            file2<<"Delta S error: "<<mconvert(ui->errS->text())<<"\n";
                                        }
                                        else
                                        {
                                            file2<<"Delta G: "<<mconvert(ui->fS->text())<<"\n";
                                            file2<<"Delta G error: "<<mconvert(ui->errS->text())<<"\n";
                                        }

                                    }
                                }
                                file2<<"#EndOfResults\n\n";
                                file2.clear();
                                file2.close();
                            }
                        }
                    }
                }
            }
            //
            QString append =iterate;
            QString illegalChars = "\\/:?\"<>|.";
            for (int m=0; m<iterate.size(); m++)
            {
                for(int l=0; l<illegalChars.size(); l++)
                    if(illegalChars[l]==append[m])
                        append[m]=' ';
            }
            tmp += append;
            tmp += ".txt";
            std::string fname = mconvert(tmp);
            std::ofstream file;
            file.open(fname.c_str(), std::ios::out);
            for(int i=0; i<ui->CDplot->graphCount(); i++)
            {
                if(ui->CDplot->graph(i)->name()==iterate)
                {
                    const QCPDataMap *dataMap = ui->CDplot->graph(i)->data();
                    QMap<double, QCPData>::const_iterator j = dataMap->constBegin();
                    while (j != dataMap->constEnd())
                    {
                        file<<j.value().key<<" "<<j.value().value<<"\n";
                        j++;
                    }
                    break;
                }
            }
            file.clear();
            file.close();
        }
    }
}

QString CDpal::convSlash(QString word)
{
    std::string w = word.toUtf8().data();
    for(unsigned int i=0;i<w.length();i++)
        if(w[i]=='\\')
            w[i]='/';
    return QString::fromUtf8(w.c_str());
}

void CDpal::saveResults()
{
    extern bool titleChanged;
    if(!titleChanged)
    {
        QMessageBox::StandardButton dialog;
        dialog = QMessageBox::warning(this, "CDpal",
                                      "Are you sure you want to print the graph with the default title?",
                                      QMessageBox::Yes | QMessageBox::Cancel);
        if( dialog == QMessageBox::Yes)
        {
            QString selFilter("");
            QString saveFilename = QFileDialog::getSaveFileName(this, "Save as", "Choose a filename", "PNG(*.png);; TIFF(*.tiff *.tif);; JPEG(*.jpg *.jpeg)",&selFilter);
            if(saveFilename=="")
                return;
            QString saveExtension = "";
            int pos = saveFilename.lastIndexOf('.');
            if (pos >= 0)
                saveExtension = saveFilename.mid(pos + 1);
#ifdef Q_OS_LINUX
            if(saveExtension=="")
            {
                if(selFilter=="PNG(*.png)")
                    saveFilename+=".png";
                else if(selFilter=="TIFF(*.tiff *.tif)")
                    saveFilename+=".tif";
                else
                    saveFilename+=".jpeg";
            }
#endif
            QPixmap pixmap(ui->CDplot->size());
            ui->CDplot->render(&pixmap, QPoint(), QRegion());
            pixmap.save(saveFilename);
        }
    }
    else
    {
        extern QString titleName;
        QString saveFilename;
        if(titleName!="Double click to change title")
            saveFilename = QFileDialog::getSaveFileName(this, "Save as", titleName, "PNG(*.png);; TIFF(*.tiff *.tif);; JPEG(*.jpg *.jpeg)");
        else
            saveFilename = QFileDialog::getSaveFileName(this, "Save as", "Choose a filename", "PNG(*.png);; TIFF(*.tiff *.tif);; JPEG(*.jpg *.jpeg)");

        if(saveFilename=="")
            return;
        QString saveExtension = "PNG";
        int pos = saveFilename.lastIndexOf('.');
        if (pos >= 0)
            saveExtension = saveFilename.mid(pos + 1);

        QPixmap pixmap(ui->CDplot->size());
        ui->CDplot->render(&pixmap, QPoint(), QRegion());
        pixmap.save(saveFilename);
    }
}

void CDpal::saveProject()
{
    //Saves state of project to one file.
    //If a project file exists, all data necessary to restore the state will exist unless corrupted
    std::string saveFilename = mconvert(QFileDialog::getSaveFileName(this, "Save as", "Choose a filename", "PROJ(*.proj)"));
    if(saveFilename=="")
        return;
    std::ofstream file;
    int fit(0), graph(0);
    for(int i=0; i<ui->CDplot->graphCount(); i++)
    {
        bool isFit(false);
        if(ui->CDplot->graph(i)->name().length()>4)
        {
            for(int k=0; k<ui->CDplot->graph(i)->name().length()-4; k++)
            {
                if(ui->CDplot->graph(i)->name()[k]=='(' && ui->CDplot->graph(i)->name()[k+1]=='f' && ui->CDplot->graph(i)->name()[k+2]=='i' && ui->CDplot->graph(i)->name()[k+3]=='t' && ui->CDplot->graph(i)->name()[k+4]==':')
                {
                    isFit=true;
                    fit++;
                    break;
                }
            }
            if(!isFit)
                graph++;
        }
        else
        {
            graph++;
        }
    }

    file.open(saveFilename.c_str(), std::ios::out);
    extern QString titleName;
    file<<"Title: "<<mconvert(titleName)<<"\n";
    file<<"x-axis: "<<mconvert(ui->CDplot->xAxis->label())<<"\n";
    file<<"y-axis: "<<mconvert(ui->CDplot->yAxis->label())<<"\n";
    file<<"GraphCount: "<<graph<<"\n";
    file<<"FitCount: "<<fit<<"\n";
    extern int mode;
    file<<"FitMode: "<<mode<<"\n";
    for(int i=0; i<ui->CDplot->graphCount(); i++)
    {
        bool isFit(false);
        if(ui->CDplot->graph(i)->name().length()>4)
        {
            for(int k=0; k<ui->CDplot->graph(i)->name().length()-4; k++)
            {
                if(ui->CDplot->graph(i)->name()[k]=='(' && ui->CDplot->graph(i)->name()[k+1]=='f' && ui->CDplot->graph(i)->name()[k+2]=='i' && ui->CDplot->graph(i)->name()[k+3]=='t' && ui->CDplot->graph(i)->name()[k+4]==':')
                {
                    isFit=true;
                    break;
                }
            }
        }
        if(!isFit)
        {
            file<<"GraphStart\n";
            file<<"GraphName: "<<mconvert(ui->CDplot->graph(i)->name())<<"\n";
            std::string point("");
            QCPScatterStyle style = ui->CDplot->graph(i)->scatterStyle();
            if(style.shape()==QCPScatterStyle::ssCross)
                point="Cross";
            else if(style.shape()==QCPScatterStyle::ssPlus)
                point="Plus";
            else if(style.shape()==QCPScatterStyle::ssCircle)
                point="Circle";
            else if(style.shape()==QCPScatterStyle::ssDisc)
                point="Disc";
            else if(style.shape()==QCPScatterStyle::ssSquare)
                point="Square";
            else if(style.shape()==QCPScatterStyle::ssDiamond)
                point="Diamond";
            else if(style.shape()==QCPScatterStyle::ssStar)
                point="Star";
            else if(style.shape()==QCPScatterStyle::ssTriangle)
                point="Triangle";
            else if(style.shape()==QCPScatterStyle::ssTriangleInverted)
                point="TriangleInverted";
            else if(style.shape()==QCPScatterStyle::ssCrossSquare)
                point="CrossSquare";
            else if(style.shape()==QCPScatterStyle::ssPlusSquare)
                point="PlusSquare";
            else if(style.shape()==QCPScatterStyle::ssCrossCircle)
                point="CrossCircle";
            else if(style.shape()==QCPScatterStyle::ssPlusCircle)
                point="PlusCircle";
            else if(style.shape()==QCPScatterStyle::ssPeace)
                point="Peace";
            file<<"GraphPoint: "<<point<<"\n";
            QColor color = ui->CDplot->graph(i)->pen().color();
            file<<"RGB: "<<color.red()<<" "<<color.green()<<" "<<color.blue()<<"\n";
            file<<"PenWidth: "<<ui->CDplot->graph(i)->pen().width()<<"\n";
            const QCPDataMap *dataMap = ui->CDplot->graph(i)->data();
            QMap<double, QCPData>::const_iterator j = dataMap->constBegin();
            while (j != dataMap->constEnd())
            {
                file<<j.value().key<<" "<<j.value().value<<"\n";
                j++;
            }
            file<<"GraphEnd\n";
        }
    }
    for(int i(0); i<fit; i++)
    {
        extern std::vector< std::vector< std::string> > resultStrVec;
        extern std::vector< std::vector< std::string> > rV2;
        file<<"FitStart\n";
        file<<"FitVec0: "<<resultStrVec[i][0]<<"\n";
        file<<"FitName: "<<resultStrVec[i][1]<<"\n";
        for(int j(0); j<ui->CDplot->graphCount(); j++)
        {
            if(ui->CDplot->graph(j)->name()==mconvert(resultStrVec[i][1]))
            {
                QColor color = ui->CDplot->graph(j)->pen().color();
                file<<"RGB: "<<color.red()<<" "<<color.green()<<" "<<color.blue()<<"\n";
                file<<"PenWidth: "<<ui->CDplot->graph(j)->pen().width()<<"\n";
                file<<resultStrVec[i][2]<<"\n";
                for(unsigned int l(0); l<rV2[i].size(); l++)
                    file<<rV2[i][l]<<" ";
                file<<"\n";
                const QCPDataMap *dataMap = ui->CDplot->graph(j)->data();
                QMap<double, QCPData>::const_iterator k = dataMap->constBegin();
                while (k != dataMap->constEnd())
                {
                    file<<k.value().key<<" "<<k.value().value<<"\n";
                    k++;
                }
                break;
            }
        }
        file<<"FitEnd\n";
    }
    if(diffMode)
        file<<"DIFFMODE\n";
    file.close();
}

void CDpal::openProject()
{
    //Loads state of a project.
    //If a project file exists, all data necessary to restore the state will exist unless corrupted
    QFileDialog dialog(this);
    extern QString dirString;
    if(dirString=="")
        dialog.setDirectory(QDir::homePath());
    else
        dialog.setDirectory(dirString);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(trUtf8("PROJ(*.proj)"));
    if(dialog.exec())
    {
        if(ui->CDplot->graphCount()>0)
        {
            QMessageBox::StandardButton dialog2;
            dialog2 = QMessageBox::warning(this, "CDpal",
                                           "The current project will be closed. Any unsaved data will be lost.",
                                           QMessageBox::Ok | QMessageBox::Cancel);
            if(dialog2==QMessageBox::Cancel)
                return;
            ui->fitDiff->setEnabled(false);
            ui->autofitAllDiff->setEnabled(false);
            ui->autoFitDiff->setEnabled(false);
        }
        dirString = dialog.selectedFiles().at(0);
        for(unsigned int i = dirString.size()-1; i>0; i--)
            if(dirString[i]=='/' || dirString[i]=='\\')
            {
                dirString = dirString.mid(0,i);
                break;
            }

        //Remove all graphs
        ui->CDplot->clearGraphs();
        ui->CDplot->replot();
        updateTable(0);
        clearResults();
        extern std::vector< std::vector< std::string> > rV2;
        extern std::vector< std::vector< std::string> > resultStrVec;
        resultStrVec.clear();
        rV2.clear();
        diffMode = false;
        changeDiffMode(true);
        //Disables functions when no data is present
        disconnect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
        disconnect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
        disconnect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
        disconnect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
        disconnect(ui->actionFit,SIGNAL(triggered()),this,SLOT(fitData()));
        disconnect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveResults()));
        disconnect(ui->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
        ui->actionSave_Project->setDisabled(true);
        disconnect(ui->actionLoad_style_preset_2, SIGNAL(triggered()), this, SLOT(loadStyle()));
        ui->actionLoad_style_preset_2->setDisabled(true);
        disconnect(ui->actionSave_style_preset, SIGNAL(triggered()), this, SLOT(saveStyle()));
        ui->actionSave_style_preset->setDisabled(true);
        disconnect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
        disconnect(ui->actionDelete_graph,SIGNAL(triggered()),this,SLOT(removeSelectedGraph()));
        disconnect(ui->actionDelete_all_graphs,SIGNAL(triggered()),this,SLOT(removeAllGraphs()));
        disconnect(ui->actionDelete_fitted_graphs,SIGNAL(triggered()),this,SLOT(removeFittedGraphs()));
        ui->actionDelete_graph->setDisabled(true);
        ui->actionDelete_all_graphs->setDisabled(true);
        ui->actionDelete_fitted_graphs->setDisabled(true);
        disconnect(ui->actionColor,SIGNAL(triggered()),this,SLOT(colorGraph()));
        disconnect(ui->actionChange_style,SIGNAL(triggered()),this,SLOT(changeOrnament()));
        disconnect(ui->actionChange_pen_width,SIGNAL(triggered()),this,SLOT(changeWidth()));
        disconnect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
        disconnect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
        ui->actionColor->setDisabled(true);
        ui->fitButton->setDisabled(true);
        ui->fitButton_2->setDisabled(true);
        ui->fitButton_3->setDisabled(true);
        ui->fitButton_4->setDisabled(true);
        ui->actionSave->setDisabled(true);
        ui->actionExport_data->setDisabled(true);
        ui->actionChange_style->setDisabled(true);
        ui->actionChange_pen_width->setDisabled(true);
        ui->graphBox->clear();
        ui->graphBox_2->clear();
        ui->graphBox_3->clear();
        ui->graphBox_4->clear();
        ui->graphBoxDiff->clear();
        disconnect(ui->actionF_test, SIGNAL(triggered()), this, SLOT(fTest()));
        //

        std::ifstream file;
        bool passed(true), modeError(false);
        file.open(mconvert(dialog.selectedFiles().at(0)).c_str(), std::ios::in);
        if(file.is_open())
        {
            int graphcount(0), fitcount(0);
            std::string line("");
            int counter(1);
            while(getline(file, line))
            {
                std::string str = line;
                std::istringstream iss(line);
                std::string sub("");
                if(line == "DIFFMODE")
                    diffMode = true;

                if(counter<7)
                {
                    switch(counter)
                    {
                    case 1: iss>>sub;
                        if(sub!="Title:")
                            passed=false;
                        else
                        {
                            ui->CDplot->plotLayout()->remove(ui->CDplot->plotLayout()->element(0,0));
                            QCPPlotTitle *qTitle =  new QCPPlotTitle(ui->CDplot, mconvert(str.substr(7)));
                            qTitle->setFont(QFont("sans", 16, QFont::Bold));
                            ui->CDplot->plotLayout()->addElement(0, 0, qTitle);
                            counter++;
                        }
                        break;
                    case 2:iss>>sub;
                        if(sub!="x-axis:")
                            passed=false;
                        else
                        {
                            ui->CDplot->xAxis->setLabel(mconvert(str.substr(8)));
                            counter++;
                        }
                        break;
                    case 3:iss>>sub;
                        if(sub!="y-axis:")
                            passed=false;
                        else
                        {
                            ui->CDplot->yAxis->setLabel(mconvert(str.substr(8)));
                            counter++;
                        }
                        break;
                    case 4:iss>>sub;
                        if(sub!="GraphCount:")
                            passed=false;
                        else
                        {
                            iss>>sub;
                            graphcount = atoi(sub.c_str());
                            counter++;
                        }
                        break;
                    case 5:iss>>sub;
                        if(sub!="FitCount:")
                            passed=false;
                        else
                        {
                            iss>>sub;
                            fitcount = atoi(sub.c_str());
                            counter++;
                            if(graphcount+fitcount<1)
                                passed=false;
                        }
                        break;
                    case 6:iss>>sub;
                        if(sub!="FitMode:")
                            passed=false;
                        else
                        {
                            iss>>sub;
                            extern int mode;
                            if(atoi(sub.c_str())!=mode)
                            {
                                modeError=true;
                                passed=false;
                            }
                            counter++;
                        }
                        break;
                    }
                }
                else
                {
                    if(graphcount>0)
                    {
                        if(line!="GraphStart")
                        {
                            passed=false;
                            break;
                        }
                        int rowC(0);
                        QString graphName("");
                        QString graphPoint("");
                        QColor graphColor;
                        int graphPenWidth(1);
                        std::vector<std::vector<std::string> > dataVec;
                        while(getline(file, line))
                        {
                            if(line=="GraphEnd")
                            {
                                renderGraph(dataVec,0,0);
                                QString oldName = ui->CDplot->graph(ui->CDplot->graphCount()-1)->name();
                                ui->CDplot->graph(ui->CDplot->graphCount()-1)->setName(graphName);
                                QPen Pen = ui->CDplot->graph(ui->CDplot->graphCount()-1)->pen();
                                for(int u=0; u<ui->graphBox->count(); u++)
                                {
                                    if(ui->graphBox->itemText(u)==oldName)
                                    {
                                        ui->graphBox->setItemText(u,graphName);
                                        ui->graphBox_2->setItemText(u,graphName);
                                        ui->graphBox_3->setItemText(u,graphName);
                                        ui->graphBox_4->setItemText(u,graphName);
                                        ui->graphBoxDiff->setItemText(u,graphName);
                                    }
                                }
                                Pen.setWidth(graphPenWidth);
                                Pen.setColor(graphColor);
                                ui->CDplot->graph(ui->CDplot->graphCount()-1)->setPen(Pen);
                                ui->CDplot->graph(ui->CDplot->graphCount()-1)->setErrorPen(Pen);
                                QVector<QCPScatterStyle::ScatterShape> shapes;
                                shapes << QCPScatterStyle::ssCross;
                                shapes << QCPScatterStyle::ssPlus;
                                shapes << QCPScatterStyle::ssCircle;
                                shapes << QCPScatterStyle::ssDisc;
                                shapes << QCPScatterStyle::ssSquare;
                                shapes << QCPScatterStyle::ssDiamond;
                                shapes << QCPScatterStyle::ssStar;
                                shapes << QCPScatterStyle::ssTriangle;
                                shapes << QCPScatterStyle::ssTriangleInverted;
                                shapes << QCPScatterStyle::ssCrossSquare;
                                shapes << QCPScatterStyle::ssPlusSquare;
                                shapes << QCPScatterStyle::ssCrossCircle;
                                shapes << QCPScatterStyle::ssPlusCircle;
                                shapes << QCPScatterStyle::ssPeace;
                                if(graphPoint=="Cross")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(0), 10));
                                else if(graphPoint=="Plus")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(1), 10));
                                else if(graphPoint=="Circle")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(2), 10));
                                else if(graphPoint=="Disc")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(3), 10));
                                else if(graphPoint=="Square")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(4), 10));
                                else if(graphPoint=="Diamond")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(5), 10));
                                else if(graphPoint=="Star")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(6), 10));
                                else if(graphPoint=="Triangle")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(7), 10));
                                else if(graphPoint=="TriangleInverted")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(8), 10));
                                else if(graphPoint=="CrossSquare")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(9), 10));
                                else if(graphPoint=="PlusSquare")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(10), 10));
                                else if(graphPoint=="CrossCircle")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(11), 10));
                                else if(graphPoint=="PlusCircle")
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(12), 10));
                                else
                                    ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle(shapes.at(13), 10));
                                break;
                            }
                            if(rowC==0)
                            {
                                std::string str2(line), sub2("");
                                std::istringstream iss2(line);
                                iss2>>sub2;
                                if(sub2!="GraphName:")
                                {
                                    passed=false;
                                    break;
                                }
                                graphName=mconvert(str2.substr(11));
                                rowC++;
                            }
                            else if(rowC==1)
                            {
                                std::string str2(line), sub2("");
                                std::istringstream iss2(line);
                                iss2>>sub2;
                                if(sub2!="GraphPoint:")
                                {
                                    passed=false;
                                    break;
                                }
                                graphPoint=mconvert(str2.substr(12));
                                rowC++;
                            }
                            else if(rowC==2)
                            {
                                std::string sub2("");
                                std::istringstream iss2(line);
                                iss2>>sub2;
                                if(sub2!="RGB:")
                                {
                                    passed=false;
                                    break;
                                }
                                iss2>>sub2;
                                graphColor.setRed(atoi(sub2.c_str()));
                                iss2>>sub2;
                                graphColor.setGreen(atoi(sub2.c_str()));
                                iss2>>sub2;
                                graphColor.setBlue(atoi(sub2.c_str()));
                                rowC++;
                            }
                            else if(rowC==3)
                            {
                                std::string sub2("");
                                std::istringstream iss2(line);
                                iss2>>sub2;
                                if(sub2!="PenWidth:")
                                {
                                    passed=false;
                                    break;
                                }
                                iss2>>sub2;
                                graphPenWidth=atoi(sub2.c_str());
                                rowC++;
                            }
                            else
                            {
                                std::vector<std::string> tempVec;
                                std::string sub2("");
                                std::istringstream iss2(line);
                                iss2>>sub2;
                                tempVec.push_back(sub2);
                                iss2>>sub2;
                                tempVec.push_back(sub2);
                                dataVec.push_back(tempVec);
                            }
                        }
                        graphcount--;
                    }
                    else if(fitcount>0)
                    {
                        if(line!="FitStart")
                        {
                            passed=false;
                            break;
                        }
                        int rowC(-1);
                        QString fitName("");
                        QColor fitColor;
                        int fitPenWidth(1);
                        std::vector<std::vector<std::string> > dataVec;
                        std::vector< std::string> tmpVec;
                        extern std::vector< std::vector< std::string> > resultStrVec;
                        while(getline(file, line))
                        {
                            if(line=="FitEnd")
                            {
                                renderGraph(dataVec, 1, 0);
                                QString oldName = ui->CDplot->graph(ui->CDplot->graphCount()-1)->name();
                                ui->CDplot->graph(ui->CDplot->graphCount()-1)->setName(fitName);
                                QPen Pen = ui->CDplot->graph(ui->CDplot->graphCount()-1)->pen();
                                Pen.setWidth(fitPenWidth);
                                Pen.setColor(fitColor);
                                ui->CDplot->graph(ui->CDplot->graphCount()-1)->setPen(Pen);
                                ui->CDplot->graph(ui->CDplot->graphCount()-1)->setErrorPen(Pen);
                                ui->CDplot->graph(ui->CDplot->graphCount()-1)->setLineStyle(QCPGraph::lsLine);
                                ui->CDplot->graph(ui->CDplot->graphCount()-1)->setScatterStyle(QCPScatterStyle::ssNone);

                                for(int u=0; u<ui->graphBox->count(); u++)
                                {
                                    if(ui->graphBox->itemText(u)==oldName)
                                    {
                                        ui->graphBox->setItemText(u,fitName);
                                        ui->graphBox_2->setItemText(u,fitName);
                                        ui->graphBox_3->setItemText(u,fitName);
                                        ui->graphBox_4->setItemText(u,fitName);
                                        ui->graphBoxDiff->setItemText(u,fitName);
                                    }
                                }

                                break;
                            }
                            if(rowC==-1)
                            {
                                std::string str2(line), sub2("");
                                std::istringstream iss2(line);
                                iss2>>sub2;
                                if(sub2!="FitVec0:")
                                {
                                    passed=false;
                                    break;
                                }
                                tmpVec.push_back(str2.substr(9));
                                rowC++;
                            }
                            else if(rowC==0)
                            {
                                std::string str2(line), sub2("");
                                std::istringstream iss2(line);
                                iss2>>sub2;
                                if(sub2!="FitName:")
                                {
                                    passed=false;
                                    break;
                                }
                                fitName=mconvert(str2.substr(9));
                                rowC++;
                            }
                            else if(rowC==1)
                            {
                                std::string sub2("");
                                std::istringstream iss2(line);
                                iss2>>sub2;
                                if(sub2!="RGB:")
                                {
                                    passed=false;
                                    break;
                                }
                                iss2>>sub2;
                                fitColor.setRed(atoi(sub2.c_str()));
                                iss2>>sub2;
                                fitColor.setGreen(atoi(sub2.c_str()));
                                iss2>>sub2;
                                fitColor.setBlue(atoi(sub2.c_str()));
                                rowC++;
                            }
                            else if(rowC==2)
                            {
                                std::string sub2("");
                                std::istringstream iss2(line);
                                iss2>>sub2;
                                if(sub2!="PenWidth:")
                                {
                                    passed=false;
                                    break;
                                }
                                iss2>>sub2;
                                fitPenWidth=atoi(sub2.c_str());
                                rowC++;
                            }
                            else if(rowC==3)
                            {
                                tmpVec.push_back(mconvert(fitName));
                                tmpVec.push_back(line);
                                resultStrVec.push_back(tmpVec);
                                rowC++;
                            }
                            else if(rowC==4)
                            {
                                extern std::vector< std::vector< std::string> > rV2;
                                std::vector< std::string> tmpVec2;
                                std::string sub2("");
                                std::istringstream iss2(line);
                                while(iss2>>sub2)
                                    tmpVec2.push_back(sub2);
                                rV2.push_back(tmpVec2);
                                rowC++;
                            }
                            else
                            {
                                std::vector<std::string> tempVec;
                                std::string sub2("");
                                std::istringstream iss2(line);
                                iss2>>sub2;
                                tempVec.push_back(sub2);
                                iss2>>sub2;
                                tempVec.push_back(sub2);
                                dataVec.push_back(tempVec);
                            }
                        }
                        fitcount--;
                    }
                }
                if(!passed)
                    break;
            }
            file.close();
        }
        else
            passed=false;
        if(!passed || ui->CDplot->graphCount()<1)
        {
            ui->CDplot->clearGraphs();
            ui->CDplot->replot();
            updateTable(0);
            clearResults();
            extern std::vector< std::vector< std::string> > rV2;
            extern std::vector< std::vector< std::string> > resultStrVec;
            resultStrVec.clear();
            rV2.clear();
            //Disables functions when no data is present
            disconnect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
            disconnect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
            disconnect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
            disconnect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
            disconnect(ui->actionFit,SIGNAL(triggered()),this,SLOT(fitData()));
            disconnect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveResults()));
            disconnect(ui->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
            ui->actionSave_Project->setDisabled(true);
            disconnect(ui->actionSave_style_preset, SIGNAL(triggered()), this, SLOT(saveStyle()));
            ui->actionSave_style_preset->setDisabled(true);
            disconnect(ui->actionLoad_style_preset_2, SIGNAL(triggered()), this, SLOT(loadStyle()));
            ui->actionLoad_style_preset_2->setDisabled(true);
            disconnect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
            disconnect(ui->actionDelete_graph,SIGNAL(triggered()),this,SLOT(removeSelectedGraph()));
            disconnect(ui->actionDelete_all_graphs,SIGNAL(triggered()),this,SLOT(removeAllGraphs()));
            disconnect(ui->actionDelete_fitted_graphs,SIGNAL(triggered()),this,SLOT(removeFittedGraphs()));
            ui->actionDelete_graph->setDisabled(true);
            ui->actionDelete_all_graphs->setDisabled(true);
            ui->actionDelete_fitted_graphs->setDisabled(true);
            disconnect(ui->actionColor,SIGNAL(triggered()),this,SLOT(colorGraph()));
            disconnect(ui->actionChange_style,SIGNAL(triggered()),this,SLOT(changeOrnament()));
            disconnect(ui->actionChange_pen_width,SIGNAL(triggered()),this,SLOT(changeWidth()));
            disconnect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
            disconnect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
            ui->actionColor->setDisabled(true);
            ui->fitButton->setDisabled(true);
            ui->fitButton_2->setDisabled(true);
            ui->fitButton_3->setDisabled(true);
            ui->fitButton_4->setDisabled(true);
            ui->actionSave->setDisabled(true);
            ui->actionExport_data->setDisabled(true);
            ui->actionChange_style->setDisabled(true);
            ui->actionChange_pen_width->setDisabled(true);
            ui->graphBox->clear();
            ui->graphBox_2->clear();
            ui->graphBox_3->clear();
            ui->graphBox_4->clear();
            ui->graphBoxDiff->clear();
            disconnect(ui->actionF_test, SIGNAL(triggered()), this, SLOT(fTest()));
            QMessageBox::StandardButton dialog2;
            if(!modeError)
            {
                dialog2 = QMessageBox::warning(this, "CDpal",
                                               "Error! Could not read the project file.",
                                               QMessageBox::Ok);
                Q_UNUSED(dialog2)
            }
            else
            {
                extern int mode;
                if(mode==0)
                {
                    dialog2 = QMessageBox::warning(this, "CDpal",
                                                   "The project file is intended for use with the \"chemical denaturation\" mode. Please change mode before attempting to load this project.",
                                                   QMessageBox::Ok);
                    if(dialog2==QMessageBox::Ok)
                    {
                        ui->CDplot->xAxis->setLabel("Temperature (°C)");
                        ui->CDplot->replot();
                    }
                }
                else
                {
                    dialog2 = QMessageBox::warning(this, "CDpal",
                                                   "The project file is intended for use with the \"thermal denaturation\" mode. Please change mode before attempting to load this project.",
                                                   QMessageBox::Ok);
                    if(dialog2==QMessageBox::Ok)
                    {
                        ui->CDplot->xAxis->setLabel("Concentration (M)");
                        ui->CDplot->replot();
                    }
                }
            }
            return;
        }
        ui->CDplot->xAxis->setLabelFont(QFont("sans", 12, QFont::Bold));
        ui->CDplot->yAxis->setLabelFont(QFont("sans", 12, QFont::Bold));
        ui->CDplot->replot();
    }
    if(ui->CDplot->graphCount())
    {
        ui->fitDiff->setEnabled(true);
        ui->autofitAllDiff->setEnabled(true);
        ui->autoFitDiff->setEnabled(true);
    }
    disconnect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
    disconnect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
    disconnect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
    disconnect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
    disconnect(ui->actionFit,SIGNAL(triggered()),this,SLOT(fitData()));
    connect(ui->actionFit,SIGNAL(triggered()),this,SLOT(fitData()));
    connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
    ui->fitButton->setEnabled(true);
    connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
    ui->fitButton_2->setEnabled(true);
    connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
    ui->fitButton_3->setEnabled(true);
    connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
    ui->fitButton_4->setEnabled(true);
    disconnect(ui->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(ui->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
    ui->actionSave_Project->setEnabled(true);
    disconnect(ui->actionSave_style_preset, SIGNAL(triggered()), this, SLOT(saveStyle()));
    connect(ui->actionSave_style_preset, SIGNAL(triggered()), this, SLOT(saveStyle()));
    ui->actionSave_style_preset->setEnabled(true);
    disconnect(ui->actionLoad_style_preset_2, SIGNAL(triggered()), this, SLOT(loadStyle()));
    connect(ui->actionLoad_style_preset_2, SIGNAL(triggered()), this, SLOT(loadStyle()));
    ui->actionLoad_style_preset_2->setEnabled(true);
    disconnect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveResults()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveResults()));
    ui->actionSave->setEnabled(true);
    disconnect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
    connect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
    ui->actionExport_data->setEnabled(true);
    disconnect(ui->actionDelete_all_graphs,SIGNAL(triggered()),this,SLOT(removeAllGraphs()));
    disconnect(ui->actionDelete_fitted_graphs,SIGNAL(triggered()),this,SLOT(removeFittedGraphs()));
    connect(ui->actionDelete_all_graphs,SIGNAL(triggered()),this,SLOT(removeAllGraphs()));
    connect(ui->actionDelete_fitted_graphs,SIGNAL(triggered()),this,SLOT(removeFittedGraphs()));
    ui->actionDelete_all_graphs->setEnabled(true);
    ui->actionDelete_fitted_graphs->setEnabled(true);
    disconnect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
    disconnect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
    connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
    connect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
    disconnect(ui->actionF_test, SIGNAL(triggered()), this, SLOT(fTest()));
    connect(ui->actionF_test, SIGNAL(triggered()), this, SLOT(fTest()));
    if(diffMode)
        changeDiffMode(true);
}

QString CDpal::calcSG(int model, int mode, double x, double y, double x2, double y2)
{
    //Calculates entropy or Gibbs free energy at 0 M denaturant
    if(mode==0)//Thermal denaturation, Calculate entropy
    {
        if(model==1 && y!=0.0) //N-D model
            return QString::number(x/y);
        else if(y!=0.0 && y2!=0.0) //N-I-D, N2-2I-2D and N2-I2-2D models
            return QString::number(x/y+x2/y2);
        else
            return "N/A";
    }
    else//Chemical denaturation, Calculate Gibbs free energy at 0 M denaturant
    {
        if(model==1) //N-D model
            return QString::number(x*y);
        else //N-I-D, N2-2I-2D and N2-I2-2D models
            return QString::number(x*y+x2*y2);
    }
}

QString CDpal::calcdSdG(int model, int submodel, int submodel2, int mode, double x, double y, double x2, double y2, double dx, double dy, double dx2, double dy2)
{
    //Error propagation for entropy or Gibbs free energy at 0 M denaturant
    //mode: 0=thermal, 1=chemical

    if(mode==0)//Thermal denaturation, Calculate entropy error
    {
        if(model==1) //N-D model
        {
            switch(submodel){
            case 1://No parameter fixed
                if(y!=0.0)
                    return QString::number(pow((pow(dx/y,2)+pow(x*dy/(y*y),2)),0.5));
                else
                    return "N/A";
            case 2://deltaH fixed
                if(y!=0.0)
                    return QString::number(pow(pow(x*dy/(y*y),2),0.5));
                else
                    return "N/A";
            case 3://Tm fixed
                if(y!=0.0)
                    return QString::number(pow(pow(dx/y,2),0.5));
                else
                    return "N/A";
            default:
                return "N/A";
            }
        }
        else //N-I-D, N2-2I-2D and N2-I2-2D models
        {
            if((y==0.0 && submodel!=0)|| (y2==0.0 && submodel2!=0) || (submodel==0 && submodel2==0))
                return "N/A";
            double dS(0.0);
            double dS1noFix(0.0), dS2noFix(0.0);
            dS1noFix=pow((pow(dx/y,2)+pow(x*dy/(y*y),2)),0.5);
            dS2noFix=pow((pow(dx2/y2,2)+pow(x2*dy2/(y2*y2),2)),0.5);
            double dS1(dS1noFix);
            double dS2(dS2noFix);
            double dS1Hfix(0.0), dS1Tmfix(0.0);
            dS1Hfix=pow(pow(x*dy/(y*y),2),0.5);
            dS1Tmfix=pow(pow(dx/y,2),0.5);
            double dS2Hfix(0.0), dS2Tmfix(0.0);
            dS2Hfix=pow(pow(x2*dy2/(y2*y2),2),0.5);
            dS2Tmfix=pow(pow(dx2/y2,2),0.5);

            switch(submodel){
            case 1://No parameter fixed
                break;
            case 2://dH1 fixed
                dS1=dS1Hfix;
                break;
            case 3://Tm1 fixed
                dS1=dS1Tmfix;
                break;
            default://Both fixed =0
                dS1=0.0;
                break;
            }
            switch(submodel2){
            case 1://No parameter fixed
                break;
            case 2://dH2 fixed
                dS2=dS2Hfix;
                break;
            case 3://Tm2 fixed
                dS2=dS2Tmfix;
                break;
            default://Both fixed =0
                dS2=0.0;
                break;
            }
            dS=pow(dS1*dS1+dS2*dS2,0.5);
            return QString::number(dS);
        }
    }
    else//Chemical denaturation, Calculate Gibbs free energy error at 0 M denaturant
    {
        if(model==1) //N-D model
        {
            switch(submodel){
            case 1://No parameter fixed
                return QString::number(pow((pow(dx*y,2)+pow(x*dy,2)),0.5));
            case 2://m fixed
                return QString::number(pow(pow(x*dy,2),0.5));
            case 3://Cm fixed
                return QString::number(pow(pow(dx*y,2),0.5));
            default:
                return "N/A";
            }
        }
        else //N-I-D, N2-2I-2D and N2-I2-2D models
        {
            if(submodel==0 && submodel2==0)
                return "N/A";
            double dG(0.0);
            double dG1noFix(0.0), dG2noFix(0.0);
            dG1noFix=pow((pow(dx*y,2)+pow(x*dy,2)),0.5);
            dG2noFix=pow((pow(dx2*y2,2)+pow(x2*dy2,2)),0.5);
            double dG1(dG1noFix);
            double dG2(dG2noFix);
            double dG1mfix(0.0), dG1Cmfix(0.0);
            dG1mfix=pow(pow(x*dy,2),0.5);
            dG1Cmfix=pow(pow(dx*y,2),0.5);
            double dG2mfix(0.0), dG2Cmfix(0.0);
            dG2mfix=pow(pow(x2*dy2,2),0.5);
            dG2Cmfix=pow(pow(dx2*y2,2),0.5);

            switch(submodel){
            case 1://No parameter fixed
                break;
            case 2://m1 fixed
                dG1=dG1mfix;
                break;
            case 3://Cm1 fixed
                dG1=dG1Cmfix;
                break;
            default://Both fixed =0
                dG1=0.0;
                break;
            }
            switch(submodel2){
            case 1://No parameter fixed
                break;
            case 2://m2 fixed
                dG2=dG2mfix;
                break;
            case 3://Cm2 fixed
                dG2=dG2Cmfix;
                break;
            default://Both fixed =0
                dG2=0.0;
                break;
            }
            dG=pow(dG1*dG1+dG2*dG2,0.5);
            return QString::number(dG);
        }
    }
}


void CDpal::loadStyle()
{
    //Load a preset for the graph style
    loadpreset lDialog;
    lDialog.setWindowFlags(lDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    lDialog.setWindowModality(Qt::ApplicationModal);
    style fitStyle;
    style graphStyle;
    QVector< style > fsVec;
    QVector<style> gVec;
    if(lDialog.exec())
    {
        //Ok button was pressed and format is ok
        extern QVector<QString> styleVec;
        for(int i(0); i<styleVec.size(); i++)
        {
            std::istringstream iss(mconvert(styleVec[i]));
            std::string sub;
            int counter = 0;
            bool fit(false);
            while(iss>>sub)
            {
                switch(counter)
                {
                case 0:
                    if(sub=="1")
                        fit=true;
                    break;
                case 1:
                    if(fit)
                        fitStyle.pen.setColor(atoi(sub.c_str()));
                    else
                        graphStyle.pen.setColor(atoi(sub.c_str()));
                    break;
                case 2:
                    if(fit)
                    {
                        fitStyle.pen.setWidth(atoi(sub.c_str()));
                        fsVec.push_back(fitStyle);
                    }
                    else
                        graphStyle.pen.setWidth(atoi(sub.c_str()));
                    break;
                case 3:
                    if(!fit)
                    {
                        QCPScatterStyle orn;
                        switch(atoi(sub.c_str()))
                        {
                        case 2: orn=QCPScatterStyle::ssCross;
                            break;
                        case 3: orn=QCPScatterStyle::ssPlus;
                            break;
                        case 4: orn=QCPScatterStyle::ssCircle;
                            break;
                        case 5: orn=QCPScatterStyle::ssDisc;
                            break;
                        case 6: orn=QCPScatterStyle::ssSquare;
                            break;
                        case 7: orn=QCPScatterStyle::ssDiamond;
                            break;
                        case 8: orn=QCPScatterStyle::ssStar;
                            break;
                        case 9: orn=QCPScatterStyle::ssTriangle;
                            break;
                        case 10: orn=QCPScatterStyle::ssTriangleInverted;
                            break;
                        case 11: orn=QCPScatterStyle::ssCrossSquare;
                            break;
                        case 12: orn=QCPScatterStyle::ssPlusSquare;
                            break;
                        case 13: orn=QCPScatterStyle::ssCrossCircle;
                            break;
                        case 14: orn=QCPScatterStyle::ssPlusCircle;
                            break;
                        case 15: orn=QCPScatterStyle::ssPeace;
                            break;
                        default : orn=QCPScatterStyle::ssDisc;
                            break;
                        }
                        graphStyle.ornament=orn;
                        gVec.push_back(graphStyle);
                    }
                    break;
                }
                counter++;
            }
        }
        //Apply the loaded style to current project
        int fitC(0);
        int graphC(0);
        for(int i(0); i<ui->CDplot->graphCount();i++)
        {
            bool isFit(false);
            QString str= ui->CDplot->graph(i)->name();
            if(str.length()>4)
                for(int j=0; j<str.length()-4; j++)
                {
                    if(str[j]=='(' && str[j+1]=='f' && str[j+2]=='i' && str[j+3]=='t' && str[j+4]==':')
                    {
                        isFit=true;
                        break;
                    }
                }
            if(isFit && fitC<fsVec.size())
            {
                ui->CDplot->graph(i)->setPen(fsVec[fitC].pen);
                fitC++;
            }
            else if(!isFit && graphC<gVec.size())
            {
                ui->CDplot->graph(i)->setPen(gVec[graphC].pen);
                ui->CDplot->graph(i)->setScatterStyle(gVec[graphC].ornament);
                graphC++;
            }
        }
        ui->CDplot->replot();
    }
}

void CDpal::saveStyle()
{
    //Save a preset for the graph style
    //Presets are placed in the shared preset folder of the installation directory
    extern QVector<bool> isFitVec;
    extern QVector<QPen> penVec;
    extern QVector<QCPScatterStyle> ornamentVec;
    isFitVec.clear();
    penVec.clear();
    ornamentVec.clear();

    for(int i=0; i<ui->CDplot->graphCount();i++)
    {
        bool isFit(false);
        QString str= ui->CDplot->graph(i)->name();
        if(str.length()>4)
            for(int j=0; j<str.length()-4; j++)
            {
                if(str[j]=='(' && str[j+1]=='f' && str[j+2]=='i' && str[j+3]=='t' && str[j+4]==':')
                {
                    isFit=true;
                    break;
                }
            }
        if(isFit)
            isFitVec.push_back(true);
        else
            isFitVec.push_back(false);
        ornamentVec.push_back(ui->CDplot->graph(i)->scatterStyle());
        QPen pen;
        pen.setColor(ui->CDplot->graph(i)->pen().color());
        pen.setWidth(ui->CDplot->graph(i)->pen().width());
        penVec.push_back(pen);
    }

    savePreset sDialog;
    sDialog.setWindowFlags(sDialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    sDialog.setWindowModality(Qt::ApplicationModal);
    if(sDialog.exec())
    {
        //Ok button was pressed
    }
}

//Code for fitting first derivatives
void CDpal::on_clearButtonDiff_clicked()
{
    ui->aEditDiff->clear();
    ui->tmEditDiff->clear();
    ui->deltaEditDiff->clear();
    ui->aBoxDiff->setChecked(0);
    ui->tmBoxDiff->setChecked(0);
    ui->deltaBoxDiff->setChecked(0);
}

void CDpal::on_fitDiff_clicked()
{
    //Fit derivative
    bool ok(false);
    double tm(ui->tmEditDiff->text().toDouble(&ok));
    if(!ok)
    {
        QMessageBox::warning(this, "Error","Tm is not a numerical value. Aborting.",QMessageBox::Ok);
        return;
    }
    double dH(ui->deltaEditDiff->text().toDouble(&ok));
    if(!ok)
    {
        QMessageBox::warning(this, "Error","dH is not a numerical value. Aborting.",QMessageBox::Ok);
        return;
    }
    double a(ui->aEditDiff->text().toDouble(&ok));
    if(!ok)
    {
        QMessageBox::warning(this, "Error","The scaling factor \'a\' is not a numerical value. Aborting.",QMessageBox::Ok);
        return;
    }
    if(ui->graphBoxDiff->currentText().contains("(fit:"))
    {
        QMessageBox::StandardButton dialog;
        dialog = QMessageBox::warning(this, "Error",
                                      "Cannot fit already fitted data. Aborting.",
                                      QMessageBox::Ok);
    }
    else
    {
        for(int i(0); i<ui->CDplot->graphCount(); ++i)
        {
            if(ui->CDplot->graph(i)->name() == ui->graphBoxDiff->currentText())
            {
                autoFitDiff(ui->graphBoxDiff->currentIndex(), true, dH, tm, a);
                return;
            }
        }
    }
}

void CDpal::on_autoFitDiff_clicked()
{
    //Autofit diff
    if(ui->graphBoxDiff->currentText().contains("(fit:"))
    {
        QMessageBox::StandardButton dialog;
        dialog = QMessageBox::warning(this, "Error",
                                      "Cannot fit already fitted data. Aborting.",
                                      QMessageBox::Ok);
    }
    else
    {
        for(int i(0); i<ui->CDplot->graphCount(); ++i)
        {
            if(ui->CDplot->graph(i)->name() == ui->graphBoxDiff->currentText())
            {
                autoFitDiff(ui->graphBoxDiff->currentIndex(), false, 0.0, 0.0, 0.0);
                return;
            }
        }
    }
}

void CDpal::on_autofitAllDiff_clicked()
{
    //Autofit all diff
    int max(ui->CDplot->graphCount());
    for(int i(0); i< max; ++i)
    {
        if(!ui->CDplot->graph(i)->name().contains("(fit:"))
            autoFitDiff(i, false, 0.0, 0.0, 0.0);
    }
}

void CDpal::autoFitDiff(int idx, bool manual, double mdH, double mtm, double ma)
{
    std::vector< double > a, x, y, errVal, params;
    std::vector< bool > fixed;
    x.resize(ui->CDplot->graph(idx)->data()->values().count());
    y.resize(ui->CDplot->graph(idx)->data()->values().count());
    errVal.resize(ui->CDplot->graph(idx)->data()->values().count());
    params.resize(3);
    fixed.resize(3);
    a.resize(3);
    //Find Tm estimate == highest value
    double tmComp(-9e99);
    double tm(0);
    for(int j(0); j<ui->CDplot->graph(idx)->data()->values().count(); ++j)
    {
        if(tmComp < ui->CDplot->graph(idx)->data()->values().at(j).value)
        {
            tmComp = ui->CDplot->graph(idx)->data()->values().at(j).value;
            tm = ui->CDplot->graph(idx)->data()->values().at(j).key;
        }
        x[j] = ui->CDplot->graph(idx)->data()->values().at(j).key;
        y[j] = ui->CDplot->graph(idx)->data()->values().at(j).value;
        errVal[j] = 1.0;
    }
    ui->deltaEditDiff->setText("350");
    ui->tmEditDiff->setText(QString::number(tm));
    double dH(350000);
    double aVal(1.0e-5);
    if(manual)
    {
        dH = mdH*1000.0;
        tm = mtm;
        aVal = ma;
    }
    params[0] = a[0] = dH;
    params[1] = a[1] = tm;
    params[2] = a[2] = aVal;
    if(manual)
    {
        fixed[0] = !ui->deltaBoxDiff->isChecked();
        fixed[1] = !ui->tmBoxDiff->isChecked();
        fixed[2] = !ui->aBoxDiff->isChecked();
    }
    else
    {
        ui->tmEditDiff->setText(QString::number(tm));
        ui->deltaEditDiff->setText("350");
        ui->aEditDiff->setText(QString::number(aVal));
        ui->deltaBoxDiff->setChecked(false);
        ui->tmBoxDiff->setChecked(false);
        ui->aBoxDiff->setChecked(false);
        fixed[0] = true;
        fixed[1] = true;
        fixed[2] = true;
    }
    int dof(x.size());

    for(unsigned int p=0; p<fixed.size(); p++)
    {
        if(fixed[p])
            --dof;
        if(params[p]>0)
            continue;
        if(fixed[p])
            params[p]=0.00000001;
    }

    void fitfunc(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
    CDdiffFitmrq fitData(x, y, errVal, params, fixed, fitfunc);
    //Gridsearch
    if(!manual)
    {
        std::vector< double > aLow;
        std::vector< double > aHigh;
        aLow.push_back(350000); //dH
        aHigh.push_back(350000);
        aLow.push_back(tm);//tm
        aHigh.push_back(tm);
        aLow.push_back(1e-20);//aVal
        aHigh.push_back(0.1);
        std::vector< int > steps;
        steps.push_back(1);
        steps.push_back(1);
        steps.push_back(100);
        fitData.gridSearch(aLow, aHigh, steps, true);
    }
    //
    fitData.fit();
    if(fitData.a.at(0)<0)
        fitData.a[0]*=-1.0;
    extern QString matrixError;
    if(matrixError!="")
    {
        QMessageBox::StandardButton dialog3;
        dialog3 = QMessageBox::warning(this, "CDpal",
                                       matrixError,
                                       QMessageBox::Ok);
        if(QMessageBox::Ok==dialog3)
            matrixError="";
        return;
    }
    CDdiffErrorSim myerr(x, y, errVal, fitData.a, fixed, fitfunc);
    myerr.simerror(0,1,0); //jackknife
    char *cfile=NULL;

    Output myoutput(x, y, errVal, fitData.a, fitfunc, myerr.jackerr,
                    fitData.covar, fitData.chisq, dof, cfile, cfile);
    myoutput.print(true);
    myoutput.plot(false, true); //smooth plotting (many data points)
    plotfit(idx);

    extern std::vector< std::vector< std::string> > resultStrVec;
    int fitNo=1;
    for(unsigned int u=0; u<resultStrVec.size(); u++)
    {
        QString str = ui->graphBoxDiff->itemText(idx)+"(fit:"+QString::number(fitNo)+")";
        if(resultStrVec[u][1] == mconvert(str))
        {
            fitNo++;
            u=-1;
        }
    }
    QString nN = ui->graphBoxDiff->itemText(idx) + "(fit:" + QString::number(fitNo) + ")";
    std::vector<std::string> tmpStrVec;
    extern std::string resultStr;
    tmpStrVec.push_back(resultStr);
    tmpStrVec.push_back(mconvert(nN));
    //Store fitting parameters for display upon selection
    QString parameters;
    if(ui->deltaEditDiff->text()!="")
        parameters="5 "+ui->deltaEditDiff->text()+" ";
    else
        parameters="5 0 ";
    if(ui->deltaBoxDiff->isChecked())
        parameters+="true ";
    else
        parameters+="false ";
    if(ui->tmEditDiff->text()!="")
        parameters+=ui->tmEditDiff->text()+" ";
    else
        parameters+="0 ";
    if(ui->tmBoxDiff->isChecked())
        parameters+="true ";
    else
        parameters+="false ";
    if(ui->aEditDiff->text()!="")
        parameters+=ui->aEditDiff->text()+" ";
    else
        parameters+="0 ";
    if(ui->aBoxDiff->isChecked())
        parameters+="true ";
    else
        parameters+="false ";
    tmpStrVec.push_back(mconvert(parameters));
    //
    resultStrVec.push_back(tmpStrVec);
    extern std::vector< std::string> rV;
    extern std::vector< std::vector< std::string> > rV2;
    for(int o=0; o<3; o++)
        if(!fixed[o])
            rV[4+o*2]="Fixed";
    rV2.push_back(rV);
    //Enable correct lineEdits and labels for corresponding model
    loadLabels(5);
    fillLabels(resultStrVec.size()-1, 5);
    //Change to result tab after fit
    ui->tabWidget_2->setCurrentIndex(1);
}

void CDpal::on_actionSimulate_data_triggered()
{
    //Simulate data
    if(diffMode)
    {
        QMessageBox::StandardButton dialog;
        dialog = QMessageBox::warning(this, "Warning",
                                      "Importing a new data set will delete all current data sets.\n"
                                      "This step cannot be undone.",
                                      QMessageBox::Ok | QMessageBox::Cancel);
        if( dialog == QMessageBox::Cancel)
            return;
        diffMode = false;
        changeDiffMode(false);
        ui->CDplot->clearGraphs();
        ui->CDplot->replot();
        updateTable(0);
        clearResults();
        extern std::vector< std::vector< std::string> > rV2;
        extern std::vector< std::vector< std::string> > resultStrVec;
        resultStrVec.clear();
        rV2.clear();
        ui->graphBox->clear();
        ui->graphBox_2->clear();
        ui->graphBox_3->clear();
        ui->graphBox_4->clear();
        ui->graphBoxDiff->clear();
    }
    if(!simDiag)
    {
        simDiag = new simulateDialog(this, chemical);
        disconnect(simDiag, SIGNAL(simulate()), this, SLOT(simulate()));
        connect(simDiag, SIGNAL(simulate()), this, SLOT(simulate()));
        disconnect(simDiag, SIGNAL(deleteDataset()), this, SLOT(deleteLastDataset()));
        connect(simDiag, SIGNAL(deleteDataset()), this, SLOT(deleteLastDataset()));
        disconnect(simDiag, SIGNAL(hideUI()), simDiag, SLOT(hide()));
        connect(simDiag, SIGNAL(hideUI()), simDiag, SLOT(hide()));
        simDiag->setModal(true);
    }
    simDiag->show();
}

void CDpal::simulate()
{
    double stepsize((simDiag->maxTemp - simDiag->minTemp)/(simDiag->datapoints-1));
    std::vector<double> x;
    x.resize(simDiag->datapoints);
    for(int i(0); i<x.size();++i)
        x[i] = simDiag->minTemp + i * stepsize;
    void (*func)(const double, std::vector< double > &, double &, std::vector< double > &);
    std::vector< double > parVec;

    switch(simDiag->model)
    {
    case 0: //ND
        if(chemical)
        {
            void fitfunc_two_state_chem(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            func = fitfunc_two_state_chem;
        }
        else
        {
            void function(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            func = function;
        }
        parVec.push_back(simDiag->dH);
        parVec.push_back(simDiag->tm);
        parVec.push_back(simDiag->mn);
        parVec.push_back(simDiag->md);
        parVec.push_back(simDiag->kn);
        parVec.push_back(simDiag->kd);
        parVec.push_back(simDiag->cp);
        break;
    case 1: //NID
        if(chemical)
        {
            void fitfunc_three_state_chem(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            func = fitfunc_three_state_chem;
        }
        else
        {
            void fitfunc_three_state(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            func = fitfunc_three_state;
        }
        parVec.push_back(simDiag->dH);
        parVec.push_back(simDiag->tm);
        parVec.push_back(simDiag->mn);
        parVec.push_back(simDiag->md);
        parVec.push_back(simDiag->kn);
        parVec.push_back(simDiag->kd);
        parVec.push_back(simDiag->cp);
        parVec.push_back(simDiag->dH2);
        parVec.push_back(simDiag->tm2);
        parVec.push_back(simDiag->mi);
        parVec.push_back(simDiag->ki);
        if(!chemical)
            parVec.push_back(simDiag->cp2);
        break;
    case 2: //N22I2D
        if(chemical)
        {
            void fitfunc_three_state_dimer1_chem(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            func = fitfunc_three_state_dimer1_chem;
        }
        else
        {
            void fitfunc_three_state_dimer1(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            func = fitfunc_three_state_dimer1;
        }
        parVec.push_back(simDiag->dH);
        parVec.push_back(simDiag->tm);
        parVec.push_back(simDiag->mn);
        parVec.push_back(simDiag->md);
        parVec.push_back(simDiag->kn);
        parVec.push_back(simDiag->kd);
        parVec.push_back(simDiag->cp);
        parVec.push_back(simDiag->dH2);
        parVec.push_back(simDiag->tm2);
        parVec.push_back(simDiag->mi);
        parVec.push_back(simDiag->ki);
        if(!chemical)
            parVec.push_back(simDiag->cp2);
        parVec.push_back(simDiag->conc);
        break;
    case 3: //NI22D
        if(chemical)
        {
            void fitfunc_three_state_dimer2_chem(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            func = fitfunc_three_state_dimer2_chem;
        }
        else
        {
            void fitfunc_three_state_dimer2(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
            func = fitfunc_three_state_dimer2;
        }
        parVec.push_back(simDiag->dH);
        parVec.push_back(simDiag->tm);
        parVec.push_back(simDiag->mn);
        parVec.push_back(simDiag->md);
        parVec.push_back(simDiag->kn);
        parVec.push_back(simDiag->kd);
        parVec.push_back(simDiag->cp);
        parVec.push_back(simDiag->dH2);
        parVec.push_back(simDiag->tm2);
        parVec.push_back(simDiag->mi);
        parVec.push_back(simDiag->ki);
        if(!chemical)
            parVec.push_back(simDiag->cp2);
        parVec.push_back(simDiag->conc);
        break;
    default://Derivative
        void fitfunc(const double x, std::vector< double > &a, double &y, std::vector< double > &dyda);
        func = fitfunc;
        parVec.push_back(simDiag->dH);
        parVec.push_back(simDiag->tm);
        parVec.push_back(simDiag->a);
        break;
    }
    std::vector< double > dydx(parVec.size());
    std::vector<double> yplot(x.size());
    const double mean = 0.0;
    const double stddev = simDiag->noise;
    std::mt19937 generator(std::random_device{}());
    auto dist = std::bind(std::normal_distribution<double>{mean, stddev},
                          std::mt19937(std::random_device{}()));

    double max=-1.0e99;
    double min=1.0e99;
    for (unsigned int i=0; i<static_cast<unsigned int>(x.size()); i++)
    {
        func(x[i], parVec, yplot[i], dydx);
        yplot[i] = yplot[i] + dist(generator); // Add noise
        if(yplot[i]>max)
            max=yplot[i];
        if(yplot[i]<min)
            min=yplot[i];
    }
    //Normalize y values
    std::vector<std::vector<std::string> > dataVec;
    for (unsigned int i=0; i<yplot.size(); i++)
    {
        std::vector<std::string> tmpVec;
        tmpVec.push_back(mconvert(x.at(i)));
        tmpVec.push_back(mconvert((yplot[i]-min)/(max-min)));
        dataVec.push_back(tmpVec);
    }
    extern bool customName;
    customName = true;
    extern QString currentName;
    currentName = "Simulated data: ";
    switch (simDiag->model)
    {
    case 0:
        currentName += "N->D";
        break;
    case 1:
        currentName += "N->I->D";
        break;
    case 2:
        currentName += "N->2I->2D";
        break;
    case 3:
        currentName += "N->I2->2D";
        break;
    default:
        currentName += "Derivative";
        break;
    }
    ui->fitDiff->setEnabled(true);
    ui->autofitAllDiff->setEnabled(true);
    ui->autoFitDiff->setEnabled(true);
    disconnect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
    disconnect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
    disconnect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
    disconnect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
    disconnect(ui->actionFit,SIGNAL(triggered()),this,SLOT(fitData()));
    connect(ui->actionFit,SIGNAL(triggered()),this,SLOT(fitData()));
    connect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
    ui->fitButton->setEnabled(true);
    connect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
    ui->fitButton_2->setEnabled(true);
    connect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
    ui->fitButton_3->setEnabled(true);
    connect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
    ui->fitButton_4->setEnabled(true);
    disconnect(ui->actionSave_style_preset, SIGNAL(triggered()), this, SLOT(saveStyle()));
    connect(ui->actionSave_style_preset, SIGNAL(triggered()), this, SLOT(saveStyle()));
    ui->actionSave_style_preset->setEnabled(true);
    disconnect(ui->actionLoad_style_preset_2, SIGNAL(triggered()), this, SLOT(loadStyle()));
    connect(ui->actionLoad_style_preset_2, SIGNAL(triggered()), this, SLOT(loadStyle()));
    ui->actionLoad_style_preset_2->setEnabled(true);
    disconnect(ui->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
    connect(ui->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
    ui->actionSave_Project->setEnabled(true);
    disconnect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveResults()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveResults()));
    ui->actionSave->setEnabled(true);
    disconnect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
    connect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
    ui->actionExport_data->setEnabled(true);
    disconnect(ui->actionDelete_all_graphs,SIGNAL(triggered()),this,SLOT(removeAllGraphs()));
    disconnect(ui->actionDelete_fitted_graphs,SIGNAL(triggered()),this,SLOT(removeFittedGraphs()));
    connect(ui->actionDelete_all_graphs,SIGNAL(triggered()),this,SLOT(removeAllGraphs()));
    connect(ui->actionDelete_fitted_graphs,SIGNAL(triggered()),this,SLOT(removeFittedGraphs()));
    ui->actionDelete_all_graphs->setEnabled(true);
    ui->actionDelete_fitted_graphs->setEnabled(true);
    disconnect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
    disconnect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
    connect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
    connect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
    disconnect(ui->actionF_test, SIGNAL(triggered()), this, SLOT(fTest()));
    connect(ui->actionF_test, SIGNAL(triggered()), this, SLOT(fTest()));
    if(simDiag->model == 4)
    {
        diffMode = true;
        changeDiffMode(false);
    }

    renderGraph(dataVec,0,0);
}

void CDpal::deleteLastDataset()
{
    if(!ui->CDplot->graphCount()) return;
    ui->graphBox->removeItem(ui->graphBox->count()-1);
    ui->graphBox_2->removeItem(ui->graphBox_2->count()-1);
    ui->graphBox_3->removeItem(ui->graphBox_3->count()-1);
    ui->graphBox_4->removeItem(ui->graphBox_4->count()-1);
    ui->graphBoxDiff->removeItem(ui->graphBoxDiff->count()-1);
    ui->CDplot->removeGraph(ui->CDplot->graphCount()-1);
    extern int highlightGraph;
    highlightGraph = -1;
    ui->CDplot->replot();
    updateTable(0);
    extern std::vector< std::vector< std::string> > resultStrVec;
    extern std::vector< std::vector< std::string> > rV2;
    for(unsigned int i=0; i<resultStrVec.size();i++)
        for(int j=0; j<ui->CDplot->graphCount(); j++)
        {
            if(ui->CDplot->graph(j)->name()==mconvert(resultStrVec[i][1]))
                break;
            else if(j==ui->CDplot->graphCount()-1)
            {
                resultStrVec[i].erase(resultStrVec[i].begin() + i);
                rV2[i].erase(rV2[i].begin() + i);
            }
        }
    //Disables functions if no data is present
    if(ui->CDplot->graphCount()==0)
    {
        ui->fitDiff->setEnabled(false);
        ui->autofitAllDiff->setEnabled(false);
        ui->autoFitDiff->setEnabled(false);
        disconnect(ui->fitButton,SIGNAL(clicked()),this,SLOT(fitData()));
        disconnect(ui->fitButton_2,SIGNAL(clicked()),this,SLOT(fitData()));
        disconnect(ui->fitButton_3,SIGNAL(clicked()),this,SLOT(fitData()));
        disconnect(ui->fitButton_4,SIGNAL(clicked()),this,SLOT(fitData()));
        disconnect(ui->actionFit,SIGNAL(triggered()),this,SLOT(fitData()));
        disconnect(ui->actionSave, SIGNAL(triggered()), this, SLOT(saveResults()));
        disconnect(ui->actionExport_data,SIGNAL(triggered()),this,SLOT(exportResults()));
        disconnect(ui->actionDelete_graph,SIGNAL(triggered()),this,SLOT(removeSelectedGraph()));
        disconnect(ui->actionDelete_all_graphs,SIGNAL(triggered()),this,SLOT(removeAllGraphs()));
        disconnect(ui->actionDelete_fitted_graphs,SIGNAL(triggered()),this,SLOT(removeFittedGraphs()));
        disconnect(ui->actionSave_Project, SIGNAL(triggered()), this, SLOT(saveProject()));
        disconnect(ui->actionLoad_style_preset_2, SIGNAL(triggered()), this, SLOT(loadStyle()));
        disconnect(ui->actionSave_style_preset, SIGNAL(triggered()), this, SLOT(saveStyle()));
        ui->actionSave_Project->setDisabled(true);
        ui->actionLoad_style_preset_2->setDisabled(true);
        ui->actionSave_style_preset->setDisabled(true);
        ui->actionDelete_graph->setDisabled(true);
        ui->actionDelete_all_graphs->setDisabled(true);
        ui->actionDelete_fitted_graphs->setDisabled(true);
        disconnect(ui->actionColor,SIGNAL(triggered()),this,SLOT(colorGraph()));
        disconnect(ui->actionChange_style,SIGNAL(triggered()),this,SLOT(changeOrnament()));
        disconnect(ui->actionChange_pen_width,SIGNAL(triggered()),this,SLOT(changeWidth()));
        disconnect(ui->actionAutofit, SIGNAL(triggered()), this, SLOT(Autofit()));
        disconnect(ui->actionAutofit_All, SIGNAL(triggered()), this, SLOT(AutofitAll()));
        ui->fitButton->setDisabled(true);
        ui->fitButton_2->setDisabled(true);
        ui->fitButton_3->setDisabled(true);
        ui->fitButton_4->setDisabled(true);
        ui->actionSave->setDisabled(true);
        ui->actionColor->setDisabled(true);
        ui->actionExport_data->setDisabled(true);
        ui->actionChange_style->setDisabled(true);
        ui->actionChange_pen_width->setDisabled(true);
        disconnect(ui->actionF_test, SIGNAL(triggered()), this, SLOT(fTest()));
    }
}
