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

#include "helpdialog.h"
#include "ui_helpdialog.h"
#include <iostream>
#include "mfunc.h"

helpDialog::helpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::helpDialog)
{
    ui->setupUi(this);
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
    setAttribute(Qt::WA_QuitOnClose, false);
    QIcon icon(windowIcon());
    Qt::WindowFlags flags = windowFlags();
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
    flags = flags & (~helpFlag);
    setWindowFlags(flags);
    setWindowIcon(icon);
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(acceptEvent()));
    connect(ui->topicList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(changeTopic()));
    connect(ui->infoBrowser, SIGNAL(anchorClicked(const QUrl &)), this, SLOT(anchorClicked(const QUrl &)));
}

helpDialog::~helpDialog()
{
    delete ui;
}

void helpDialog::acceptEvent()
{
    accept();
}

void helpDialog::anchorClicked(const QUrl &url)
{

    if(QUrl("openImport") == url)
    {
        ui->topicList->setCurrentRow(2);
        changeTopic();
    }
    else if(QUrl("openFit") == url)
    {
        ui->topicList->setCurrentRow(4);
        changeTopic();
    }
    else if(QUrl("openLinear") == url)
    {
        ui->topicList->setCurrentRow(5);
        changeTopic();
    }
    else if(QUrl("openSave") == url)
    {
        ui->topicList->setCurrentRow(6);
        changeTopic();
    }
    else if(QUrl("openMod") == url)
    {
        ui->topicList->setCurrentRow(3);
        changeTopic();
    }
    else if(QUrl("openWeb") == url)
    {
        QDesktopServices::openUrl(QUrl("http://onlinelibrary.wiley.com/doi/10.1002/pro.2809/abstract"));
    }
    else
    {
        QDesktopServices::openUrl(QUrl(url));
    }
}

