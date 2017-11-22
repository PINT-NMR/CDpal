#ifndef SIMULATEDIALOG_H
#define SIMULATEDIALOG_H

#include <QDialog>

namespace Ui {
class simulateDialog;
}

class simulateDialog : public QDialog
{
    Q_OBJECT

public:
    explicit simulateDialog(QWidget *parent = 0, bool chemical = false);
    ~simulateDialog();
    bool chemMode;
    int model;
    double dH;
    double dH2;
    double cp;
    double cp2;
    double tm;
    double tm2;
    double kn;
    double ki;
    double kd;
    double mn;
    double mi;
    double md;
    double conc;
    double a;
    double noise;
    double minTemp;
    double maxTemp;
    double datapoints;

private slots:
    void on_simulateButton_clicked();
    void on_cancelButton_clicked();
    QString checkFormat();
    void checkTempRange(bool maxChanged);
    void on_minTempBox_editingFinished();
    void on_maxTempBox_editingFinished();

    void on_deleteButton_clicked();

private:
    Ui::simulateDialog *ui;

signals:
    void simulate();
    void deleteDataset();
    void hideUI();
};

#endif // SIMULATEDIALOG_H
