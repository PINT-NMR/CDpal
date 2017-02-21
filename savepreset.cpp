#include "savepreset.h"
#include "ui_savepreset.h"
#include <qdir.h>
#include <qmessagebox.h>
#include <QListWidgetItem>
#include <globals.h>

savePreset::savePreset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::savePreset)
{
    ui->setupUi(this);
    loadExistingPresets();
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(acceptEvent()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
    connect(ui->deleteButton, SIGNAL(clicked()), this, SLOT(deletePreset()));
}

savePreset::~savePreset()
{
    delete ui;
}

void savePreset::loadExistingPresets()
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

void savePreset::deletePreset()
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

void savePreset::acceptEvent()
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
        appDir+="/"+append+".spre";
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
            extern QVector<bool> isFitVec;
            extern QVector<QPen> penVec;
            extern QVector<QCPScatterStyle> ornamentVec;
            QTextStream stream(&file);
            for(int i(0); i<isFitVec.size(); i++)
            {
                stream <<isFitVec[i]<<" "<<penVec[i].color().rgb()<<" "<<penVec[i].width()<<" "<<ornamentVec[i].shape()<<endl;
            }
            file.close();
        }
        accept();
    }
    else
    {
        QMessageBox::StandardButton dialog;
        dialog = QMessageBox::warning(this, "CDpal",
                     "Cannot save preset without a name.",
                     QMessageBox::Ok);
        Q_UNUSED(dialog);
    }
}
