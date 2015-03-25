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
	QColor _colorRGB = settings.value("Viewer/background_color", QColor(0, 0, 102)).value<QColor>();
	setBackgroundColor(_colorRGB);

	makeCurrent();
    initializeOpenGLFunctions();

    initOpengl();

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, context()->device()->width() * retinaScale, context()->device()->height() * retinaScale);
}


void SceneRenderer::initOpengl(){
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_DEPTH_CLAMP);
	glCullFace(GL_BACK);
}


void SceneRenderer::resizeGL(int fWidth, int fHeight){
    if(fHeight == 0)
        fHeight = 1;
	mScreenWidth = fWidth;
	mScreenHeight = fHeight;
}


void SceneRenderer::paintGL() {

	this->makeCurrent();

	// Viewport
	glViewport(0, 0, mScreenWidth, mScreenHeight);

	// BackgroundColor
	changeBackground(mBackGroundColor);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Object::switchShader(Object::Shader::STANDARD_SHADING);

	Scene::getScene()->render();

}

void SceneRenderer::render(Object* fModel, Camera* fCamera, bool fRenderForeground, bool fRenderLowResolution) {

	Object* _model = fModel;
	if (fRenderLowResolution && fModel->getLowModel() != nullptr){
		_model = fModel->getLowModel();
	}


	// Init VBO
	if (!_model->isVboInitialized()){
		_model->initVbo(this);
    }

	// Bind the shader
	if (!_model->getShader()->bind()){
        qWarning() << "Could not bind shader program";
        return;
    }


	QMatrix4x4 _viewMatrix = fCamera->getViewMatrix();
	const QMatrix4x4& _projectionMatrix = fCamera->getProjectionMatrix();

	QMatrix4x4 _modelMatrix = fModel->getModelMatrix();

	// Matrices
	_model->getShader()->setUniformValue("viewProjectionMatrix", _projectionMatrix * _viewMatrix * _modelMatrix);
	_model->getShader()->setUniformValue("modelMatrix", _modelMatrix);
	_model->getShader()->setUniformValue("normalMatrix", _modelMatrix.inverted().transposed().toGenericMatrix<3, 3>());
	_model->getShader()->setUniformValue("viewMatrixInv", _viewMatrix.inverted());

	// Parameters
	_model->getShader()->setUniformValue("isSelected", _model->isObjectSelected());
	_model->getShader()->setUniformValue("globalColor", _model->getGlobalColor());
	_model->getShader()->setUniformValue("enableShading", !fRenderForeground);

	QVector4D _lamps[8];
	_lamps[0] = QVector4D(Scene::getScene()->getCamera()->getPosition(),1);
	//_lamps[0] = QVector4D(QVector3D(0, 5, 5), 1);
	_model->getShader()->setUniformValueArray("lamps", _lamps, 8);


	if (fRenderForeground) {
		glDisable(GL_DEPTH_TEST);
	}

	// Draw the object
	_model->draw(this);


	if (fRenderForeground) {
		glEnable(GL_DEPTH_TEST);
	}

	// Unbind the shader
	_model->getShader()->release();

}


void SceneRenderer::changeBackground(QColor fColor){
    QVector3D _color(fColor.red(), fColor.green(), fColor.blue());
    _color = _color/ 255.f;
    glClearColor(_color.x(), _color.y(), _color.z(), 1.f);
}


void SceneRenderer::changeBackground(QVector3D fColor){
	glClearColor(fColor.x(), fColor.y(), fColor.z(), 1.f);
}


void SceneRenderer::setBackgroundColor(QColor fColor){
	mBackGroundColor = QVector3D(fColor.red(), fColor.green(), fColor.blue());
	mBackGroundColor /= 255.f;
}