#ifndef MY_WINDOW_H
#define MY_WINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QGLFunctions>
#include <QtGui/QOpenGLShaderProgram>

#include "MyGLWidget.h"
#include "objLoader.h"

class MyWindow : public MyGLWidget, protected QGLFunctions { // add QGLFunctions

  Q_OBJECT

 public:
  explicit MyWindow(QWidget *parent = 0);
  void initializeGL();
  void resizeGL(int width, int height);
  void paintGL();
};

#endif // MY_WINDOW_H
