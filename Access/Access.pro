#-------------------------------------------------
#
# Project created by QtCreator 2013-08-07T12:39:33
#
#-------------------------------------------------

QT       += core gui
QT       += xml
QT	 += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Access
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ADTRecordFile.cpp \
    field_w.cpp \
    field.cpp \
    fileheader.cpp \
    mfields_w.cpp \
    btree.cpp \
    bnode.cpp \
    key.cpp

HEADERS  += mainwindow.h \
    ADTRecordFile.h \
    field_w.h \
    field.h \
    fileheader.h \
    mfields_w.h \
    btree.h \
    bnode.h \
    key.h

FORMS    += mainwindow.ui \
    field_w.ui \
    mfields_w.ui
