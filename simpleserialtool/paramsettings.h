#ifndef PARAMSETTINGS_H
#define PARAMSETTINGS_H

#include <QDialog>

namespace Ui {
class paramsettings;
}

class paramsettings : public QDialog
{
    Q_OBJECT

public:
    explicit paramsettings(QWidget *parent = 0);
    ~paramsettings();

private:
    Ui::paramsettings *ui;
};

#endif // PARAMSETTINGS_H
