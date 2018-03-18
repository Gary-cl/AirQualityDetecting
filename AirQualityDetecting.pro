#-------------------------------------------------
#
# Project created by QtCreator 2017-05-14T15:43:22
#
#-------------------------------------------------

QT       += core gui network sql

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = AirQualityDetecting
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mysocket.cpp \
    mysockethandler.cpp \
    tcpsocket.cpp \
    qcustomplot.cpp \
    mygraph.cpp \
    mygraphstream.cpp \
    led.cpp \
    mydatabase.cpp

HEADERS  += mainwindow.h \
    mysocket.h \
    mysockethandler.h \
    tcpsocket.h \
    qcustomplot.h \
    mygraph.h \
    mygraphstream.h \
    led.h \
    mydatabase.h

FORMS    += mainwindow.ui \
    mysocket.ui \
    mygraph.ui \
    led.ui
