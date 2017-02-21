#include "displayerror.h"
#include "ui_displayerror.h"
#include "globals.h"

displayError::displayError(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::displayError)
{
    ui->setupUi(this);
    connect(ui->yesButton, SIGNAL(clicked()), this, SLOT(acceptEvent()));
    connect(ui->noButton, SIGNAL(clicked()), this, SLOT(reject()));
    extern QString dispError;
    ui->errorBrowser->clear();
    ui->errorBrowser->setText(dispError);
}

displayError::~displayError()
{
    delete ui;
}

void displayError::acceptEvent()
{
    accept();
}
