#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/qserialportinfo.h>
#include <qt_windows.h>
#include <QPainter>
#include "mytype.h"
#include "cscanport.h"
#include "ccmdwriter.h"
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include "paramsettings.h"
#include <QMap>

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
    void save_port_baud();
    void save_port_byte();
    void save_port_stopbyte();
    void save_port_parity();
    void save_port_flowCtrl();
    void save_port_name();
    void on_pushButton_2_clicked();
    void destroy_threads_on_exit();
    void read_comport_data();

    void on_checkBox_clicked(bool checked);

    void on_pushButton_3_clicked();

    void on_checkBox_2_clicked(bool checked);

    void auto_send_timer();

    void on_pushButton_4_clicked();

    void on_checkBox_3_clicked(bool checked);

    void on_pushButton_5_clicked();

protected:
    void paintEvent(QPaintEvent *);
    void setPortParams();
private:
    Ui::MainWindow *ui;
    QSerialPort* port;
    QString portName;
    SerialPortSetting portInfo;
    CScanPort portScaner;
    CCmdWriter workThread;
    bool bWork;
    bool bhex;
    QTimer autoTimer;
    paramsettings armAsk;
    QMap<QString,QString> cmdMap;
    int nReadNums;
    int nWriteNums;
};

#endif // MAINWINDOW_H
