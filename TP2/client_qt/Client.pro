#-------------------------------------------------
#
# Project created by QtCreator 2016-11-21T19:54:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    transmissioncontroller.cpp \
    receptioncontroller.cpp \
    loginscreen.cpp \
    user.cpp

HEADERS  += mainwindow.h \
    transmissioncontroller.h \
    receptioncontroller.h \
    loginscreen.h \
    user.h \
    messagableinterface.h

FORMS    += mainwindow.ui \
    loginscreen.ui

DISTFILES +=
