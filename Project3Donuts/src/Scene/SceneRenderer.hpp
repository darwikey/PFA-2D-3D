#ifndef SCENERENDERER_HPP
#define SCENERENDERER_HPP

#include <QOpenGLFunctions>
#include "MyGLWidget.hpp"
#include "global.hpp"

class Object;
class Camera;

//! \class SceneRenderer
//! \brief Widget where the scene is render
class SceneRenderer : public MyGLWidget{

public:
    SceneRenderer(QWidget *fParent = 0);

    void initializeGL() override;
	void initOpengl();
	void resizeGL(int width, int height) override;
	void paintGL() override;

	//! \brief 
	//! \param fModel model to render
	//! \param fCamera camera used
	//! \param fRenderForeground if true draw the object in front of other object
	//! \param fRenderlowResolution if the model have a low resolution model, use it
	void render(Object* fModel, Camera* fCamera, bool fRenderForeground, bool fRenderLowResolution = false);
    
	void changeBackground(QVector3D fColor);
	void setBackgroundColor(QColor fColor);

private:
	QVector3D mBackGroundColor;
	int mScreenWidth = 0;
	int mScreenHeight = 0;

};

#endif // SCENERENDERER_HPP
