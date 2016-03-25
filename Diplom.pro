#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T10:36:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Diplom
TEMPLATE = app

#QMAKE_LFLAGS += /INCREMENTAL:NO

SOURCES += main.cpp\
    dialog.cpp \
    startwindow.cpp \
    rastrmanipulation.cpp \
    paintrastr.cpp \
    mainwindow.cpp \
    paintgraph.cpp

HEADERS  += \
    dialog.h \
    startwindow.h \
    rastrmanipulation.h \
    paintrastr.h \
    mainwindow.h \
    paintgraph.h

FORMS    += \
    dialog.ui \
    startwindow.ui \
    mainwindow.ui
