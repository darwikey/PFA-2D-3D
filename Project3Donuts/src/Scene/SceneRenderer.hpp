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
    void resizeGL(int width, int height) override;
	void paintGL() override;
	void render(Object* fModel, bool fRenderForeground);
    QOpenGLFunctions * getContext();

private:
    QOpenGLFunctions *mcontext;
};

#endif // SCENERENDERER_HPP
