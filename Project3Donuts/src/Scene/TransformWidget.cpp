#include "TransformWidget.hpp"
#include "ObjLoader.hpp"
#include "SceneRenderer.hpp"
#include "Object.hpp"
#include "Scene.hpp"
#include "Camera.hpp"


TransformWidget::TransformWidget(){
}

TransformWidget::~TransformWidget(){
}


void TransformWidget::render(SceneRenderer* fRenderer, Object* fSelectedObject){
	if (mState != TransformWidget::State::HIDE
		&& mObjectX != nullptr
		&& fSelectedObject != nullptr) {

		mObjectX->moveObject(fSelectedObject->getPosition());
		mObjectY->moveObject(fSelectedObject->getPosition());
		mObjectZ->moveObject(fSelectedObject->getPosition());

		mObjectX->changeObjectOrientation(QVector3D(0.f, 0.f, -1.57f));
		//mObjectY->changeObjectOrientation(fSelectedObjects[0]->getRotation());
		mObjectZ->changeObjectOrientation(QVector3D(1.57f, 0.f, 0.f));

		fRenderer->render(mObjectX, true);
		fRenderer->render(mObjectY, true);
		fRenderer->render(mObjectZ, true);
	}
}


void TransformWidget::changeState(TransformWidget::State fState) {
	// Load the widget model
	if (mObjectX == nullptr) {
		mObjectX = new Object();
		mObjectY = new Object();
		mObjectZ = new Object();

		std::string _objPath = "resources/models/widget.obj";
		ObjLoader _loaderX(_objPath);
		ObjLoader _loaderY(_objPath);
		ObjLoader _loaderZ(_objPath);

		if (!_loaderX.load(mObjectX)
			|| !_loaderY.load(mObjectY)
			|| !_loaderZ.load(mObjectZ)){
			QMessageBox::critical(0, "Error", "Error opening " + QString(_objPath.c_str()));
		}

		mObjectX->computeColors(QVector3D(1.f, 0.f, 0.f));
		mObjectY->computeColors(QVector3D(0.f, 1.f, 0.f));
		mObjectZ->computeColors(QVector3D(0.f, 0.f, 1.f));
	}

	mState = fState;
}


bool TransformWidget::isSelected(){
	return mIsSelected;
}


void TransformWidget::select(QVector2D fMousePosition){
	if (mState == State::HIDE) {
		return;
	}

	mNameSelectedObject = Scene::getScene()->getNameSelectedObject();
	if (mNameSelectedObject == "") {
		return;
	}

	QVector3D _rayOrigin, _rayDirection;
	Scene::getScene()->getCamera()->getMouseRay(fMousePosition, _rayOrigin, _rayDirection);

	float _intersection = 0;
	bool _isCollisionX = mObjectX->getBoundingBox().isCollision(_rayOrigin, _rayDirection, mObjectX->getModelMatrix(), _intersection);
	bool _isCollisionY = mObjectY->getBoundingBox().isCollision(_rayOrigin, _rayDirection, mObjectY->getModelMatrix(), _intersection);
	bool _isCollisionZ = mObjectZ->getBoundingBox().isCollision(_rayOrigin, _rayDirection, mObjectZ->getModelMatrix(), _intersection);

	if (_isCollisionX)
		mDirection = Direction::X;
	else if (_isCollisionY)
		mDirection = Direction::Y;
	else if (_isCollisionZ)
		mDirection = Direction::Z;

	mIsSelected = _isCollisionX || _isCollisionY || _isCollisionZ;

	if (mIsSelected) {
		mInitialMousePosition = fMousePosition;
		Object* _object = Scene::getScene()->getObject(mNameSelectedObject);

		switch (mState) {
		case State::TRANSLATION:
			mInitialSelectedObject = _object->getPosition();
			break;

		case State::ROTATION:
			mInitialSelectedObject = _object->getRotation();
			break;

		case State::SCALE:
			mInitialSelectedObject = _object->getScale();
			break;

		default:
			break;
		}
	}
}


void TransformWidget::activate(QVector2D fMousePosition){
	Object* _object = Scene::getScene()->getObject(mNameSelectedObject);

	QVector3D _dir;

	switch (mDirection) {
	default:
	case Direction::X:
		_dir = QVector3D(1.f, 0.f, 0.f);
		break;

	case Direction::Y:
		_dir = QVector3D(0.f, 1.f, 0.f);
		break;

	case Direction::Z:
		_dir = QVector3D(0.f, 0.f, 1.f);
		break;
	}

	QVector3D _delta = ((fMousePosition.x() - mInitialMousePosition.x()) + (fMousePosition.y() - mInitialMousePosition.y())) * _dir;

	if (_object != nullptr) {
		switch (mState) {
		case State::TRANSLATION:
			_delta *= 2.f;
			_object->moveObject(mInitialSelectedObject + _delta);
			break;

		case State::ROTATION:
			_delta *= 2.f;
			_object->changeObjectOrientation(mInitialSelectedObject + _delta);
			break;

		case State::SCALE:
			//_delta *= 2.f;
			_object->changeObjectScale(mInitialSelectedObject + _delta);
			break;

		default:
			break;
		}
	}
}


void TransformWidget::unselect() {
	mIsSelected = false;
}