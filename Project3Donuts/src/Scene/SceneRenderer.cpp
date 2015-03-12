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
    QSettings settings("settings.ini", QSettings::IniFormat);
    makeCurrent();
    initializeOpenGLFunctions();

    QColor _colorRGB = settings.value("Viewer/background_color",QColor(0,0,102)).value<QColor>();
    QVector3D _color(_colorRGB.red(), _colorRGB.green(), _colorRGB.blue());
    initOpengl(_color/255.f);

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

	this->makeCurrent();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Object::switchShader(Object::Shader::STANDARD_SHADING);

	Scene::getScene()->render();

}

void SceneRenderer::render(Object* fModel, Camera* fCamera, bool fRenderForeground) {

    if(! fModel->isVboInitialized()){
		fModel->initVbo(this);
    }

	// Bind the shader
	if (!fModel->getShader()->bind()){
        qWarning() << "Could not bind shader program";
        return;
    }


	QMatrix4x4 _viewMatrix = fCamera->getViewMatrix();
	const QMatrix4x4& _projectionMatrix = fCamera->getProjectionMatrix();

	QMatrix4x4 _modelMatrix = fModel->getModelMatrix();

	// Matrices
	fModel->getShader()->setUniformValue("viewProjectionMatrix", _projectionMatrix * _viewMatrix * _modelMatrix);
	fModel->getShader()->setUniformValue("modelMatrix", _modelMatrix);
	fModel->getShader()->setUniformValue("normalMatrix", _modelMatrix.inverted().transposed().toGenericMatrix<3, 3>());
	fModel->getShader()->setUniformValue("viewMatrixInv", _viewMatrix.inverted());

	// Parameters
	fModel->getShader()->setUniformValue("isSelected", fModel->isObjectSelected());
	fModel->getShader()->setUniformValue("globalColor", fModel->getGlobalColor());
	fModel->getShader()->setUniformValue("enableShading", !fRenderForeground);

	QVector4D _lamps[8];
	_lamps[0] = QVector4D(Scene::getScene()->getCamera()->getPosition(),1);

	fModel->getShader()->setUniformValueArray("lamps", _lamps, 8);


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

void SceneRenderer::ChangeBackground(QColor fColor)
{
    QVector3D _color(fColor.red(), fColor.green(), fColor.blue());
    _color = _color/ 255.f;
    glClearColor(_color.x(), _color.y(), _color.z(), 1.f);
}
