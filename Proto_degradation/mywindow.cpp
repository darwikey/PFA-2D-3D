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

	Model* _model = Loader::getInstance()->getModel("cube1");

	if (_model != nullptr)
	{
		GLfloat _color = 0.f;

		for (auto _face :_model->triangles)
		{
			for (int i = 0; i < 3; i++)
			{
				if (_face.vertices[i]-1 >= 0 && _face.vertices[i]-1 < _model->vertices.size()){
					Vec3 _v = _model->vertices[_face.vertices[i] - 1];
					glVertex3f(_v.x, _v.y, _v.z);
					glColor3f(_color, _color, _color);
				}
			}
			_color += 1.f / _model->triangles.size();
		}
	}

	_model = Loader::getInstance()->getModel("cube2");

	if (_model != nullptr)
	{
		GLfloat _color = 0.f;

		for (auto _face :_model->triangles)
		{
			for (int i = 0; i < 3; i++)
			{
				if (_face.vertices[i]-1 >= 0 && _face.vertices[i]-1 < _model->vertices.size()){
					Vec3 _v = _model->vertices[_face.vertices[i] - 1];
					glVertex3f(_v.x + 3.f, _v.y, _v.z);
					glColor3f(_color, _color, _color);
				}
			}
			_color += 1.f / _model->triangles.size();
		}
	}

    glEnd();
}

