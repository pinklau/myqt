#ifndef PARAMSETTINGS_H
#define PARAMSETTINGS_H

#include <QDialog>
#include <QTextEdit>

namespace Ui {
class paramsettings;
}

class paramsettings : public QDialog
{
    Q_OBJECT

public:
    explicit paramsettings(QWidget *parent = 0);
    ~paramsettings();

    QStringList PcParams() const;
    QStringList ArmParams() const;
private slots:
    void on_pushButton_ok_destroyed();

    void on_pushButton_cancel_destroyed();

    void on_pushButton_reset_clicked();

    void on_pushButton_ok_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    void read_data(QTextEdit* &textCtrl);

private:
    Ui::paramsettings *ui;
    QStringList listPc;
    QStringList listArm;
};

#endif // PARAMSETTINGS_H
