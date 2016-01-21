#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T16:05:08
#
#-------------------------------------------------

QT       += core gui
QT += serialport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simpleserialtool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ccmdwriter.cpp \
    cscanport.cpp

HEADERS  += mainwindow.h \
    ccmdwriter.h \
    mytype.h \
    cscanport.h

FORMS    += mainwindow.ui

RESOURCES += \
    simpleserialtool.qrc


