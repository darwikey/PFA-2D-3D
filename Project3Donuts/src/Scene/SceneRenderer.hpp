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

	//! \brief init the opengl context and functions
    void initializeGL() override;

	//! \brief init opengl parameter
	void initOpengl();

	//! \brief call when the window is resize
	void resizeGL(int width, int height) override;

	//! \brief call at each frame, render everything
	void paintGL() override;

	//! \brief 
	//! \param fModel model to render
	//! \param fCamera camera used
	//! \param fRenderForeground if true draw the object in front of other object
	//! \param fRenderlowResolution if the model have a low resolution model, use it
	void render(Object* fModel, Camera* fCamera, bool fRenderForeground, bool fRenderLowResolution = false);
    
	//! \brief change the background color
	void changeBackground(QVector3D fColor);

	//! \brief set the background color
	void setBackgroundColor(QColor fColor);

private:
	QVector3D mBackGroundColor;
	int mScreenWidth = 0;
	int mScreenHeight = 0;

};

#endif // SCENERENDERER_HPP
