#include "myWindow.h"
#include"loader.h"
//#include "glut/include/GL/glut.h"

#define GL_GLEXT_PROTOTYPES

myWindow::myWindow(QWidget *parent)
    : myGLWidget(60, parent, "Objet Loader")
{

}

void myWindow::initializeGL()
{
    initializeGLFunctions();

	glShadeModel(GL_SMOOTH);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1.0f);
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);

     // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // set up light colors (ambient, diffuse, specular)
    GLfloat lightKa[] = {.2f, .2f, .2f, 1.0f};  // ambient light
    GLfloat lightKd[] = {.7f, .7f, .7f, 1.0f};  // diffuse light
    GLfloat lightKs[] = {1, 1, 1, 1};           // specular light
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightKa);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightKd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightKs);

    // position the light
    float lightPos[4] = {0, 0, 20, 1}; // positional light
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_LIGHT0);


    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    Model* _model = Loader::getInstance()->getModel("cube1");

    glGenBuffers(2, &_model->vboId[0]);
    glBindBuffer(GL_ARRAY_BUFFER, _model->vboId[0]);
    glBufferData(GL_ARRAY_BUFFER, _model->vertices.size()*sizeof(Coordinate3d), &(_model->vertices[0]), GL_STATIC_DRAW);

    glGenBuffers(1, &_model->elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _model->elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _model->indices.size() * sizeof(uint), &(_model->indices[0]), GL_STATIC_DRAW);

    glGenBuffers(2, &_model->vboId[1]);
    glBindBuffer(GL_ARRAY_BUFFER, _model->vboId[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(_model->color.size()) * sizeof(Coordinate3d), &(_model->color[0]), GL_STATIC_DRAW);

    glVertexAttribPointer((GLuint) 0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer((GLuint) 1, 3, GL_FLOAT, GL_FALSE, 0, 0);
}

void myWindow::resizeGL(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
    Model* _model = Loader::getInstance()->getModel("cube1");
    GLdouble left = (_model->BoundingBox.x_max+_model->BoundingBox.x_min)/2 - (_model->BoundingBox.z_max-_model->BoundingBox.z_min);
    GLdouble right = (_model->BoundingBox.x_max+_model->BoundingBox.x_min)/2 + (_model->BoundingBox.z_max-_model->BoundingBox.z_min);
    GLdouble bottom = (_model->BoundingBox.y_max+_model->BoundingBox.y_min)/2 - (_model->BoundingBox.z_max-_model->BoundingBox.z_min);
    GLdouble top = (_model->BoundingBox.y_max+_model->BoundingBox.y_min)/2 + (_model->BoundingBox.z_max-_model->BoundingBox.z_min);
    GLfloat zNear = 0.01;
    GLfloat zFar = zNear + 100.0f;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(left, right, bottom, top, zNear, zFar);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //gluLookAt (0., 0., 2*(_model->BoundingBox.z_max-_model->BoundingBox.z_min), (_model->BoundingBox.x_max+_model->BoundingBox.x_min)/2, (_model->BoundingBox.y_max+_model->BoundingBox.y_min)/2, (_model->BoundingBox.z_max+_model->BoundingBox.z_min)/2, 0.0, 1.0, 0.0);
}

void myWindow::paintGL()
{
    Model* _model = Loader::getInstance()->getModel("cube1");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(fMoveLeftRight, fMoveUpDown, fMoveInOut);
    glRotatef(fRotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(fRotationY, 0.0f, 1.0f, 0.0f);
    glRotatef(fRotationZ, 0.0f, 0.0f, 1.0f);


    glEnableVertexAttribArray(0);
    // Index buffer
     glBindBuffer(GL_ARRAY_BUFFER, _model->vboId[0]);

     // Draw the triangles !

     glVertexAttribPointer(
         0,                  // attribute
         3,                  // size
         GL_FLOAT,           // type
         GL_FALSE,           // normalized?
         0,                  // stride
         (void*)0            // array buffer offset
     );

     // 2nd attribute buffer : colors
     glEnableVertexAttribArray(1);
     glBindBuffer(GL_ARRAY_BUFFER, _model->vboId[1]);
     glVertexAttribPointer(
         1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
         3,                                // size
         GL_FLOAT,                         // type
         GL_FALSE,                         // normalized?
         0,                                // stride
         (void*)0                          // array buffer offset
     );

     //not working, no shader
     glBindBuffer(GL_ARRAY_BUFFER, _model->elementbuffer);
     // Draw the triangles !
     glDrawElements(
         GL_TRIANGLES,      // mode
         _model->indices.size(),    // count
         GL_UNSIGNED_INT,   // type
         (void*)0           // element array buffer offset
     );

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);


}

