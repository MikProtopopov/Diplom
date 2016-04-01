#-------------------------------------------------
#
# Project created by QtCreator 2015-10-13T10:36:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = Diplom
TEMPLATE = app

#QMAKE_LFLAGS += /INCREMENTAL:NO

SOURCES += main.cpp\
    dialog.cpp \
    startwindow.cpp \
    rastrmanipulation.cpp \
    paintrastr.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS  += \
    dialog.h \
    startwindow.h \
    rastrmanipulation.h \
    paintrastr.h \
    mainwindow.h \
    qcustomplot.h

FORMS    += \
    dialog.ui \
    startwindow.ui \
    mainwindow.ui
