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

#include "customformat.h"
#include "ui_customformat.h"
#include "globals.h"

customFormat::customFormat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::customFormat)
{
    ui->setupUi(this);
#ifdef Q_OS_LINUX
    window()->setFont(QFont( "Arial", 8));
#endif
#ifdef Q_OS_MAC
    window()->setFont(QFont( "Arial",10));
    ui->saveButton->setMinimumWidth(80);
#endif
    extern int mode;
    if(mode==1)
    {
        ui->typeLabel->setText("Concentration data column");
        ui->stopBox->hide();
    }
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
    setAttribute(Qt::WA_QuitOnClose, false);
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(acceptEvent()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    QString appDir = QCoreApplication::applicationDirPath();
    appDir += "/settings.txt";
    std::ifstream file;
    file.open(mconvert(appDir).c_str(), std::ios::in);
    std::string str;
    int counter=0;
    while(getline(file, str))
    {
        if(counter==0)
        {
            std::istringstream iss(str);
            std::string sub;
            iss >> sub;
            if(sub!="0")
                ui->patternBox->setCurrentIndex(1);
        }
        else if(counter==1)
        {
            if(str!="EMPTY")
                ui->patternEdit->setText(mconvert(str));
            else
                ui->patternEdit->setText("");
        }
        else if(counter==2)
        {
            std::istringstream iss(str);
            std::string sub;
            iss >> sub;
            ui->skipBox->setValue(atoi(sub.c_str()));
        }
        else if(counter==3)
        {
            std::istringstream iss(str);
            std::string sub;
            iss >> sub;
            ui->headerBox->setValue(atoi(sub.c_str()));
        }
        else if(counter==5)
        {
            std::istringstream iss(str);
            std::string sub;
            iss >> sub;
            ui->cdBox->setValue(atoi(sub.c_str()));
        }
        else if(counter==4)
        {
            std::istringstream iss(str);
            std::string sub;
            iss >> sub;
            ui->tempBox->setValue(atoi(sub.c_str()));
        }
        else
            break;
        counter++;
    }
    file.clear();
    file.close();

    connect(ui->patternBox, SIGNAL(currentIndexChanged(int)), this, SLOT(preview()));
    connect(ui->patternEdit,SIGNAL(textChanged(QString)), this, SLOT(preview()));
    connect(ui->headerBox, SIGNAL(valueChanged(int)), this, SLOT(preview()));
    connect(ui->tempBox, SIGNAL(valueChanged(int)), this, SLOT(preview()));
    connect(ui->cdBox, SIGNAL(valueChanged(int)), this, SLOT(preview()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(savePreset()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadPreset2()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deletePreset()));
    connect(ui->skipBox, SIGNAL(valueChanged(int)), this, SLOT(preview()));
    connect(ui->stopBox, SIGNAL(toggled(bool)), this, SLOT(preview()));
    updatePreset();
    preview();
}

void customFormat::loadPreset2()
{
    loadPreset("");
}

customFormat::~customFormat()
{
    delete ui;
}

void customFormat::preview()
{
    QString preText="";
    if(ui->tempBox->value()==ui->cdBox->value())
    {
        ui->previewBrowser->setText("Invalid file format.\nTemperature data and CD signal column cannot be identical.");
        return;
    }
    if(ui->patternEdit->text()!="")
    {
        QString pattern;
        pattern = ui->patternEdit->text();
        if(ui->patternBox->currentIndex()==0)
        {
            for(int j=0; j<pattern.size(); j++)
                if(pattern[j]==' ')
                {
                    ui->previewBrowser->setText("Invalid file format.\nWhitespace is not allowed when searching a file for a word.\nUse \"line\" instead.");
                    return;
                }
        }
        preText= "...\n(The content of these rows will be skipped)\n...\n" +pattern+"\n";
        for(int i=0; i<ui->skipBox->value(); i++)
            preText+="...\n"+pattern+"\n";
    }
    for(int i=0; i<ui->headerBox->value(); i++)
        preText+="\n";
    extern int mode;
    for(int j=0; j<5; j++)
    {
        for(int i=1; i<=MAX(ui->tempBox->value(),ui->cdBox->value()); i++)
        {
            if(i==ui->tempBox->value())
            {
                if(mode==0)
                    preText+="TEMPERATURE_DATA_COLUMN     ";
                else
                    preText+="CONCENTRATION_DATA_COLUMN     ";
            }
            else if(i==ui->cdBox->value())
            {
                preText+="CD_SIGNAL_COLUMN     ";
            }
            else
            {
                preText+="IGNORED_VALUE     ";
            }
        }
        preText+="\n";
    }
    if(mode==0 && !ui->stopBox->isChecked())
        preText+="...\nDATA WILL BE IMPORTED UNTIL:\n1:END OF FILE\n2:BAD FORMAT\n...";
    else if(mode==0)
        preText+="...\nDATA WILL BE IMPORTED UNTIL:\n1:END OF FILE\n2:BAD FORMAT\n3:TEMPERATURE IS DECREASING\n...";
    else
        preText+="...\nDATA WILL BE IMPORTED UNTIL:\n1:END OF FILE\n2:BAD FORMAT\n...";
    ui->previewBrowser->setText(preText);
}

int customFormat::MAX(int i, int j)
{
    if(i>j)
        return i;
    return j;
}

void customFormat::loadPreset(QString fname)
{
    for(int i = 0; i < ui->presetWidget->count(); ++i)
    {
        if(ui->presetWidget->item(i)->isSelected() || fname == ui->presetWidget->item(i)->text())
        {
            QListWidgetItem* item = ui->presetWidget->item(i);
            QString appDir = QCoreApplication::applicationDirPath();
            appDir+="/Presets/";
            appDir+=item->text();
            QFile file(appDir);
            if(file.open(QIODevice::ReadOnly))
            {
                QTextStream stream(&file);
                int counter=1;
                while(!stream.atEnd())
                {
                    QString line = stream.readLine();
                    switch(counter)
                    {
                    case 1:
                        if(line=="1")
                            ui->patternBox->setCurrentIndex(1);
                        else
                            ui->patternBox->setCurrentIndex(0);
                        break;
                    case 2:
                        if(line!="EMPTY")
                            ui->patternEdit->setText(line);
                        else
                            ui->patternEdit->setText("");
                        break;
                    case 3:
                        ui->skipBox->setValue(line.toInt());
                        break;
                    case 4:
                        ui->headerBox->setValue(line.toInt());
                        break;
                    case 5:
                        ui->tempBox->setValue(line.toInt());
                        break;
                    case 6:
                        ui->cdBox->setValue(line.toInt());
                        break;
                    }
                    counter++;
                    if(counter>6)
                        break;
                }
                file.close();
            }
            break;
        }
    }
}

void customFormat::savePreset()
{
    if(ui->presetEdit->text()!="")
    {
        QString append = ui->presetEdit->text();
        QString illegalChars = "\\/:?\"<>|.";
        for (int m=0; m<ui->presetEdit->text().size(); m++)
        {
            for(int l=0; l<illegalChars.size(); l++)
                if(illegalChars[l]==append[m])
                    append[m]=' ';
        }
        QString appDir = QCoreApplication::applicationDirPath();
        appDir+="/Presets";
        QDir dirTest(appDir);
        if(!dirTest.exists())
            dirTest.mkdir(appDir);
        appDir+="/"+append+".pre";
        if(QFile::exists(appDir))
        {
            QMessageBox::StandardButton dialog;
            dialog = QMessageBox::warning(this, "CDpal",
                         "Preset with entered name already exists.\nOverwrite preset?",
                         QMessageBox::Yes | QMessageBox::No);
            if( dialog == QMessageBox::Yes)
            {
                QFile::remove(appDir);
            }
            else
                return;
        }
        QFile file(appDir);
        if(file.open(QIODevice::WriteOnly))
        {
            QTextStream stream(&file);
            if(ui->patternBox->currentIndex()==0)
                stream <<"0"<<endl;
            else
                stream <<"1"<<endl;
            if(ui->patternEdit->text()!="")
                stream << ui->patternEdit->text()<<endl;
            else
                stream << "EMPTY"<< endl;
            stream << QString::number(ui->skipBox->value())<<endl;
            stream << QString::number(ui->headerBox->value())<<endl;
            stream << QString::number(ui->tempBox->value())<<endl;
            stream << QString::number(ui->cdBox->value())<<endl;
            file.close();
        }
    }
    else
    {
        QMessageBox::StandardButton dialog;
        dialog = QMessageBox::warning(this, "CDpal",
                     "Cannot save preset without a name.",
                     QMessageBox::Ok);
        Q_UNUSED(dialog);
    }
    updatePreset();
}

void customFormat::updatePreset()
{
    ui->presetWidget->clear();
    QString appDir = QCoreApplication::applicationDirPath();
    appDir+="/Presets";
    QDir dirTest(appDir);
    if(!dirTest.exists())
        return;
    QStringList nameFilter("*.pre");
    QDir directory(appDir);
    QStringList txtFiles = directory.entryList(nameFilter);
    ui->presetWidget->addItems(txtFiles);
}

void customFormat::deletePreset()
{
    QMessageBox::StandardButton dialog;
    dialog = QMessageBox::warning(this, "CDpal",
                 "Do you want to delete the selected preset?",
                 QMessageBox::Yes | QMessageBox::No);
    if( dialog == QMessageBox::Yes)
    {
        for(int i = 0; i < ui->presetWidget->count(); ++i)
        {
            if(ui->presetWidget->item(i)->isSelected())
            {
                QListWidgetItem* item = ui->presetWidget->item(i);
                QString appDir = QCoreApplication::applicationDirPath();
                appDir+="/Presets/";
                appDir+=item->text();
                if(QFile::exists(appDir))
                    QFile::remove(appDir);
            }
        }
        updatePreset();
    }

}

void customFormat::acceptEvent()
{
    QString pattern;
    pattern = ui->patternEdit->text();
    if(ui->patternBox->currentIndex()==0)
    {
        for(int j=0; j<pattern.size(); j++)
            if(pattern[j]==' ')
            {
                QString errMessage = "";
                QMessageBox::StandardButton dialog;
                errMessage = "Invalid file format.\nWhitespace is not allowed when searching a file for a word.\nUse \"line\" instead.";
                dialog = QMessageBox::warning(this, "CDpal",errMessage,QMessageBox::Ok);
                if(dialog==QMessageBox::Ok)
                    return;
            }
    }
    if(ui->cdBox->value() == ui->tempBox->value())
    {
        QString errMessage = "";
        QMessageBox::StandardButton dialog;
        extern int mode;
        if(mode==0)
            errMessage = "The CD signal column and temperature data column are identical.\nPlease check your custom format settings.";
        else
            errMessage = "The CD signal column and concentration data column are identical.\nPlease check your custom format settings.";
        dialog = QMessageBox::warning(this, "CDpal",errMessage,QMessageBox::Ok);
        if(dialog==QMessageBox::Ok)
            return;
    }
    else
    {
        QString appDir = QCoreApplication::applicationDirPath();
        appDir += "/settings.txt";
        std::ofstream paramFile;
        paramFile.open(mconvert(appDir).c_str(), std::ios::out);
        QString str = ui->patternEdit->text();
        if(str=="")
            str="EMPTY";
        extern QString sPattern;
        extern int sPatternType;
        extern int sskipR;
        extern int sH;
        extern int sC;
        extern int sT;
        sPattern=str;
        sPatternType=ui->patternBox->currentIndex();
        sskipR=ui->skipBox->value();
        sH=ui->headerBox->value();
        sC=ui->cdBox->value();
        sT=ui->tempBox->value();
        paramFile<<ui->patternBox->currentIndex()<<"\n"<<mconvert(str)<<"\n"<<ui->skipBox->value()<<"\n"<<ui->headerBox->value()<<"\n"<<ui->tempBox->value()<<"\n"<<ui->cdBox->value();
        paramFile.clear();
        paramFile.close();        
        QString errMess(checkErrors());
        if(errMess=="")
            accept();
        else
        {
            extern QString dispError;
            dispError = errMess;
            displayError errorWin;
            errorWin.setWindowFlags(errorWin.windowFlags() & ~Qt::WindowContextHelpButtonHint);
            errorWin.setWindowModality(Qt::ApplicationModal);
            if(errorWin.exec())
            {
                //Ok button was pressed
                accept();
            }
        }

    }
}

QString customFormat::checkErrors()
{
    QString errors("");
    extern QStringList files;
    extern double minXG;
    extern double maxXG;
    extern std::vector< std::vector<std::vector<std::string> > >storedData;
    storedData.clear();
    for(int i(0); i<files.size(); i++)
    {
        std::vector<std::vector<std::string> > dataVec;
        QString path = files.at(i);
        std::string f = mconvert(path);
        std::ifstream file;
        file.open(f.c_str(), std::ios::in);
        if(file.is_open())
        {
            bool foundPattern(false);
            QString pattern(ui->patternEdit->text());
            if(pattern=="")
                foundPattern=true;
            bool wordBool(true);
            if(ui->patternBox->currentIndex()==1)
                wordBool=false;
            int skippedPattern(0);
            int skipTimes(ui->skipBox->value()+1);
            int header(ui->headerBox->value());
            int tempCol(ui->tempBox->value());
            int cdCol(ui->cdBox->value());

            //Process file
            std::string line;
            int dataCount(0);
            int headerCount(0);
            QString stoppedReading("");
            QString stoppedFormatReading("");
            double lastTemp(-999999.9);
            bool stopReading(false);
            bool stopEmptyReading(false);
            bool stopFormatReading(false);
            int lC(0);
            while(getline(file, line))
            {
                if(stopReading || stopEmptyReading || stopFormatReading)
                {
                    lC++;
                    continue;
                }
                if(!foundPattern)
                {
                    if(wordBool) //Scan for word
                    {
                        std::istringstream iss(line);
                        std::string sub;
                        while(iss>>sub)
                        {
                            if(mconvert(pattern)==sub)
                            {
                                skippedPattern++;
                                break;
                            }
                        }
                    }
                    else //Scan for line
                    {
                        if(line==mconvert(pattern))
                            skippedPattern++;
                    }
                    if(skippedPattern==skipTimes)
                        foundPattern=true;
                }
                else //Begin processing header and data
                {
                    if(headerCount!=header)
                        headerCount++;
                    else
                    {
                        std::vector<std::string> tempVec;
                        std::string tmpLine(line);
                        std::istringstream iss(tmpLine);
                        std::string sub;
                        int colCount(1);
                        int pointCount(1);
                        if(line.find_first_not_of(' ') == std::string::npos)
                        {
                            stopEmptyReading=true;
                            continue;
                        }
                        while(iss >> sub)
                        {
                            bool ok(true);
                            if(colCount==tempCol)
                            {
                                double d(mconvert(sub).toDouble(&ok));
                                if(ok && lastTemp>d && ui->stopBox->isChecked())
                                {
                                    stopReading=true;
                                    stoppedReading+=mconvert(line);
                                    stoppedReading+="<br>";
                                }
                                else if(ok)
                                {
                                    pointCount++;
                                    tempVec.push_back(sub);
                                }
                                if(ok)
                                    lastTemp = d;
                            }
                            else if(colCount==cdCol)
                            {
                                double d(mconvert(sub).toDouble(&ok));
                                Q_UNUSED(d)
                                if(ok)
                                {
                                    pointCount++;
                                    tempVec.push_back(sub);
                                }
                            }
                            colCount++;
                            if(!ok)
                            {
                                stopFormatReading=true;
                                stoppedFormatReading+=mconvert(line);
                                stoppedFormatReading+="<br>";
                            }
                        }
                        if(pointCount==3)
                        {
                            dataCount++;
                            if(cdCol < tempCol && tempVec.size()>1)
                            {
                                std::string s = tempVec[0];
                                tempVec[0]= tempVec[1];
                                tempVec[1]= s;
                            }
                            dataVec.push_back(tempVec);
                        }
                        else if(!stopFormatReading && !stopReading)
                        {
                            stopFormatReading=true;
                            stoppedFormatReading+=mconvert(line);
                            stoppedFormatReading+="<br>";
                        }
                    }
                }
            }
            if(dataVec.size()>1)
            {
                if(atof(dataVec[0][0].c_str())<minXG)
                    minXG=atof(dataVec[0][0].c_str());
                if(atof(dataVec[dataVec.size()-1][0].c_str())>maxXG)
                    maxXG=atof(dataVec[dataVec.size()-1][0].c_str());
            }
            //Analyze results
            QString errorsTmp("");
            if(dataCount==0)
                errorsTmp+="No data could be imported either due to custom file format or lack of input file data.<br>";
            if(!foundPattern && skippedPattern==0)
                errorsTmp+="Could not find the specified pattern.<br>No data was imported.<br>";
            else if(!foundPattern)
            {
                errorsTmp+="Could only find the specified pattern ";
                errorsTmp+= QString::number(skippedPattern);
                errorsTmp+=" time(s).<br>No data was imported.<br>";
            }
            if(stopReading)
            {
                errorsTmp+="The following line caused a decrease in temperature and aborted the data import:<br>";
                errorsTmp+=stoppedReading;
                errorsTmp+="Number of successfully imported data points: ";
                errorsTmp+=QString::number(dataCount);
                errorsTmp+="<br>Remaining number of lines that were not read: ";
                errorsTmp+=QString::number(lC);
                errorsTmp+="<br>";
            }
            if(stopFormatReading)
            {
                errorsTmp+="The following line caused a bad format and aborted the data import:<br>";
                errorsTmp+=stoppedFormatReading;
                errorsTmp+="Number of successfully imported data points: ";
                errorsTmp+=QString::number(dataCount);
                errorsTmp+="<br>Remaining number of lines that were not read: ";
                errorsTmp+=QString::number(lC);
                errorsTmp+="<br>";
            }
            if(stopEmptyReading)
            {
                errorsTmp+="An empty line was encountered and aborted the data import.<br>";
                errorsTmp+="Number of successfully imported data points: ";
                errorsTmp+=QString::number(dataCount);
                errorsTmp+="<br>Remaining number of lines that were not read: ";
                errorsTmp+=QString::number(lC);
                errorsTmp+="<br>";
            }
            file.close();
            if(errorsTmp!="")
            {
                errors+="<b>Warning! When reading the file ";
                errors+=files.at(i);
                errors+=" the following errors occurred:</b><br>";
                errors+=errorsTmp;
                errors+="<hr><br>";
            }
        }
        else
        {
            errors+="Warning! Could not open the file ";
            errors+=files.at(i);
            errors+="<hr><br><br>";
        }
        storedData.push_back(dataVec);
    }
    return errors;
}
