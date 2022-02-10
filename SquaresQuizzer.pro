#-------------------------------------------------
#
# Project created by QtCreator 2016-03-17T21:25:49
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SquaresQuizzer
TEMPLATE = app


SOURCES += main.cpp\
    configurationwindow.cpp \
        mainwindow.cpp \
    qgraphicsclickablerectitem.cpp

HEADERS  += mainwindow.h \
    configurationwindow.h \
    qgraphicsclickablerectitem.h

FORMS    += mainwindow.ui \
    configurationwindow.ui
