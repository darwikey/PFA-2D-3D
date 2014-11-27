#include "myWindow.h"
#include"loader.h"

myWindow::myWindow(QWidget *parent)
    : myGLWidget(60, parent, "Objet Loader")
{

}

void myWindow::initializeGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

void myWindow::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    perspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

void myWindow::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(fMoveLeftRight, fMoveUpDown, fMoveInOut);
    glRotatef(fRotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(fRotationY, 0.0f, 1.0f, 0.0f);
    glRotatef(fRotationZ, 0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
        for(int i =0;i<Loader::model.vertices.size();i++){
        glVertex3f(Loader::model.vertices[i].getX(), Loader::model.vertices[i].getY(), Loader::model.vertices[i].getZ());
        }

    glEnd();
}


