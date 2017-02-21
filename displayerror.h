#ifndef DISPLAYERROR_H
#define DISPLAYERROR_H

#include <QDialog>

namespace Ui {
class displayError;
}

class displayError : public QDialog
{
    Q_OBJECT

public:
    explicit displayError(QWidget *parent = 0);
    ~displayError();

private:
    Ui::displayError *ui;

public slots:
    void acceptEvent();
};

#endif // DISPLAYERROR_H
