#ifndef NAMEFILES_H
#define NAMEFILES_H

#include <QDialog>

namespace Ui {
class nameFiles;
}

class nameFiles : public QDialog
{
    Q_OBJECT

public:
    explicit nameFiles(QWidget *parent = 0);
    ~nameFiles();

private:
    Ui::nameFiles *ui;

public slots:
    void setupTable();
    void acceptEvent();
};

#endif // NAMEFILES_H
