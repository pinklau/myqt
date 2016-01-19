#include "mainwindow.h"
#include <QApplication>
#include "ccmdwriter.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CCmdWriter cw;
    cw.start();
    w.show();

    return a.exec();
}
