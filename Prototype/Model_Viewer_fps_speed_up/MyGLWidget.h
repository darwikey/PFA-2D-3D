#ifndef MY_GLWIDGET_H
#define MY_GLWIDGET_H

#include <QMouseEvent>
#include <QtOpenGL>
#include <QWheelEvent>
#include <QSize>
#include <QPoint>
#include <QGLWidget>

#include"Model.h"

class MyGLWidget : public QGLWidget {

  Q_OBJECT

 public:
 
  explicit MyGLWidget(int framesPerSecond = 0, QWidget *parent = 0, char * name = 0);
  void perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar);
  virtual void initializeGL() = 0;
  virtual void resizeGL(int width, int height) = 0;
  virtual void paintGL() = 0;
  virtual void keyPressEvent(QKeyEvent *pEvent);

  /** Handles mouse press events on the QGLWidget. */
  void mousePressEvent(QMouseEvent *pEvent);

  /** Handles mouse move events on the QGLWidget. */
  void mouseMoveEvent(QMouseEvent *pEvent);

  /** Zoomin in and out of the cube */
  void wheelEvent (QWheelEvent * pEvent);

  public slots:
    virtual void timeOutSlot();

 private:
  QTimer *t_Timer;

 public:
  GLfloat fRotationX;
  GLfloat fRotationY;
  GLfloat fRotationZ;

  GLfloat fMoveUpDown;
  GLfloat fMoveLeftRight;
  GLfloat fMoveInOut;

  QSize viewport_size;					//< current size of the viewport.
  QPoint lastPos;

  /** Change settings for rendering. */
  void setRotation(GLfloat _x, GLfloat _y, GLfloat _z);
};

#endif // MY_GLWIDGET_H
