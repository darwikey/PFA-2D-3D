#ifndef TRANSFORM_WIDGET_HPP
#define TRANSFORM_WIDGET_HPP

#include "global.hpp"

class Object;
class SceneRenderer;
class Camera;

class TransformWidget
{
public:
	enum class State {
		HIDE, TRANSLATION, ROTATION, SCALE
	};

	enum class Direction {
		X, Y, Z
	};

	TransformWidget();
	~TransformWidget();

	//! \brief render the widget
	void render(SceneRenderer* fRenderer, Camera* fCamera, Object* fSelectedObject);

	//! \brief show the widget, and choose the transformation
	void changeState(TransformWidget::State fState);

	//! \brief tell if the widget is selected by the mouse
	bool isSelected();

	// \brief select with the mouse the widget
	void select(QVector2D fMousePosition);

	//! \brief the widget can be manipulate with the mouse
	void activate(QVector2D fMousePosition);

	//! \brief unselect the widget, the mouse will not be able to use it
	void unselect();


private:
	State mState = State::HIDE;
	bool mIsSelected = false;
	std::string mNameSelectedObject;
	QVector2D mInitialMousePosition = QVector2D(0.f, 0.f);
	QVector3D mInitialSelectedObject = QVector3D(0.f, 0.f, 0.f);
	Direction mDirection = Direction::X;

	Object* mObjectX = nullptr;
	Object* mObjectY = nullptr;
	Object* mObjectZ = nullptr;
};


#endif
