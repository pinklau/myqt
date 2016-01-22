#ifndef CCMDWRITER_H
#define CCMDWRITER_H
#include <QThread>
#include <QStringList>
#include <QtSerialPort/qserialportinfo.h>
#include <QtSerialPort/QSerialPort>

class CCmdWriter : public QThread
{
    Q_OBJECT
public:
    CCmdWriter(QObject* parent = 0);
    void stop();

protected:
    void run();
public:
    QStringList list_port();
    void setSerialObj(QSerialPort* serialObj);
private:
    QSerialPort* serialPortObj;
    bool bContine;
};

#endif // CCMDWRITER_H
