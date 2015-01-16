#include "SceneRenderer.hpp"
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include "Scene.hpp"
#include "Object.hpp"
#include "Camera.hpp"


SceneRenderer::SceneRenderer(){

}


void SceneRenderer::initialize()
{


    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
    glCullFace(GL_BACK);

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

}


void SceneRenderer::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::getScene()->render();
}


void SceneRenderer::render(Object* fModel, bool fRenderForeground) {

    if(! fModel->isVboInitialized()){
		fModel->initVbo(this);
    }

	if (!fModel->getShader()->bind()){
        qWarning() << "Could not bind shader program";
        return;
    }

	if (fRenderForeground) {
		glDisable(GL_DEPTH_TEST);
	}
	
	fModel->draw(this);

	QMatrix4x4 _viewMatrix = Scene::getScene()->getCamera()->getViewMatrix();
	const QMatrix4x4& _projectionMatrix = Scene::getScene()->getCamera()->getProjectionMatrix();

	QMatrix4x4 _modelMatrix, _scale;
	_viewMatrix.translate(fModel->getPosition());
	_viewMatrix.scale(fModel->getScale());

	fModel->getShader()->setUniformValue("matrix", _projectionMatrix * _viewMatrix);
	fModel->getShader()->setUniformValue("isSelected", fModel->isObjectSelected());

	fModel->getShader()->release();

    ++mFrame;

	if (fRenderForeground) {
		glEnable(GL_DEPTH_TEST);
	}
}

