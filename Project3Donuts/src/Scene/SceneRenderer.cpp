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
    //glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
    glCullFace(GL_BACK);

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, context()->device()->width() * retinaScale, context()->device()->height() * retinaScale);

}

void SceneRenderer::resizeGL(int fWidth, int fHeight){
    if(fHeight == 0)
        fHeight = 1;
    glViewport(0, 0, fWidth, fHeight);

}

void perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	GLdouble xmin, xmax, ymin, ymax;

	ymax = zNear * tan(fovy * M_PI / 360.0);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;

	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

void SceneRenderer::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	perspective(45.0f, (GLfloat)width() / (GLfloat)height(), 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0., 0., -50);
	glBegin(GL_TRIANGLES);
	Scene::getScene()->render();

	glEnd();
	glFlush();
}


void SceneRenderer::render(Object* fModel, bool fRenderForeground) {

    /*if(! fModel->isVboInitialized()){
		fModel->initVbo(this);
    }

	if (!fModel->getShader()->bind()){
        qWarning() << "Could not bind shader program";
        return;
    }

	if (fRenderForeground) {
		glDisable(GL_DEPTH_TEST);
	}
	
	fModel->draw(this);*/

	QMatrix4x4 _viewMatrix = Scene::getScene()->getCamera()->getViewMatrix();
	const QMatrix4x4& _projectionMatrix = Scene::getScene()->getCamera()->getProjectionMatrix();
	QMatrix4x4 _modelMatrix = fModel->getModelMatrix();

	/*glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, -10);*/
	/*glRotatef(fRotationX, 1.0f, 0.0f, 0.0f);
	glRotatef(fRotationY, 0.0f, 1.0f, 0.0f);
	glRotatef(fRotationZ, 0.0f, 0.0f, 1.0f);*/

	fModel->draw(this);

	/*fModel->getShader()->setUniformValue("viewProjectionMatrix", _projectionMatrix * _viewMatrix * _modelMatrix);
	fModel->getShader()->setUniformValue("normalMatrix", _modelMatrix.inverted().transposed());
	fModel->getShader()->setUniformValue("isSelected", fModel->isObjectSelected());
	fModel->getShader()->setUniformValue("enableShading", !fRenderForeground);

	fModel->getShader()->release();*/

    ++mFrame;

	/*if (fRenderForeground) {
		glEnable(GL_DEPTH_TEST);
	}*/
}

