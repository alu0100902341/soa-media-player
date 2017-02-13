#-------------------------------------------------
#
# Project created by QtCreator 2017-02-07T13:09:20
#
#-------------------------------------------------

RESOURCES     = application.qrc
QT       += core gui
QT += multimediawidgets
QT += multimedia multimediawidgets
QT += multimedia
QT += widgets
QT += gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = player
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
