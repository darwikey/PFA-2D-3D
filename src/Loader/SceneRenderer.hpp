#ifndef SCENERENDERER_HPP
#define SCENERENDERER_HPP

#include "MyGLWidget.hpp"
#include "global.hpp"


class SceneRenderer : public MyGLWidget
{

public:
    SceneRenderer();
    void initialize();
    void render();
    QOpenGLShaderProgram* getShaderProgram();

private:
    GLuint loadShader(GLenum type, const char *source);


    GLuint mMatrixUniform = 0;
    QMatrix4x4 mMatrix;

    QOpenGLShaderProgram* mProgram = nullptr;
    int mFrame = 0;
};

#endif // SCENERENDERER_HPP
