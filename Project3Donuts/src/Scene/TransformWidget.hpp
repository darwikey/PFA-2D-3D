#ifndef TRANSFORM_WIDGET_HPP
#define TRANSFORM_WIDGET_HPP

#include "global.hpp"

class Object;
class SceneRenderer;
class Camera;

//! \class TransformWidget
//! \brief 3D widget that will be render in the scene, user can manipulate it
class TransformWidget
{
public:
	enum class State {
		HIDE, TRANSLATION, ROTATION, SCALE
	};

	enum class Direction {
		X, Y, Z
	};

	//! \brief Constructor 
	TransformWidget(std::string fObjPath = std::string("resources/models/widget.obj"));
	~TransformWidget();

	//! \brief render the widget
	//! param fRenderer where the widget will be render
	//! param fCamera active camera
	//! param fSelectedObject the widget will be active on this object
    void render(SceneRenderer* fRenderer, Camera* fCamera, Object* fSelectedObject);

	//! \brief render the widget
	//! param fRenderer where the widget will be render
	//! param fCamera active camera
    void render(SceneRenderer* fRenderer, Camera* fCamera);

	//! \brief show the widget, and choose the transformation
	void changeState(TransformWidget::State fState);

	//! \brief tell if the widget is selected by the mouse
	bool isSelected();

	//! \brief select with the mouse the widget
	void select(QVector2D fMousePosition);

	//! \brief the widget can be manipulate with the mouse
	void activate(QVector2D fMousePosition);

	//! \brief unselect the widget, the mouse will not be able to use it
	void unselect();


private:
	QVector3D getDirection(Direction fDirection) const;
	void applyTransformation(Object* fObject, QVector3D fInitialSelectedObject, State fState, Direction fDirection, float fDelta) const;

	State mState = State::HIDE;
	bool mIsSelected = false;
	std::string mNameSelectedObject;
	QVector2D mInitialMousePosition = QVector2D(0.f, 0.f);
	QVector3D mInitialSelectedObject = QVector3D(0.f, 0.f, 0.f);
	Direction mDirection = Direction::X;

	std::string mObjPath;

	Object* mObjectX = nullptr;
	Object* mObjectY = nullptr;
	Object* mObjectZ = nullptr;
};


#endif
