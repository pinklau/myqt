#ifndef PARAMSETTINGS_H
#define PARAMSETTINGS_H

#include <QDialog>
#include <QTextEdit>
#include <QMap>

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

    void on_checkBox_clicked(bool checked);

    void on_pushButton_3_clicked(bool checked);

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    void read_data(QTextEdit* &textCtrl);
    void clear_words();
    bool find_add_str(QString& str);
    QMap<QString,QPoint>* find_add_str_list(QString& str);
private:
    Ui::paramsettings *ui;
    QStringList listPc;
    QStringList listArm;
    bool bshow;
    QMap<QString, QMap<QString,QPoint>* > replaceWords;
};

#endif // PARAMSETTINGS_H
