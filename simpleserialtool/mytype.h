#ifndef MYTYPE
#define MYTYPE
#include <QVector>
#include <QtSerialPort/QSerialPort>
#include <QString>
#include <QPoint>

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

typedef struct tagReplacewords
{
    bool bReplaceFlag;
    int nCmdType;
    QVector<int>* posSet;
    QVector<QPoint>* paramsSet;
    QString text;
}ReplaceWords;

typedef struct tagCmdheadTrail
{
    QString head;
    QString end;
    QString userSignal;
    QString returnHead;
}CmdHeadTrail;

typedef struct tagCmdParams
{
    QString cmd;
    QString subcmd;
    QString maincmd;
    QString strReturn;
    QString text;
    int nReturnCount;
    int nTextReplaceCount;
    QVector<QPoint>* rangeSet;


}CmdParams;

typedef struct tagCommadSet
{
    CmdParams* mainCmd;
    QVector<CmdParams*> subCmd;
}CommandSet;

#endif // MYTYPE

