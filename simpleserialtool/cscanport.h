#ifndef CSCANPORT_H
#define CSCANPORT_H

#include <QObject>
#include <QThread>
#include <QComboBox>


class CScanPort : public QThread
{
public:
    CScanPort();
    void SetPortBox(QComboBox* pPort);
protected:
    void run();
    QStringList list_port();
private:
    QComboBox* portList;
};

#endif // CSCANPORT_H
