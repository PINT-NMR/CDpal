#include "namefiles.h"
#include "ui_namefiles.h"
#include "globals.h"

nameFiles::nameFiles(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nameFiles)
{
    ui->setupUi(this);
    setupTable();
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(acceptEvent()));
    connect(ui->skipButton, SIGNAL(clicked()), this, SLOT(reject()));
}

nameFiles::~nameFiles()
{
    delete ui;
}

void nameFiles::setupTable()
{
    extern QStringList files;
    ui->nameTable->setRowCount(files.size());
    ui->nameTable->setColumnCount(1);
    extern QStringList takenNames;
    if(takenNames.size()>0)
    {
        int no(1);
        for(int i(0); i<files.size(); i++)
        {
            bool done(false);
            QString str("");
            while(!done)
            {
                str="Graph ";
                str+=QString::number(no);
                for(int j(0);j<takenNames.size();j++)
                {
                    if(takenNames[j]==str)
                        break;
                    else if(j==takenNames.size()-1)
                        done=true;
                }
                no++;
            }
            ui->nameTable->setItem(i,0,new QTableWidgetItem(str));
        }
    }
    else
    {
        for(int i(0); i<files.size(); i++)
        {
            QString str("Graph ");
            str+=QString::number(i+1);
            ui->nameTable->setItem(i,0,new QTableWidgetItem(str));
        }
    }
    ui->nameTable->setHorizontalHeaderLabels(QStringList() << "Graph name");
    ui->nameTable->setVerticalHeaderLabels(files);
    ui->nameTable->resizeColumnsToContents();
}

void nameFiles::acceptEvent()
{
    for(int i(0); i<ui->nameTable->rowCount()-1; i++)
    {
        QString str(ui->nameTable->item(i,0)->text());
        if(str=="")
        {
            QMessageBox::warning(this, "Error","Unnamed dataset detected.", QMessageBox::Ok);
            return;
        }
        for(int j(0); j<str.length()-4; j++)
            if(str[j]=='(' && str[j+1]=='f' && str[j+2]=='i' && str[j+3]=='t' && str[j+4]==':')
            {
                QMessageBox::warning(this, "Error","Please do not include the string \"(fit:\" in the graph name.", QMessageBox::Ok);
                return;
            }
    }
    for(int i(0); i<ui->nameTable->rowCount()-1; i++)
    {
        for(int j(i+1); j<ui->nameTable->rowCount(); j++)
        {
            if(ui->nameTable->item(i,0)->text() == ui->nameTable->item(j,0)->text())
            {
                QMessageBox::warning(this, "Error","Duplicate names detected.", QMessageBox::Ok);
                return;
            }
        }
    }
    extern QStringList graphNames;
    graphNames.clear();
    for(int i(0); i<ui->nameTable->rowCount(); i++)
        graphNames.push_back(ui->nameTable->item(i,0)->text());
    accept();
}
