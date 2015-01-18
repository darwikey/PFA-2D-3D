#ifndef SCENERENDERER_HPP
#define SCENERENDERER_HPP

#include "MyGLWidget.hpp"
#include "global.hpp"

class Object;

class SceneRenderer : public MyGLWidget{

public:
    SceneRenderer(QWidget *fParent = 0);
    void initializeGL();
    void resizeGL(int width, int height);
	void paintGL();
	void render(Object* fModel, bool fRenderForeground);

private:

    int mFrame = 0;
};

#endif // SCENERENDERER_HPP
