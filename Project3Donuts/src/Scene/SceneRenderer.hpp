#ifndef SCENERENDERER_HPP
#define SCENERENDERER_HPP

#include <QOpenGLFunctions>
#include "MyGLWidget.hpp"
#include "global.hpp"

class Object;
class Camera;

class SceneRenderer : public MyGLWidget{

public:
    SceneRenderer(QWidget *fParent = 0);

    void initializeGL() override;
	void initOpengl();
	void resizeGL(int width, int height) override;
	void paintGL() override;
	void render(Object* fModel, Camera* fCamera, bool fRenderForeground);
    void changeBackground(QColor fColor);
	void changeBackground(QVector3D fColor);
	void setBackgroundColor(QColor fColor);

private:
	QVector3D mBackGroundColor;
	int mScreenWidth = 0;
	int mScreenHeight = 0;

};

#endif // SCENERENDERER_HPP
