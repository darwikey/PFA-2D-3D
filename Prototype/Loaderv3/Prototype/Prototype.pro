#-------------------------------------------------
#
# Project created by QtCreator 2014-11-27T18:05:49
#
#-------------------------------------------------

QT       += core gui opengl
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 5): QT += widgets

TARGET = Prototype
TEMPLATE = app


SOURCES += main.cpp\
    obj_loader.cpp \
    PlyLoader.cpp \
    Point.cpp \
        MainWindow.cpp \
    QFileSystemModelDialog.cpp \
    Chargeur.cpp \
    Scene.cpp \
    Model.cpp \
    Camera.cpp \
    MyGLWidget.cpp \
    SceneRenderer.cpp

HEADERS  += MainWindow.hpp \
    obj_loader.h \
    PlyLoader.hpp \
    Point.hpp \
    QFileSystemModelDialog.hpp \
    ui_mainwindow.h \
    ui_qfilesystemmodeldialog.h \
    singleton.h \
    Chargeur.hpp \
    Scene.hpp \
    Model.hpp \
    Camera.hpp \
    MyGLWidget.hpp \
    SceneRenderer.hpp

FORMS    += mainwindow.ui \
    dialog_file_tree.ui
