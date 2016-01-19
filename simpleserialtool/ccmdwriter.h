#ifndef CCMDWRITER_H
#define CCMDWRITER_H
#include <QThread>
#include <QStringList>

class CCmdWriter : public QThread
{
    Q_OBJECT
public:
    CCmdWriter(QObject* parent = 0);

public:
    void run();
    QStringList list_port();
};

#endif // CCMDWRITER_H
