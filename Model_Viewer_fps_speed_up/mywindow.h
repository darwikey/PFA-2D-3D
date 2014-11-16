#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "myGLWidget.h"
#include "obj_loader.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QGLFunctions>
#include <QtGui/QOpenGLShaderProgram>


class myWindow : public myGLWidget, protected QGLFunctions // add QGLFunctions
{
    Q_OBJECT
public:
    explicit myWindow(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
};

#endif // MYWINDOW_H
