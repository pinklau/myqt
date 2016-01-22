#ifndef MYTYPE
#define MYTYPE

#include <QtSerialPort/QSerialPort>

/* @brief: serialport setting data*/
typedef struct tagSerialPortSetting
{
    QString                  portname;
    QSerialPort::BaudRate    baud;
    QSerialPort::DataBits    databits;
    QSerialPort::FlowControl flowCtrl;
    QSerialPort::StopBits    stopbits;
    QSerialPort::Parity      parity;
}SerialPortSetting;

#endif // MYTYPE

