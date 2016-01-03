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
    conversion.cpp \
    texturesettings.cpp \
    unitsettings.cpp \
    physicssettings.cpp \
    mod_picker.cpp

HEADERS  += mainwindow.h \
    data_base.h \
    conversion.h \
    texturesettings.h \
    unitsettings.h \
    physicssettings.h \
    mod_picker.h \
    globals.h

FORMS    += mainwindow.ui \
    texturesettings.ui \
    unitsettings.ui \
    physicssettings.ui \
    mod_picker.ui

INCLUDEPATH += $$PWD/../../Dependencies/SDL2-2.0.0/include
INCLUDEPATH += $$PWD/../../Dependencies/SDL2_net-2.0.0/i686-w64-mingw32/include/SDL2
INCLUDEPATH += $$PWD/../../Dependencies/SDL2_ttf-2.0.12/i686-w64-mingw32/include/SDL2
INCLUDEPATH += $$PWD/../../Dependencies/SDL2_image-2.0.0/i686-w64-mingw32/include/SDL2
INCLUDEPATH += $$PWD/../../Dependencies/SDL2_mixer-2.0.0/i686-w64-mingw32/include/SDL2
INCLUDEPATH += $$PWD/../../Dependencies/libFFmpeg/include

DEFINES += "__STDC_CONSTANT_MACROS"

win32: LIBS += -L$$PWD/../../bin/engine/ -lEureka

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

win32: LIBS += -L$$PWD/../../bin/engine/ -lIO

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

win32: LIBS += -L$$PWD/../../bin/engine/ -lnetwork

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

win32: LIBS += -L$$PWD/../../bin/engine/ -lUnit

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

win32: LIBS += -L$$PWD/../../bin/engine/ -lUI

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

win32: LIBS += -L$$PWD/../../bin/engine/ -lFlags

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../

win32: LIBS += -L$$PWD/../../bin/engine/ -lCore

INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../
