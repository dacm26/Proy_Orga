#-------------------------------------------------
#
# Project created by QtCreator 2013-08-07T12:39:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Access
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ADTFile.cpp \
    ADTRecordFile.cpp \
    field_w.cpp

HEADERS  += mainwindow.h \
    ADTFile.h \
    ADTRecordFile.h \
    field_w.h

FORMS    += mainwindow.ui \
    field_w.ui
