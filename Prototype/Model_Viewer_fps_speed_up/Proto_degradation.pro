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

LIBS += -lglut -lGLU

INCLUDEPATH += -L/usr/lib

SOURCES += main.cpp\
        MyWindow.cpp \
    Model.cpp \
    MyGLWidget.cpp \
    objLoader.cpp \
    plyLoader.cpp \
    Point.cpp \
    Loader.cpp

HEADERS  += MyWindow.h \
    Model.h \
    MyGLWidget.h \
    objLoader.h \
    plyLoader.h \
    Point.h \
    Loader.h
