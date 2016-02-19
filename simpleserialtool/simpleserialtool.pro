#-------------------------------------------------
#
# Project created by QtCreator 2015-12-18T16:05:08
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = simpleserialtool
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ccmdwriter.cpp \
    cscanport.cpp \
    paramsettings.cpp \
    ccomparestrings.cpp

HEADERS  += mainwindow.h \
    ccmdwriter.h \
    mytype.h \
    cscanport.h \
    paramsettings.h \
    ccomparestrings.h

FORMS    += mainwindow.ui \
    paramsettings.ui

RESOURCES += \
    simpleserialtool.qrc

DISTFILES += \
    cmd_sample.xml


