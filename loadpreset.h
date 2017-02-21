#ifndef LOADPRESET_H
#define LOADPRESET_H

#include <QDialog>

namespace Ui {
class loadpreset;
}

class loadpreset : public QDialog
{
    Q_OBJECT

public:
    explicit loadpreset(QWidget *parent = 0);
    ~loadpreset();

private:
    Ui::loadpreset *ui;

public slots:
    void deletePreset();
    void loadExistingPresets();
    void acceptEvent();
    bool is_number(const std::string& s);
    bool formatOK();
};

#endif // LOADPRESET_H
