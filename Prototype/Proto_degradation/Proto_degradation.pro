#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T15:28:11
#
#-------------------------------------------------

QT       += core gui opengl
CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Model_Loader
TEMPLATE = app


SOURCES += main.cpp\
        mywindow.cpp \
    model.cpp \
    myglwidget.cpp \
    obj_loader.cpp \
    Point.cpp \
    loader.cpp \
    Mesh.cpp

HEADERS  += mywindow.h \
    model.h \
    myglwidget.h \
    obj_loader.h \
    Point.h \
    loader.h \
    Mesh.h