void helpDialog::changeTopic()
{
    if(ui->topicList->currentRow()==0) //About CDpal
    {
        ui->infoBrowser->setHtml("<b>About CDpal</b><hr><br>"
                                 "This software is intended to be used for curve fitting of CD thermal or chemical "
                                 "denaturation data.<br><br>"
                                 "Copyright &copy; 2017 Markus Niklasson and Patrik Lundström<br><br>"
                                 "This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.<br>"
                                 "This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.<br><br>"
                                 "You should have received a copy of the GNU General Public License along with this program. If not, see <a href=\"http://www.gnu.org/licenses/\">http://www.gnu.org/licenses/</a>.<br><br>"

                                 "Programmers: Markus Niklasson and Patrik Lundström<br><br>"
                                 "Adress correspondence to: patlu@ifm.liu.se<br>"
                                 "Report bugs to: <br>&bull;&nbsp;&nbsp;marni@ifm.liu.se<br>&bull;&nbsp;&nbsp;patlu@ifm.liu.se<br><br>"
                                 "Date: 21 February, 2017<br>"
                                 "Version: 2.16<br>");
    }
    else if(ui->topicList->currentRow()==1) //Using the GUI
    {
        QString html;
        html ="<b>Using the GUI</b><hr><br>"
                "<img src= ':/img/file.png' width='50' height='50'><b>OPEN</b>: Use this button to add new datasets to CDpal. <a href=\"openImport\">Additional information</a><hr><br>"
                "<img src= ':/img/open.png' width='50' height='50'><b>OPEN PROJECT</b>: Use this button to open a saved CDpal session. <a href=\"openImport\">Additional information</a><hr><br>"
                "<img src= ':/img/save.png' width='50' height='50'><b>SAVE PROJECT</b>: Use this button to save the current project. <a href=\"openSave\">Additional information</a><hr><br>"
                "<img src= ':/img/printer.png' width='50' height='50'><b>SAVE GRAPH</b>: Use this button to save the current graph according to the current scale. <a href=\"openSave\">Additional information</a><hr><br>"
                "<img src= ':/img/export.png' width='50' height='50'><b>EXPORT DATA</b>: Use this button to export the datasets of any existing graph in CDpal. <a href=\"openSave\">Additional information</a><hr><br>"
              "<img src= ':/img/preset.png' width='50' height='50'><b>LOAD STYLE PRESET</b>: Use this button to load a custom style for your current project. <a href=\"openMod\">Additional information</a><hr><br>"
              "<img src= ':/img/preset.png' width='50' height='50'><b>SAVE STLYE PRESET</b>: Use this button to save the custom style of your current project. <a href=\"openMod\">Additional information</a><hr><br>"
                "<img src= ':/img/color.png' width='50' height='50'><b>CHANGE COLOR</b>: Use this button to change color of the currently selected dataset. <a href=\"openMod\">Additional information</a><hr><br>"
                "<img src= ':/img/point.png' width='50' height='50'><b>CHANGE STYLE</b>: Use this button to change the point style of the currently selected dataset. <a href=\"openMod\">Additional information</a><hr><br>"
                "<img src= ':/img/pen.png' width='50' height='50'><b>CHANGE PEN WIDTH</b>: Use this button to change the thickness of the line or shape of the currently selected dataset. <a href=\"openMod\">Additional information</a><hr><br>"
                "<img src= ':/img/deleteGraph.png' width='50' height='50'><b>DELETE</b>: Use these buttons to delete datasets. <a href=\"openMod\">Additional information</a><hr><br>"
                "<img src= ':/img/expand.png' width='50' height='50'><b>SCALE</b>: Use these buttons to change the axes scales. <a href=\"openMod\">Additional information</a><hr><br>"
                "<img src= ':/img/merge.png' width='50' height='50'><b>MERGE GRAPHS</b>: Use this button to merge all experimental data. <a href=\"openMod\">Additional information</a><hr><br>"
                "<img src= ':/img/fit.png' width='50' height='50'><b>FIT</b>: Use these buttons to fit data. <a href=\"openFit\">Additional information</a><hr><br>"
                "<img src= ':/img/ftest.png' width='50' height='50'><b>F-TEST</b>: Use this button to perform an F-Test on fitted datasets. <a href=\"openFit\">Additional information</a><hr><br>";
        QString css;
        css = "font-size: 11px;";
        QTextDocument *doc = new QTextDocument(this);
        doc->addResource( QTextDocument::StyleSheetResource, QUrl( "format.css" ), css);
        doc->setHtml( html );
        ui->infoBrowser->setDocument( doc );
    }
    else if(ui->topicList->currentRow()==2) //Importing data
    {
        QString html;
        html ="<b>Importing data</b><hr><br>"
                "<img src= ':/img/file.png' width='50' height='50'><b>OPEN</b>: Use this button to add new datasets to CDpal.<br>"
                "<br>Single or multiple datasets may be added simultaneously to CDpal. During import, CDpal will scan the files for compatibility issues.<br>"
                "The user may specify a custom format for the imported data. The custom format can be saved as a preset and loaded in future sessions.<br>"
                "The format that was used during the previous session will always be set as the default format when new data is imported.<br>"
                "To specify a custom format the user may enter a word or line that CDpal will scan the file for. When this pattern is found CDpal will skip the number of specified header rows before reading data. The pattern can be set to occur multiple times before data processing.<br>"
                "The input data is temperature &deg;C or denaturant concentration and CD signal. The user must specify the columns that contain this data. CDpal will import data until one of the following conditions is fulfilled: 1) End of file is reached 2) Non-numerical data is imported 3) Temperature is no longer increasing (For thermal denaturation data)<br><br>"
                "When importing data there is the option to normalize the data between zero and one. This is a convenient function best used when studying multiple datasets at once. However, we recommend the user to always normalize input data.<hr><br>"
                "<img src= ':/img/open.png' width='50' height='50'><b>OPEN PROJECT</b>: Use this button to open a saved CDpal session.<br>"
                "<br>A single project file (*.proj) can be imported into CDpal. The project file includes all necessary data for resuming a prior session.<br>"
                "This means that original data files of the saved project are not needed to restore the project to the saved state.";
        QString css;
        css = "font-size: 11px;";
        QTextDocument *doc = new QTextDocument(this);
        doc->addResource( QTextDocument::StyleSheetResource, QUrl( "format.css" ), css);
        doc->setHtml( html );
        ui->infoBrowser->setDocument( doc );
    }
    else if(ui->topicList->currentRow()==3) //Customizing data
    {
        QString html;
        html ="<b>Customizing data</b><hr><br>"
              "<img src= ':/img/preset.png' width='50' height='50'><b>LOAD STYLE PRESET</b>: Use this button to load an existing custom preset and directly use it in your current project. The custom preset includes information about graph colors, point styles and pen width. Select a preferred preset and verify your selection with OK.<hr><br>"
              "<img src= ':/img/preset.png' width='50' height='50'><b>SAVE STYLE PRESET</b>: Use this button to save a custom preset based on the current project. Saving a preset will save the state of graph colors, point styles and pen width. Name the preset as preferred and save with OK.<hr><br>"
                "<img src= ':/img/color.png' width='50' height='50'><b>CHANGE COLOR</b>: Use this button to change color of a dataset. Select a dataset by clicking the plot area or the legend and then click CHANGE COLOR. Pick a color and verify your selection with Ok.<hr><br>"
                "<img src= ':/img/point.png' width='50' height='50'><b>CHANGE STYLE</b>: Use this button to change the point style of a dataset. Select a dataset by clicking the plot area or the legend and then click CHANGE STYLE. Select a point style from the menu and verify your selection with Ok.<hr><br>"
                "<img src= ':/img/pen.png' width='50' height='50'><b>CHANGE PEN WIDTH</b>: Use this button to change the thickness of the line or shape of a dataset. Select a dataset by clicking the plot area or the legend and then click CHANGE PEN WIDTH. Specify a thickness in the spin box and verify your selection with Ok.<hr><br>"
                "<img src= ':/img/deleteGraph.png' width='50' height='50'><b>DELETE</b>: Use these buttons to delete the currently selected dataset. To remove all datasets or all fitted datasets click the corresponding button.<hr><br>"
                "<img src= ':/img/expand.png' width='50' height='50'><b>SCALE</b>: Use these buttons to set the axes scales. Click \"Autoscale\" to have CDpal automatically adjust the axes for all datasets. For custom scaling, select \"Scale graph\" followed by \"Custom scale\" and enter desired axes scales. Verify the scaling with Ok.<hr><br>"
                "<img src= ':/img/merge.png' width='50' height='50'><b>MERGE GRAPHS</b>: Use this button to merge all experimental data. NOTE! We recommend the user to normalize all data before merging. Also, any fitted data will be lost when merging datasets.<hr><br>"
                "<b>Delete selected data</b>: Use this button to remove data points from a selected dataset. Select a dataset by clicking the plot area or the legend. In the table view, select data points that will be deleted and remove them by clicking \"Delete selected data\".<hr><br>"
                "CDpal lets you change the name of axes, title and datasets. Simply doubleclick an element to rename it.<br><br>"
                "Right-click the legend to move it to a different position.<br><br>";
        QString css;
        css = "font-size: 11px;";
        QTextDocument *doc = new QTextDocument(this);
        doc->addResource( QTextDocument::ImageResource, QUrl( "file.png" ), QPixmap( ":file" ) );
        doc->addResource( QTextDocument::StyleSheetResource, QUrl( "format.css" ), css);
        doc->setHtml( html );
        ui->infoBrowser->setDocument( doc );
    }
    else if(ui->topicList->currentRow()==4) //Fit data
    {
        QString html;
        html ="<b>Fitting data</b><hr><br>"
                "<img src= ':/img/fit.png' width='50' height='50'><b>FIT</b>: Use this button to fit data.<br><br>"
                "<b>Thermal denaturation data</b><br>"
                "To fit thermal denaturation data, first select the correct mode from the main menu and import at least one dataset. "
                "Select a desired model and a dataset from the \"Fitted graph\" dropdown menu or select a dataset by clicking on a graph. "
                "Enter estimates for &Delta;H, T<sub>m</sub>, &Delta;Cp and intercepts and slopes for the native and denatured regions, respectively. "
                "For multi-transitional models, intercept and slope for the intermediate region are needed. "
                "Click \"Fit\" to fit the dataset with the current parameters.<br><br>"
                "Estimate T<sub>m</sub> by determining where the sigmoidal shape has the highest increase in CD signal per temperature unit."
                " For &Delta;H, try a value in the range [200,500] kJ/mol. If the fit is not satisfactory, try again with a different value.<br><br>"
                "For &Delta;Cp, we recommend initially setting this value as fixed to \"0\" and find a good fit for the dataset. Then proceed to test if a better fit can be achieved with different values of &Delta;Cp. To evaluate different fits, use the included F-Test.<br><br>"
                "<b>Chemical denaturation data</b><br>"
                "To fit chemical denaturation data, first select the correct mode from the main menu and import at least one dataset. "
                "Select a desired model and a dataset from the \"Fitted graph\" dropdown menu or select a dataset by clicking on a graph. "
                "Enter estimates for the m-value, C<sub>m</sub> and intercepts and slopes for the native and denatured regions, respectively. "
                "For multi-transitional models, intercept and slope for the intermediate region are needed. "
                "Enter the temperature for the conducted experiment and the protein concentration, for multi-transitional models. "
                "Click \"Fit\" to fit the dataset with the current parameters.<br><br>"
                "Estimate C<sub>m</sub> by determining where the sigmoidal shape has the highest increase in CD signal per temperature unit."
                " For the m-value, try a value in the range [0.1,1.0] kJ&bull;mol<sup>-1</sup>&bull;M<sup>-1</sup>. If the fit is not satisfactory, try again with a different value. "
                "To evaluate different fits, use the included F-Test.<hr><br>"
                "<b>Linear regression</b><br>"
                "To simplify the fitting process, CDpal can automatically apply linear regression to the native, intermediate and denatured regions to estimate intercepts and slopes. "
                "Read more about using this function <a href=\"openLinear\">here</a>.<hr><br>"
                "<b>Results</b><br>"
                "The result of the fitting is displayed in the upper right browser. Sum of residuals is a measurement of how accurate the fitting is, where low values indicate a good fit."
                " The \"Fitted\" column includes the fitted parameters final values and the \"Jackknife error\" column shows the estimated error for each fitted parameter."
                " It is recommended to leave the \"Fixed value\" checkboxes unchecked as they restrict the fitting. "
                "However, under special circumstances such as for comparison reasons, the user may fix the values by checking the checkboxes.<br><br> "
                "The results are stored internally and each time you select a fitted graph from the plot area or the legend the lower right browser will be updated with the results from made fitting.<hr><br>"
                "<b>Automatic fitting</b><br>"
                "CDpal can automatically fit data for the \"N &rarr; D\" and the \"N &rarr; I &rarr; D\" model if prompted. Note that the chemical denaturation mode requires the experiment temperature to be specified. To switch between different autofit models click \"Autofit\" in the toolbar.<br><b>\"Autofit\"</b>: This function will attempt to automatically fit the currently selected dataset in the \"Fitted graph\" dropdown menu.<br>"
                "<b>\"Autofit All\"</b>: This function will attempt to automatically fit all datasets imported into CDpal.<br><br>"
                "NOTE! The automatic fitting algorithm is not, nor will it ever be, perfectly robust. If automatic fitting fails, manual fitting is required.<hr><br>"
                "<img src= ':/img/ftest.png' width='50' height='50'><b>F-TEST</b>: Use this button to perform an F-Test on fitted datasets.<br><br>"
                "To perform an F-Test two different fits of an experimental dataset must exist. Tick the checkboxes for the fitted datasets and click \"Calculate\" to perform an F-Test. The p-value will be displayed next to the calculate button.";
        QString css;
        css = "font-size: 11px;";
        QTextDocument *doc = new QTextDocument(this);
        doc->addResource( QTextDocument::StyleSheetResource, QUrl( "format.css" ), css);
        doc->setHtml( html );
        ui->infoBrowser->setDocument( doc );
    }
    else if(ui->topicList->currentRow()==5) //Linear regression
    {
        QString html;
        html ="<b>Linear regression</b><hr><br>"
                "<b>Linear regression</b>: Use this function to estimate native, intermediate and denatured start parameters.<br><br>"
                "Select a dataset and highlight a linear region in the native state by selecting datapoints in the table. Click \"Set\" (Native). Linear regression will be performed and the result of which will be displayed as start parameters.<br>"
                "Repeat the process for the intermediate and denatured state by selecting a linear region in these regions. Click \"Set\" (Intermediate/Denatured) to calculate start parameters.";
        QString css;
        css = "font-size: 11px;";
        QTextDocument *doc = new QTextDocument(this);
        doc->addResource( QTextDocument::StyleSheetResource, QUrl( "format.css" ), css);
        doc->setHtml( html );
        ui->infoBrowser->setDocument( doc );
    }
    else if(ui->topicList->currentRow()==6) //Saving data
    {
        QString html;
        html ="<b>Saving data</b><hr><br>"
                "<img src= ':/img/printer.png' width='50' height='50'><b>SAVE GRAPH</b>: Use this button to save the current graph according to the current scale.<br>"
                "The graph can be saved in .PNG, .TIFF and .JPEG formats. Currently, CDpal does not offer saving files in postscript format. For this reason we have included the \"EXPORT\" function.<hr><br>"
                "<img src= ':/img/export.png' width='50' height='50'><b>EXPORT DATA</b>: Use this button to export the datasets of any existing graph in CDpal.<br>"
                "Any available dataset can be exported from CDpal to a text file. The text file can be used directly with plotting software.<br>"
                "It is recommended to use EXPORT as CDpal does not support saving the graph in postscript format.<br>"
                "NOTE! When using EXPORT CDpal will replace textfiles with the same name as the outputfile. For this reason, it is recommended to export all data to an empty directory.<hr><br>"
                "<img src= ':/img/save.png' width='50' height='50'><b>SAVE PROJECT</b>: Use this button to save the current project. The project will be saved as a (*.proj) file that single handedly can restore the entire project."
                " This means that a project file can be opened without access to the original CD data.";
        QString css;
        css = "font-size: 11px;";
        QTextDocument *doc = new QTextDocument(this);
        doc->addResource( QTextDocument::StyleSheetResource, QUrl( "format.css" ), css);
        doc->setHtml( html );
        ui->infoBrowser->setDocument( doc );
    }
    else if(ui->topicList->currentRow()==7) //Shortcuts
    {
        QString html;
        html ="<b>Shortcuts</b><hr><br>"
                "Ctrl+O&nbsp;&nbsp;Open File<br><br>"
                "Ctrl+Shift+O&nbsp;&nbsp;Open project<br><br>"
                "Ctrl+S&nbsp;&nbsp;Export data<br><br>"
                "Ctrl+Shift+S&nbsp;&nbsp;Save project<br><br>"
                "Ctrl+P&nbsp;&nbsp;Save graph<br><br>"
                "Ctrl+Q&nbsp;&nbsp;Quit CDpal<br><br>"
                "Ctrl+M&nbsp;&nbsp;Merge graphs<br><br>"
                "Ctrl+Z&nbsp;&nbsp;Autoscale<br><br>"
                "Ctrl+F&nbsp;&nbsp;Fit<br><br>"
                "F1&nbsp;&nbsp;Help<br><br>"
                "Ctrl+D&nbsp;&nbsp;Clear parameters<br><br>"
                "Delete&nbsp;&nbsp;Delete selected graph<br><br>"
                "Ctrl+R&nbsp;&nbsp;Autofit<br><br>"
                "Ctrl+T&nbsp;&nbsp;Autofit All<br><br>"
                "Alt+F&nbsp;&nbsp;F-Test<br><br>"
                "Ctrl+L&nbsp;&nbsp;Toggle table widget<br><br>"
                "Alt+L&nbsp;&nbsp;Toggle model widget";
#ifdef Q_OS_MAC
        html ="<b>Shortcuts</b><hr><br>"
                "cmd+O&nbsp;&nbsp;Open File<br><br>"
                "cmd+Shift+O&nbsp;&nbsp;Open project<br><br>"
                "cmd+S&nbsp;&nbsp;Export data<br><br>"
                "cmd+Shift+S&nbsp;&nbsp;Save project<br><br>"
                "cmd+P&nbsp;&nbsp;Save graph<br><br>"
                "cmd+Q&nbsp;&nbsp;Quit CDpal<br><br>"
                "cmd+M&nbsp;&nbsp;Merge graphs<br><br>"
                "cmd+Z&nbsp;&nbsp;Autoscale<br><br>"
                "cmd+F&nbsp;&nbsp;Fit<br><br>"
                "cmd+D&nbsp;&nbsp;Clear parameters<br><br>"
                "cmd+R&nbsp;&nbsp;Autofit<br><br>"
                "cmd+T&nbsp;&nbsp;Autofit All<br><br>"
                "Alt+F&nbsp;&nbsp;F-Test<br><br>"
                "cmd+L&nbsp;&nbsp;Toggle table widget<br><br>"
                "Alt+L&nbsp;&nbsp;Toggle model widget";
#endif
        QString css;
        css = "font-size: 11px;";
        QTextDocument *doc = new QTextDocument(this);
        doc->addResource( QTextDocument::StyleSheetResource, QUrl( "format.css" ), css);
        doc->setHtml( html );
        ui->infoBrowser->setDocument( doc );
    }
    else if(ui->topicList->currentRow()==8) //Citation
    {
        addCitation();
    }
    else if(ui->topicList->currentRow()==9) //Changelog
    {
        QString html;
        html ="<b>Changelog</b><hr><br>"
              "<b>CDpal v 2.16</b><br><br>"
              "<b>Date:</b> 21, February 2017<br><br>"
              "<b>Notes:</b> Migrated the software to GitHub and made necessary changes linking to the new site within the application.<br>"
              "Fixed a library dependency issue caused for Mac users.<hr><br>"
              "<b>CDpal v 2.15</b><br><br>"
              "<b>Date:</b> 28, October 2015<br><br>"
              "<b>Notes:</b> Added functionality for saving and loading graph style presets.<br>"
              "Added the possibility to name graphs during import, convenient to use when handling multiple datasets.<br>"
              "Added transparency to format errors, users can now see why a file did not properly load.<br>"
              "Fixed a bug where changing the color of a dataset also caused the pen width of the dataset to reset.<hr><br>"
              "<b>CDpal v 2.11</b><br><br>"
              "<b>Date:</b> 14, August 2015<br><br>"
              "<b>Notes:</b> Cosmetic changes to font sizes of the title and axes were made.<hr><br>"
              "<b>CDpal v 2.10</b><br><br>"
              "<b>Date:</b> 2, June 2015<br><br>"
              "<b>Notes:</b> Added the possibility to fit chemical denatuartion data with the new mode \"Chemical denaturation\".<br>"
              "GUI and affected functions were updated to accommodate for the new curve fitting mode.<br>"
              "Automatic fitting of the \"N &rarr; I &rarr; D\" model was implemented.<br>"
              "Added a return to main menu button.<br>"
              "CDpal now automatically checks for updates if an internet connection can be established.<br>"
              "Fixed a bug that caused linear regression to continuously fail after failing once.<hr><br>"
              "<b>CDpal v 2.01</b><br><br>"
              "<b>Date:</b> 23, April 2015<br><br>"
              "<b>Notes:</b> Minor bug fixes concerning issues with data import.<hr><br>"
              "<b>CDpal v 2.0</b><br><br>"
              "<b>Date:</b> 16, February 2015<br><br>"
              "<b>Notes:</b> Several functions of CDpal were optimized for performance and user-friendliness.<br>"
              "CDpal sessions can now be saved and restored at convenience.<br>"
              "The user may now change the line width of point styles and fitted lines.<br>"
              "The GUI now allows hiding/showing \"Models\" and \"Table & Results\" modules.<br>"
              "The user may export results from curve fitting to a file in the \"Export data\" function.<br>"
              "Selecting a fitted data set will automatically set prior start parameters for the selected data set.<hr><br>"
              "<b>CDpal v 1.5</b><br><br>"
              "<b>Date:</b> 19, January 2015<br><br>"
              "<b>Notes:</b> Updated the GUI to be more user-friendly and include new functions.<br>"
              "CDpal now supports low-resolution monitors.<br>"
              "Added custom file format support.<br>"
              "Added the possibility to perform an F-Test of fitted data.<br>"
              "Added three advanced models for fitting experimental data involving an intermediate state.<br>"
              "The user may now select a graph for fitting by clicking on it.<br>"
              "Fixed an issue where CDpal would crash when all parameters were set as fixed values.<br>"
              "Fixed an issue where the user could not save the graph in .TIFF or .JPEG formats.<hr><br>"
              "<b>CDpal v 1.0</b><br><br>"
              "<b>Date:</b> 16, December 2014<br><br>"
              "<b>Notes:</b> CDpal was released.<hr><br>";
        QString css;
        css = "font-size: 11px;";
        QTextDocument *doc = new QTextDocument(this);
        doc->addResource( QTextDocument::StyleSheetResource, QUrl( "format.css" ), css);
        doc->setHtml( html );
        ui->infoBrowser->setDocument( doc );
    }
}
void helpDialog::addCitation()
{
    QString html;
    html ="<b>Citation</b><hr><br>"
            "<b>CDpal v 2.16</b><br><br>"
            "This program and its related software and documentation are provided as is."
            " The authors make absolutely no warranties, either expressed or implied,  as to any matter whatsoever with respect to the software."
            " In particular, any and all warranties of merchantability and fitness for any particular purpose are expressly excluded."
            " In no event will the authors be liable for any loss of profits, any incidental, special, exemplary or consequential"
            " damages of any nature whatsoever (including without limitation, loss of use or other commercial or research loss) arising out"
            " of or relating to the use or performance of the software.<br><br>"
            "If you use this program to conduct academic research you should cite our published manuscript:<br><br>"
            "<a href=\"openWeb\">Link to Protein Science paper</a>";
    QString css;
    css = "font-size: 11px;";
    QTextDocument *doc = new QTextDocument(this);
    doc->addResource( QTextDocument::StyleSheetResource, QUrl( "format.css" ), css);
    doc->setHtml( html );
    ui->infoBrowser->setDocument( doc );
}
