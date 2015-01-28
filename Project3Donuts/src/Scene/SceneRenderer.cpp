#include "SceneRenderer.hpp"
#include <QtGui/QMatrix4x4>
#include <QOpenGLFunctions>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include "Scene.hpp"
#include "Object.hpp"
#include "Camera.hpp"

SceneRenderer::SceneRenderer(QWidget *fParent):MyGLWidget(60, fParent, "Render Window"){
    mcontext = new QOpenGLFunctions();
}

void SceneRenderer::initializeGL(){
    makeCurrent();

    mcontext->initializeOpenGLFunctions();

    mcontext->glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    mcontext->glDepthFunc(GL_LESS);
    mcontext->glEnable(GL_CULL_FACE);
    mcontext->glEnable(GL_DEPTH_TEST);
    mcontext->glEnable(GL_DEPTH_CLAMP);
    mcontext->glCullFace(GL_BACK);
    mcontext->glEnable(GL_LIGHTING);
    mcontext->glEnable(GL_LIGHT0);

    // Create light components
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };

    /*QV   ector3D _lampPosition(1, 0, 0);// = Scene::getScene()->getCamera()->getViewMatrix() * QVector3D(3, 3, 3);
GLfloat light_position[] = { _lampPosition.x(), _lampPosition.y(), _lampPosition.z(), 1.f };*/
    // Assign created components to GL_LIGHT0
    /*glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);*/
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    mcontext->glEnable(GL_COLOR_MATERIAL);
    /*glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);*/
    const qreal retinaScale = devicePixelRatio();
    mcontext->glViewport(0, 0, context()->device()->width() * retinaScale, context()->device()->height() * retinaScale);
}

void SceneRenderer::resizeGL(int fWidth, int fHeight){
    if(fHeight == 0)
        fHeight = 1;
    mcontext->glViewport(0, 0, fWidth, fHeight);
}

void SceneRenderer::paintGL() {
    mcontext->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    float _aspect = (float)width() / height();
    Scene::getScene()->getCamera()->applyProjectionMatrix(_aspect);
    const float _zNear = 1.f;
    const float _zFar = 1000.f;
    GLdouble _ymax = _zNear * tan(60. * M_PI / 360.0);
    GLdouble _ymin = -_ymax;
    GLdouble _xmin = _ymin * _aspect;
    GLdouble _xmax = _ymax * _aspect;
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    //glFrustum(_xmin, _xmax, _ymin, _ymax, _zNear, _zFar);
    QVector3D _lampPosition(0,1, 1);// = Scene::getScene()->getCamera()->getViewMatrix() * QVector3D(3, 3, 3);
    GLfloat light_position[] = { _lampPosition.x(), _lampPosition.y(), _lampPosition.z(), 1.f };
    //glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    Scene::getScene()->render();
    mcontext->glFlush();
}

void SceneRenderer::render(Object* fModel, bool fRenderForeground) {
    if (fRenderForeground) {
        mcontext->glDisable(GL_DEPTH_TEST);
        mcontext->glDisable(GL_LIGHTING);
    }

    //glBegin(GL_TRIANGLES);
    fModel->draw(this);
    //glEnd();
    if (fRenderForeground) {
        mcontext->glEnable(GL_DEPTH_TEST);
        mcontext->glEnable(GL_LIGHTING);
    }
}

QOpenGLFunctions * SceneRenderer::getContext(){
    return mcontext;
}
