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


GLuint SceneRenderer::loadShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    return shader;
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


void SceneRenderer::render(Object* fModel) {

    if(! fModel->isVboInitialized()){
		fModel->initVbo(this);
    }

	if (!fModel->getShader()->bind()){
        qWarning() << "Could not bind shader program";
        return;
    }

	
	fModel->draw(this);

	QMatrix4x4 _viewMatrix = Scene::getScene()->getCamera()->getViewMatrix();
	const QMatrix4x4& _projectionMatrix = Scene::getScene()->getCamera()->getProjectionMatrix();

	QMatrix4x4 _modelMatrix, _scale;
	_viewMatrix.translate(fModel->getPosition());
	_viewMatrix.scale(fModel->getScale());

	static uint _MatrixLocation = fModel->getShader()->uniformLocation("matrix");
	fModel->getShader()->setUniformValue(_MatrixLocation, _projectionMatrix * _viewMatrix);

	fModel->getShader()->release();

    ++mFrame;
}

