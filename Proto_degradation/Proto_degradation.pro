#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T15:28:11
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Model_Loader
TEMPLATE = app


SOURCES += main.cpp\
        mywindow.cpp \
    model.cpp \
    myglwidget.cpp \
    obj_loader.cpp \
    Point.cpp \
    loader.cpp

HEADERS  += mywindow.h \
    model.h \
    myglwidget.h \
    obj_loader.h \
    Point.h \
    loader.h

FORMS    += mywindow.ui
