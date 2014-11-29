#ifndef SCENERENDERER_HPP
#define SCENERENDERER_HPP

#include "MyGLWidget.hpp"
#include "obj_loader.h"
#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>

#include"Chargeur.hpp"
#include"Model.hpp"
class SceneRenderer : public MyGLWidget
{

public:
    SceneRenderer();
    void initialize();
    void render();

private:
    GLuint loadShader(GLenum type, const char *source);

    GLuint m_matrixUniform;

    QMatrix4x4 matrix;


    QOpenGLShaderProgram *m_program;
    int m_frame;
};

#endif // SCENERENDERER_HPP
