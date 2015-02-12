#ifndef SCENERENDERER_HPP
#define SCENERENDERER_HPP

#include <QOpenGLFunctions>
#include "MyGLWidget.hpp"
#include "global.hpp"

class Object;

class SceneRenderer : public MyGLWidget{

public:
    SceneRenderer(QWidget *fParent = 0);

    void initializeGL() override;
	void initOpengl(QVector3D fColor);
	void resizeGL(int width, int height) override;
	void paintGL() override;
	void render(Object* fModel, bool fRenderForeground);

private:

	GLuint fboId = 0;
};

#endif // SCENERENDERER_HPP
