#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <qt_windows.h>
#include <QPainter>



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_FileButton_clicked();
    QStringList list_port(void);
    void on_pushButton_clicked();
    void save_serialort_setting(QString strText, int nType);

protected:
    void paintEvent(QPaintEvent *);
private:
    Ui::MainWindow *ui;
    QSerialPort* port;
    QString portName;

};

#endif // MAINWINDOW_H
