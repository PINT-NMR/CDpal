#include "simulatedialog.h"
#include "ui_simulatedialog.h"
#include <QMessageBox>

simulateDialog::simulateDialog(QWidget *parent, bool chemical) :
    QDialog(parent), chemMode(chemical),
    ui(new Ui::simulateDialog)
{
    ui->setupUi(this);
    if(chemMode)
    {
        ui->tabWidget->setTabEnabled(4,false);
        ui->tabWidget->setStyleSheet("QTabWidget::pane { \nmargin: 0px,1px,1px,1px;\nborder: 3px solid #020202;\nborder-radius: 7px;\npadding: 1px;\n	background-color: qlineargradient(spread:pad, x1:0.511, y1:1, x2:0.506, y2:0, stop:0 rgba(135, 190, 205, 100), stop:1 rgba(255, 255, 255, 255));\n}\nQTabBar::tab { \nmargin: 0px,0px,0px,0px;\nborder: 1px solid #020202;\nborder-radius: 5px;\npadding: 4px;\n }\nQTabBar::tab:selected, QTabBar::tab:hover {\n    background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,                                      stop: 0 #fafafa, stop: 0.4 #f4f4f4,                                      stop: 0.5 #e7e7e7, stop: 1.0 #fafafa); \n     }\nQTabBar::tab:selected { \n	border-color: #9B9B9B;          \n	border-bottom-color: #C2C7CB;\n}\nQTabBar::tab:!selected {\n    margin-top: 2px;\n}\n\nQTabBar::tab::disabled {width: 0; height: 0; margin: 0; padding: 0; border: none;}");
        //
        ui->lh1->setText("m (kJ<html>&bull;mol<sup>-1</sup>&bull;M<sup>-1</sup>)</html>");
        ui->ltm1->setText("Cm (M)");
        ui->lcp1->setText("Temperature (<html>&deg;</html>C)");
        ui->lh2->setText("m (kJ<html>&bull;mol<sup>-1</sup>&bull;M<sup>-1</sup>)</html>");
        ui->ltm2->setText("Cm (M)");
        ui->lcp2->setText("Temperature (<html>&deg;</html>C)");
        ui->lh3->setText("m (kJ<html>&bull;mol<sup>-1</sup>&bull;M<sup>-1</sup>)</html>");
        ui->ltm3->setText("Cm (M)");
        ui->lcp3->setText("Temperature (<html>&deg;</html>C)");
        ui->lh3->setText("m (kJ<html>&bull;mol<sup>-1</sup>&bull;M<sup>-1</sup>)</html>");
        ui->ltm3->setText("Cm (M)");
        ui->lcp3->setText("Temperature (<html>&deg;</html>C)");
        ui->cp2i->hide();
        ui->cp3i->hide();
        ui->cp4i->hide();
        ui->ltemp->setText("Concentration range (M)");
        ui->minTempBox->setMinimum(0.00);
        ui->minTempBox->setMaximum(19.99);
        ui->maxTempBox->setMinimum(0.01);
        ui->maxTempBox->setMaximum(20.00);
        ui->delta1->setText("10");
        ui->delta2n->setText("10");
        ui->delta3n->setText("10");
        ui->delta4n->setText("10");
        ui->delta2i->setText("20");
        ui->delta3i->setText("20");
        ui->delta4i->setText("20");
        ui->cp1->setText("25");
        ui->cp2n->setText("25");
        ui->cp3n->setText("25");
        ui->cp4n->setText("25");
        ui->tm1->setText("1.0");
        ui->tm2n->setText("1.0");
        ui->tm3n->setText("1.0");
        ui->tm4n->setText("1.0");
        ui->tm2i->setText("1.5");
        ui->tm3i->setText("1.5");
        ui->tm4i->setText("1.5");
        ui->maxTempBox->setValue(2.0);
        ui->maxTempBox->setSingleStep(0.1);
        ui->minTempBox->setSingleStep(0.1);
    }
}

simulateDialog::~simulateDialog()
{
    delete ui;
}

