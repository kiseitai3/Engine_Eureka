#-------------------------------------------------
#
# Project created by QtCreator 2014-01-06T17:34:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Level_Designer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    data_base.cpp \
    startup.cpp \
    conversion.cpp

HEADERS  += mainwindow.h \
    data_base.h \
    startup.h \
    conversion.h \
    globals.h

FORMS    += mainwindow.ui \
    startup.ui
