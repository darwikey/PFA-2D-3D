#include "SceneRenderer.hpp"
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include "Scene.hpp"
#include "Object.hpp"
#include "Camera.hpp"

static const char *vertexShaderSource =
	"#version 330 core\n"
	"layout(location = 0) in vec3 vertexPosition_modelspace;\n"
	"layout(location = 1) in vec3 vertexColor;\n"
	"out vec3 fragmentColor;\n"
	"uniform mat4 matrix;\n"
	"void main() {\n"
	"   gl_Position = matrix * vec4(vertexPosition_modelspace,1);\n"
	"   fragmentColor = vertexColor;\n"
	"}\n";

static const char *fragmentShaderSource =
	"#version 330 core\n"
	"in vec3 fragmentColor;\n"
	"out vec3 color;\n"
	"void main() {\n"
	"   color = fragmentColor;\n"
	"}\n";


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
    mProgram = new QOpenGLShaderProgram(this);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	mProgram->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    //m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "StandardShading.vertexshader");
    //m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "StandardShading.fragmentshader");
    //m_program->bindAttributeLocation("vertexColor",1);
    //m_program->bindAttributeLocation("vertexPosition_modelspace",0);

    qDebug() << mProgram->log();

	mProgram->link();
	mMatrixUniform = mProgram->uniformLocation("matrix");


    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
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

	if (!mProgram->bind()){
        qWarning() << "Could not bind shader program";
        return;
    }


	QVector3D _modelCenter(1.f, 0.f, 0.f);//fModel->getBoundingBox().getCenter();
	
	fModel->draw(this);

	QMatrix4x4 _cameraMatrix = Scene::getScene()->getCamera()->getViewMatrix();

	QMatrix4x4 _modelMatrix;
	_modelMatrix.translate(fModel->getPosition());


    mProgram->setUniformValue(mMatrixUniform, _cameraMatrix * _modelMatrix);

    mProgram->release();

    ++mFrame;
}


QOpenGLShaderProgram* SceneRenderer::getShaderProgram(){ 
	return mProgram;
}
