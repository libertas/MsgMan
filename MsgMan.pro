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
    logindialog.cpp \
    user.cpp \
    usermanage.cpp \
    seller.cpp \
    branch.cpp \
    branchmanage.cpp

HEADERS  += mainwindow.h \
    logindialog.h \
    user.h \
    usermanage.h \
    seller.h \
    branch.h \
    branchmanage.h

FORMS    += mainwindow.ui \
    logindialog.ui \
    usermanage.ui \
    branchmanage.ui
