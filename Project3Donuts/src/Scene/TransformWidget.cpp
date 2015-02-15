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

		//Translation
		mObjectX->moveObject(fSelectedObject->getPosition());
		mObjectY->moveObject(fSelectedObject->getPosition());
		mObjectZ->moveObject(fSelectedObject->getPosition());

		//Orientation
		mObjectX->changeObjectOrientation(QVector3D(0.f, 0.f, -1.57f));
		mObjectZ->changeObjectOrientation(QVector3D(1.57f, 0.f, 0.f));

		// Scale
		float _scale = Scene::getScene()->getCamera()->getPosition().length() / 7.f;
		mObjectX->changeObjectScale(_scale);
		mObjectY->changeObjectScale(_scale);
		mObjectZ->changeObjectScale(_scale);

		// Render
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
		mObjectX->normalizeData();
		mObjectY->normalizeData();
		mObjectZ->normalizeData();
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
	bool _isCollisionX = mObjectX->getBoundingBox().isCollision(_rayOrigin, _rayDirection, mObjectX->getModelMatrix(true), _intersection);
	bool _isCollisionY = mObjectY->getBoundingBox().isCollision(_rayOrigin, _rayDirection, mObjectY->getModelMatrix(true), _intersection);
	bool _isCollisionZ = mObjectZ->getBoundingBox().isCollision(_rayOrigin, _rayDirection, mObjectZ->getModelMatrix(true), _intersection);

	if (_isCollisionX) {
		mDirection = Direction::X;
		mObjectX->computeColors(QVector3D(1.f, 1.f, 1.f));
	}
	else if (_isCollisionY) {
		mDirection = Direction::Y;
		mObjectY->computeColors(QVector3D(1.f, 1.f, 1.f));
	}
	else if (_isCollisionZ) {
		mDirection = Direction::Z;
		mObjectZ->computeColors(QVector3D(1.f, 1.f, 1.f));
	}

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

	Camera* _camera = Scene::getScene()->getCamera();
	// matrix to project a scene vector on the screen
	QMatrix4x4 _matrix = _camera->getProjectionMatrix() * _camera->getViewMatrix();
	QVector4D _dirMouse = _matrix * QVector4D(_dir, 1.f);

	// translation of the mouse
	QVector2D _deltaMouse = fMousePosition - mInitialMousePosition;
	// translation of the mouse along the axis of the transform widget
	float _delta = QVector2D::dotProduct(_deltaMouse, QVector2D(_dirMouse.x(), _dirMouse.y()));

	if (_object != nullptr) {
		switch (mState) {
		case State::TRANSLATION:
			_delta *= _camera->getPosition().length();
			_object->moveObject(mInitialSelectedObject + _delta * _dir);
			break;

		case State::ROTATION:
			_delta *= 5.f;
			_object->changeObjectOrientation(mInitialSelectedObject + _delta * _dir);
			break;

		case State::SCALE:
			_delta *= 2.f;
			_object->changeObjectScale(mInitialSelectedObject.x() + _delta);
			break;

		default:
			break;
		}
	}
}


void TransformWidget::unselect() {
	mIsSelected = false;
	mObjectX->computeColors(QVector3D(1.f, 0.f, 0.f));
	mObjectY->computeColors(QVector3D(0.f, 1.f, 0.f));
	mObjectZ->computeColors(QVector3D(0.f, 0.f, 1.f));
}