void simulateDialog::on_simulateButton_clicked()
{
    QString s(checkFormat());
    if(s=="CONVERSION_OK")
    {
        emit simulate();
        return;
    }
    QString str(s+" is a non-numerical value. Aborting.");
    QMessageBox::StandardButton dialog;
    dialog = QMessageBox::warning(this, "Warning",
                 str,
                 QMessageBox::Ok);
    if( dialog == QMessageBox::Ok)
        return;
}

void simulateDialog::on_cancelButton_clicked()
{
    emit hideUI();
}

QString simulateDialog::checkFormat()
{
    model =ui->tabWidget->currentIndex();
    bool ok;
    double d;
    double mult(1000.0);

    switch (model)
    {
    case 0: //ND
        d = ui->delta1->text().toDouble(&ok);
        if(!ok)
            return ui->delta1->text();
        dH = d*mult;
        d = ui->tm1->text().toDouble(&ok);
        if(!ok)
            return ui->tm1->text();
        tm = d;
        d = ui->cp1->text().toDouble(&ok);
        if(!ok)
            return ui->cp1->text();
        cp = d;
        d = ui->kn1->text().toDouble(&ok);
        if(!ok)
            return ui->kn1->text();
        kn = d;
        d = ui->mn1->text().toDouble(&ok);
        if(!ok)
            return ui->mn1->text();
        mn = d;
        d = ui->kd1->text().toDouble(&ok);
        if(!ok)
            return ui->kd1->text();
        kd = d;
        d = ui->md1->text().toDouble(&ok);
        if(!ok)
            return ui->md1->text();
        md = d;
        break;
    case 1: //NID
        d = ui->delta2n->text().toDouble(&ok);
        if(!ok)
            return ui->delta2n->text();
        dH = d*mult;
        d = ui->delta2i->text().toDouble(&ok);
        if(!ok)
            return ui->delta2i->text();
        dH2 = d*mult;
        d = ui->tm2n->text().toDouble(&ok);
        if(!ok)
            return ui->tm2n->text();
        tm = d;
        d = ui->tm2i->text().toDouble(&ok);
        if(!ok)
            return ui->tm2i->text();
        tm2 = d;
        d = ui->cp2n->text().toDouble(&ok);
        if(!ok)
            return ui->cp2n->text();
        cp = d;
        d = ui->cp2i->text().toDouble(&ok);
        if(!ok)
            return ui->cp2i->text();
        cp2 = d;
        d = ui->kn1->text().toDouble(&ok);
        if(!ok)
            return ui->kn2->text();
        kn = d;
        d = ui->mn2->text().toDouble(&ok);
        if(!ok)
            return ui->mn2->text();
        mn = d;
        d = ui->ki2->text().toDouble(&ok);
        if(!ok)
            return ui->ki2->text();
        ki = d;
        d = ui->mi2->text().toDouble(&ok);
        if(!ok)
            return ui->mi2->text();
        mi = d;
        d = ui->kd2->text().toDouble(&ok);
        if(!ok)
            return ui->kd2->text();
        kd = d;
        d = ui->md2->text().toDouble(&ok);
        if(!ok)
            return ui->md2->text();
        md = d;
        break;
    case 2: //N22I2D
        d = ui->conc3->text().toDouble(&ok);
        if(!ok)
            return ui->conc3->text();
        conc = d/=1000000.0;
        d = ui->delta3n->text().toDouble(&ok);
        if(!ok)
            return ui->delta3n->text();
        dH = d*mult;
        d = ui->delta3i->text().toDouble(&ok);
        if(!ok)
            return ui->delta3i->text();
        dH2 = d*mult;
        d = ui->tm3n->text().toDouble(&ok);
        if(!ok)
            return ui->tm3n->text();
        tm = d;
        d = ui->tm3i->text().toDouble(&ok);
        if(!ok)
            return ui->tm3i->text();
        tm2 = d;
        d = ui->cp3n->text().toDouble(&ok);
        if(!ok)
            return ui->cp3n->text();
        cp = d;
        d = ui->cp3i->text().toDouble(&ok);
        if(!ok)
            return ui->cp3i->text();
        cp2 = d;
        d = ui->kn1->text().toDouble(&ok);
        if(!ok)
            return ui->kn3->text();
        kn = d;
        d = ui->mn3->text().toDouble(&ok);
        if(!ok)
            return ui->mn3->text();
        mn = d;
        d = ui->ki3->text().toDouble(&ok);
        if(!ok)
            return ui->ki3->text();
        ki = d;
        d = ui->mi3->text().toDouble(&ok);
        if(!ok)
            return ui->mi3->text();
        mi = d;
        d = ui->kd3->text().toDouble(&ok);
        if(!ok)
            return ui->kd3->text();
        kd = d;
        d = ui->md3->text().toDouble(&ok);
        if(!ok)
            return ui->md3->text();
        md = d;
        break;
    case 3: //NI22D
        d = ui->conc4->text().toDouble(&ok);
        if(!ok)
            return ui->conc4->text();
        conc = d/=1000000.0;
        d = ui->delta4n->text().toDouble(&ok);
        if(!ok)
            return ui->delta4n->text();
        dH = d*mult;
        d = ui->delta4i->text().toDouble(&ok);
        if(!ok)
            return ui->delta4i->text();
        dH2 = d*mult;
        d = ui->tm4n->text().toDouble(&ok);
        if(!ok)
            return ui->tm4n->text();
        tm = d;
        d = ui->tm4i->text().toDouble(&ok);
        if(!ok)
            return ui->tm4i->text();
        tm2 = d;
        d = ui->cp4n->text().toDouble(&ok);
        if(!ok)
            return ui->cp4n->text();
        cp = d;
        d = ui->cp4i->text().toDouble(&ok);
        if(!ok)
            return ui->cp4i->text();
        cp2 = d;
        d = ui->kn1->text().toDouble(&ok);
        if(!ok)
            return ui->kn4->text();
        kn = d;
        d = ui->mn4->text().toDouble(&ok);
        if(!ok)
            return ui->mn4->text();
        mn = d;
        d = ui->ki4->text().toDouble(&ok);
        if(!ok)
            return ui->ki4->text();
        ki = d;
        d = ui->mi4->text().toDouble(&ok);
        if(!ok)
            return ui->mi4->text();
        mi = d;
        d = ui->kd4->text().toDouble(&ok);
        if(!ok)
            return ui->kd4->text();
        kd = d;
        d = ui->md4->text().toDouble(&ok);
        if(!ok)
            return ui->md4->text();
        md = d;
        break;
    default://Derivative
        d = ui->delta5->text().toDouble(&ok);
        if(!ok)
            return ui->delta5->text();
        dH = d*mult;
        d = ui->tm5->text().toDouble(&ok);
        if(!ok)
            return ui->tm5->text();
        tm = d;
        d = ui->a->text().toDouble(&ok);
        if(!ok)
            return ui->a->text();
        a = d;
        break;
    }

    noise = ui->noiseBox->value();
    minTemp = ui->minTempBox->value();
    maxTemp = ui->maxTempBox->value();
    datapoints = ui->datapointBox->value();

    return "CONVERSION_OK";
}

void simulateDialog::checkTempRange(bool maxChanged)
{
    double comp(1.0);
    if(chemMode)
        comp = 0.01;
    if(ui->minTempBox->value()>=ui->maxTempBox->value())
    {
        if(maxChanged)
            ui->minTempBox->setValue(ui->maxTempBox->value()-comp);
        else
            ui->maxTempBox->setValue(ui->maxTempBox->value()+comp);
    }
}

void simulateDialog::on_minTempBox_editingFinished()
{
    checkTempRange(0);
}

void simulateDialog::on_maxTempBox_editingFinished()
{
    checkTempRange(1);
}

void simulateDialog::on_deleteButton_clicked()
{
    emit deleteDataset();
}
