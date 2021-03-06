#ifndef MYWINDOW_H
#define MYWINDOW_H

#include "myGLWidget.h"
#include "obj_loader.h"

class myWindow : public myGLWidget
{
    Q_OBJECT
public:
    explicit myWindow(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
    void paintGL();
};

#endif // MYWINDOW_H
