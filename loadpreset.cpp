#include "loadpreset.h"
#include "ui_loadpreset.h"
#include <qdir.h>
#include <qmessagebox.h>
#include <QListWidgetItem>
#include "globals.h"
#include "mfunc.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

loadpreset::loadpreset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loadpreset)
{
    ui->setupUi(this);
    loadExistingPresets();
    connect(ui->okButt, SIGNAL(clicked()), this, SLOT(acceptEvent()));
    connect(ui->cancelButt, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->deleteButt, SIGNAL(clicked()), this, SLOT(deletePreset()));
}

loadpreset::~loadpreset()
{
    delete ui;
}

void loadpreset::deletePreset()
{
    QMessageBox::StandardButton dialog;
    dialog = QMessageBox::warning(this, "CDpal",
                 "Do you want to delete the selected preset?",
                 QMessageBox::Yes | QMessageBox::No);
    if( dialog == QMessageBox::Yes)
    {
        for(int i = 0; i < ui->presetBrowser->count(); ++i)
        {
            if(ui->presetBrowser->item(i)->isSelected())
            {
                QListWidgetItem* item = ui->presetBrowser->item(i);
                QString appDir = QCoreApplication::applicationDirPath();
                appDir+="/Presets/";
                appDir+=item->text();
                if(QFile::exists(appDir))
                    QFile::remove(appDir);
            }
        }
        loadExistingPresets();
    }
}

void loadpreset::loadExistingPresets()
{
    //Add existing style presets to the browser
    //Does not check for format errors
    ui->presetBrowser->clear();
    QString appDir = QCoreApplication::applicationDirPath();
    appDir+="/Presets";
    QDir dirTest(appDir);
    if(!dirTest.exists())
        return;
    QStringList nameFilter("*.spre");
    QDir directory(appDir);
    QStringList txtFiles = directory.entryList(nameFilter);
    ui->presetBrowser->addItems(txtFiles);
}

void loadpreset::acceptEvent()
{
    for(int i = 0; i < ui->presetBrowser->count(); ++i)
    {
        if(ui->presetBrowser->item(i)->isSelected())
        {
            QListWidgetItem* item = ui->presetBrowser->item(i);
            QString appDir = QCoreApplication::applicationDirPath();
            appDir+="/Presets/";
            appDir+=item->text();
            QFile file(appDir);
            extern QVector<QString> styleVec;
            styleVec.clear();
            if(file.open(QIODevice::ReadOnly))
            {
                QTextStream stream(&file);
                while(!stream.atEnd())
                {
                    styleVec.push_back(stream.readLine());
                }
                file.close();
            }
            if(formatOK())
            {
                accept();
                return;
            }
            else
            {
                QMessageBox::StandardButton dialog;
                dialog = QMessageBox::warning(this, "CDpal",
                             "The format of the preset is corrupted, please delete the preset.",
                             QMessageBox::Ok);
                Q_UNUSED(dialog);
                return;
            }
        }
    }
    QMessageBox::StandardButton dialog;
    dialog = QMessageBox::warning(this, "CDpal",
                 "Please select a style preset.",
                 QMessageBox::Ok);
    Q_UNUSED(dialog);
}

bool loadpreset::formatOK()
{
    extern QVector<QString> styleVec;
    if(styleVec.size()==0)
        return false;
    for(int i(0); i<styleVec.size(); i++)
    {
        std::string str(mconvert(styleVec[i]));
        std::istringstream iss(str);
        std::string sub;
        int counter(0);
        while(iss>>sub)
        {
            if(!is_number(sub))
                return false;
            counter++;
        }
        if(counter!=4)
            return false;
    }
    return true;
}
bool loadpreset::is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while(it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
