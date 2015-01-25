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

	glBegin(GL_TRIANGLES);
	Scene::getScene()->render();

	glEnd();
	glFlush();
}


void SceneRenderer::render(Object* fModel, bool fRenderForeground) {

	if (fRenderForeground) {
		glDisable(GL_DEPTH_TEST);
	}
	
	fModel->draw(this);

	
    ++mFrame;

	if (fRenderForeground) {
		glEnable(GL_DEPTH_TEST);
	}
}

