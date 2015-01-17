#ifndef TRANSFORM_WIDGET_HPP
#define TRANSFORM_WIDGET_HPP

#include "global.hpp"

class Object;
class SceneRenderer;

class TransformWidget
{
public:
	enum class State {
		HIDE, TRANSLATION, ROTATION, SCALE
	};

	TransformWidget();
	~TransformWidget();

	void render(SceneRenderer* fRenderer, const std::vector<Object*>& fSelectedObjects);

	//! \brief show the widget, and choose the transformation
	void changeState(TransformWidget::State fState);

private:
	Object* mObjectX = nullptr;
	Object* mObjectY = nullptr;
	Object* mObjectZ = nullptr;
	State mState = State::HIDE;
};


#endif
