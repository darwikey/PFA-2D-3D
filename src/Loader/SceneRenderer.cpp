#include "SceneRenderer.hpp"
#include "Scene.hpp"
#include "Object.hpp"
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>



static const char *vertexShaderSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
    "layout(location = 1) in vec3 vertexColor;\n"
        "out vec3 fragmentColor;\n"
    "uniform mat4 matrix;\n"
    "void main() {\n"
    "   gl_Position = matrix * vec4(vertexPosition_modelspace,1);\n"
        "fragmentColor = vertexColor;\n"
    "}\n";

static const char *fragmentShaderSource =
        "#version 330 core\n"
        "in vec3 fragmentColor;\n"
        "out vec3 color;\n"
    "void main() {\n"
        "color = fragmentColor;\n"
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
    glCullFace(GL_BACK);

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);

}


void SceneRenderer::render() {

    Object* _model = Scene::getScene()->getObject("cube1");

    if(! _model->isVboInitialized()){
		_model->initVbo(this);
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!mProgram->bind()){
        qWarning() << "Could not bind shader program";
        return;
    }

    mMatrix = QMatrix4x4();

	QVector3D _modelCenter = _model->getBoundingBox().getCenter();
	
	GLdouble r = _modelCenter.distanceToPoint(_model->getBoundingBox().mVector1);

    GLfloat fDistance = r / 0.57735f; // where 0.57735f is tan(30 degrees)

    GLfloat zNear = fDistance - r;
    GLfloat zFar = fDistance + r;

    //printf("bounding box : x -- %f, %f, y -- %f, %f, z -- %f, %f\n",_model->BoundingBox.x_max,_model->BoundingBox.x_min,_model->BoundingBox.y_max,_model->BoundingBox.y_min,_model->BoundingBox.z_max,_model->BoundingBox.z_min);
    //printf("center : %lf, %lf, %lf\n", centerx, centery, centerz);
    //printf("r : %lf, dist : %f, zNear : %f, zFar : %f\n",r, fDistance, zNear, zFar);
    QVector3D _eye = QVector3D(0., 0., fDistance);
    QVector3D _center = QVector3D(0., 0., 0.);
    QVector3D _up = QVector3D(0.0, 1.0, 0.0);


    mMatrix.frustum(-r, +r, -r, +r, zNear, zFar);
    mMatrix.lookAt(_eye, _center, _up);
    mMatrix.translate(-_center.x(), -_center.y(), -_center.z());
    mMatrix.translate(fMoveLeftRight, fMoveUpDown, fMoveInOut);
    mMatrix.rotate(fRotationX, 1.0f, 0.0f, 0.0f);
    mMatrix.rotate(fRotationY, 0.0f, 1.0f, 0.0f);
    mMatrix.rotate(fRotationZ, 0.0f, 0.0f, 1.0f);


    mProgram->setUniformValue(mMatrixUniform, mMatrix);

	_model->draw(this);

    mProgram->release();

    ++mFrame;
}
