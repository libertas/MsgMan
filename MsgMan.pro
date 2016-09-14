#-------------------------------------------------
#
# Project created by QtCreator 2016-09-12T23:18:06
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MsgMan
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    msgman.cpp \
    logindialog.cpp

HEADERS  += mainwindow.h \
    msgman.h \
    logindialog.h

FORMS    += mainwindow.ui \
    logindialog.ui
