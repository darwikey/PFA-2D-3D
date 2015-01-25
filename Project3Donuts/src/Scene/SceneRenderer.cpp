#include "SceneRenderer.hpp"
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include "Scene.hpp"
#include "Object.hpp"
#include "Camera.hpp"


SceneRenderer::SceneRenderer(QWidget *fParent):MyGLWidget(60, fParent, "Render Window"){

}


void SceneRenderer::initializeGL(){


    makeCurrent();
    initializeOpenGLFunctions();

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
    glCullFace(GL_BACK);


	/*GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_shininess[] = { 50.0 };

	glShadeModel(GL_SMOOTH);

	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);*/
	// Somewhere in the initialization part of your program…
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Create light components
	GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
	GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	/*QVector3D _lampPosition(1, 0, 0);// = Scene::getScene()->getCamera()->getViewMatrix() * QVector3D(3, 3, 3);
	GLfloat light_position[] = { _lampPosition.x(), _lampPosition.y(), _lampPosition.z(), 1.f };*/

	// Assign created components to GL_LIGHT0
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	//glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, context()->device()->width() * retinaScale, context()->device()->height() * retinaScale);

}

void SceneRenderer::resizeGL(int fWidth, int fHeight){
    if(fHeight == 0)
        fHeight = 1;
    glViewport(0, 0, fWidth, fHeight);

}


void SceneRenderer::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Scene::getScene()->getCamera()->applyProjectionMatrix((float)width() / height());

	QVector3D _lampPosition(0,1, 1);// = Scene::getScene()->getCamera()->getViewMatrix() * QVector3D(3, 3, 3);
	GLfloat light_position[] = { _lampPosition.x(), _lampPosition.y(), _lampPosition.z(), 1.f };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	Scene::getScene()->render();

	glFlush();
}


void SceneRenderer::render(Object* fModel, bool fRenderForeground) {

	if (fRenderForeground) {
		glDisable(GL_DEPTH_TEST);
		glDisable(GL_LIGHTING);
	}
	
	glBegin(GL_TRIANGLES);
	fModel->draw(this);
	glEnd();
	
    ++mFrame;

	if (fRenderForeground) {
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
	}
}

