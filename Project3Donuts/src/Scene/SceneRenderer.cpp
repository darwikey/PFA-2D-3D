#include "SceneRenderer.hpp"
#include <QtGui/QMatrix4x4>
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
	initOpengl(QVector3D(0.f, 0.f, 0.4f));

	/*GLint dims[2];
	glGetIntegerv(GL_MAX_VIEWPORT_DIMS, &dims[0]);
	int _MaxTexSize = 0;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &_MaxTexSize);
	int _MaxRenderBufferSize = 0;
	glGetIntegerv(GL_MAX_RENDERBUFFER_SIZE, &_MaxRenderBufferSize);
	std::cout << "dims  " << dims[0] << " " << dims[1] << "tex " << _MaxTexSize << " render " << _MaxRenderBufferSize << std::endl;*/

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, context()->device()->width() * retinaScale, context()->device()->height() * retinaScale);
}


void SceneRenderer::initOpengl(QVector3D fColor){
	glClearColor(fColor.x(), fColor.y(), fColor.z(), 1.f);

	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glCullFace(GL_BACK);

}


void SceneRenderer::resizeGL(int fWidth, int fHeight){
    if(fHeight == 0)
        fHeight = 1;
    glViewport(0, 0, fWidth, fHeight);
}

void SceneRenderer::paintGL() {

	//this->makeCurrent();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Object::switchShader(Object::Shader::STANDARD_SHADING);

	Scene::getScene()->render();

}

void SceneRenderer::render(Object* fModel, bool fRenderForeground) {

    if(! fModel->isVboInitialized()){
		fModel->initVbo(this);
    }

	// Bind the shader
	if (!fModel->getShader()->bind()){
        qWarning() << "Could not bind shader program";
        return;
    }


	QMatrix4x4 _viewMatrix = Scene::getScene()->getCamera()->getViewMatrix();
	const QMatrix4x4& _projectionMatrix = Scene::getScene()->getCamera()->getProjectionMatrix();

	QMatrix4x4 _modelMatrix = fModel->getModelMatrix();

	fModel->getShader()->setUniformValue("viewProjectionMatrix", _projectionMatrix * _viewMatrix * _modelMatrix);
	fModel->getShader()->setUniformValue("normalMatrix", _modelMatrix.inverted().transposed());
	fModel->getShader()->setUniformValue("isSelected", fModel->isObjectSelected());
	fModel->getShader()->setUniformValue("enableShading", !fRenderForeground);


	if (fRenderForeground) {
		glDisable(GL_DEPTH_TEST);
	}

	// Draw the object
	fModel->draw(this);


	if (fRenderForeground) {
		glEnable(GL_DEPTH_TEST);
	}

	// Unbind the shader
	fModel->getShader()->release();

}
