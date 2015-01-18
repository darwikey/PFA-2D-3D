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

	QMatrix4x4 _modelMatrix;
	_modelMatrix.translate(fModel->getPosition());
	const float _radTodeg = 57.29578f;
	_modelMatrix.rotate(_radTodeg * fModel->getRotation().x(), QVector3D(1.f, 0.f, 0.f));
	_modelMatrix.rotate(_radTodeg * fModel->getRotation().y(), QVector3D(0.f, 1.f, 0.f));
	_modelMatrix.rotate(_radTodeg * fModel->getRotation().z(), QVector3D(0.f, 0.f, 1.f));
	_modelMatrix.scale(fModel->getScale());

	fModel->getShader()->setUniformValue("viewProjectionMatrix", _projectionMatrix * _viewMatrix * _modelMatrix);
	fModel->getShader()->setUniformValue("normalMatrix", _modelMatrix.inverted().transposed());
	fModel->getShader()->setUniformValue("isSelected", fModel->isObjectSelected());

	fModel->getShader()->release();

    ++mFrame;

	if (fRenderForeground) {
		glEnable(GL_DEPTH_TEST);
	}
}

