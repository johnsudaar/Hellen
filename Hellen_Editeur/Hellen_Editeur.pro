#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T12:21:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Hellen_Editeur
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        tilecreator.cpp \
    tile.cpp

HEADERS  += mainwindow.h\
            tilecreator.h \
    tile.h

FORMS    += mainwindow.ui\
            tilecreator.ui
