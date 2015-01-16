#ifndef SCENERENDERER_HPP
#define SCENERENDERER_HPP

#include "MyGLWidget.hpp"
#include "global.hpp"

class Object;

class SceneRenderer : public MyGLWidget{

public:
    SceneRenderer();
    void initialize();
    void render();
	void render(Object* fModel, bool fRenderForeground);

private:

    int mFrame = 0;
};

#endif // SCENERENDERER_HPP
