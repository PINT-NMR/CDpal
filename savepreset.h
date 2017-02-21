#ifndef SAVEPRESET_H
#define SAVEPRESET_H

#include <QDialog>

namespace Ui {
class savePreset;
}

class savePreset : public QDialog
{
    Q_OBJECT

public:
    explicit savePreset(QWidget *parent = 0);
    ~savePreset();

private:
    Ui::savePreset *ui;

public slots:
    void loadExistingPresets();
    void deletePreset();
    void acceptEvent();
};

#endif // SAVEPRESET_H
