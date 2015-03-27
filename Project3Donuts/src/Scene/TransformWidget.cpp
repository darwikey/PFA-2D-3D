#include "TransformWidget.hpp"
#include "ObjLoader.hpp"
#include "SceneRenderer.hpp"
#include "Object.hpp"
#include "Scene.hpp"
#include "Camera.hpp"


TransformWidget::TransformWidget(std::string fObjPath) : mObjPath(fObjPath){
}

TransformWidget::~TransformWidget(){
}

void TransformWidget::render(SceneRenderer* fRenderer, Camera* fCamera){
    if (mState != TransformWidget::State::HIDE
        && mObjectX != nullptr){
        //Translation
		QVector3D _pos(0.f, 0.f, 0.f);// = fCamera->getPosition();

        mObjectX->moveObject(_pos);
        mObjectY->moveObject(_pos);
        mObjectZ->moveObject(_pos);

        //Orientation
        mObjectX->changeObjectOrientation(QVector3D(0.f, 0.f, -1.57f));
        mObjectZ->changeObjectOrientation(QVector3D(1.57f, 0.f, 0.f));

        // Scale
		float _scale =  fCamera->getPosition().length();
        mObjectX->changeObjectScale(_scale/20);
        mObjectY->changeObjectScale(_scale/20);
        mObjectZ->changeObjectScale(_scale/20);

        // Render
        fRenderer->render(mObjectX, fCamera, true);
        fRenderer->render(mObjectY, fCamera, true);
        fRenderer->render(mObjectZ, fCamera, true);
    }
}

void TransformWidget::render(SceneRenderer* fRenderer, Camera* fCamera, Object* fSelectedObject){
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
        float _scale = fCamera->getPosition().length() / 14.f;
        mObjectX->changeObjectScale(_scale);
        mObjectY->changeObjectScale(_scale);
        mObjectZ->changeObjectScale(_scale);

        // Render
        fRenderer->render(mObjectX, fCamera, true);
        fRenderer->render(mObjectY, fCamera, true);
        fRenderer->render(mObjectZ, fCamera, true);
    }
}

void TransformWidget::changeState(TransformWidget::State fState) {
    // Load the widget model
    if (mObjectX == nullptr) {
        mObjectX = new Object();
        mObjectY = new Object();
        mObjectZ = new Object();

		ObjLoader _loaderX(mObjPath);
		ObjLoader _loaderY(mObjPath);
		ObjLoader _loaderZ(mObjPath);

        if (!_loaderX.load(mObjectX)
            || !_loaderY.load(mObjectY)
            || !_loaderZ.load(mObjectZ)){
            QMessageBox::critical(0, "Error", "Error opening " + QString(mObjPath.c_str()));
        }

        mObjectX->computeColors();
        mObjectY->computeColors();
        mObjectZ->computeColors();

        mObjectX->normalizeData();
        mObjectY->normalizeData();
        mObjectZ->normalizeData();

        mObjectX->setGlobalColor(QVector3D(1.f, 0.f, 0.f));
        mObjectY->setGlobalColor(QVector3D(0.f, 1.f, 0.f));
        mObjectZ->setGlobalColor(QVector3D(0.f, 0.f, 1.f));
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
		mObjectX->setGlobalColor(QVector3D(1.f, 1.f, 1.f));
	}
	else if (_isCollisionY) {
		mDirection = Direction::Y;
		mObjectY->setGlobalColor(QVector3D(1.f, 1.f, 1.f));
	}
	else if (_isCollisionZ) {
		mDirection = Direction::Z;
		mObjectZ->setGlobalColor(QVector3D(1.f, 1.f, 1.f));
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


	Camera* _camera = Scene::getScene()->getCamera();
	// matrix to project a scene vector on the screen
	QMatrix4x4 _matrix = _camera->getProjectionMatrix() * _camera->getViewMatrix();
	QVector4D _dirMouse = _matrix * QVector4D(getDirection(mDirection), 1.f);

	// translation of the mouse
	QVector2D _deltaMouse = fMousePosition - mInitialMousePosition;
	
	// translation of the mouse along the axis of the transform widget
	float _delta = 0.f;
	
	if (mState == State::ROTATION){
		_delta = QVector2D::dotProduct(_deltaMouse, QVector2D(_dirMouse.y(), _dirMouse.x()));
	}
	else{
		_delta = QVector2D::dotProduct(_deltaMouse, QVector2D(_dirMouse.x(), _dirMouse.y()));
	}

	if (mState == State::TRANSLATION){
		_delta *= _camera->getPosition().length();
	}

	applyTransformation(_object, mInitialSelectedObject, mState, mDirection, _delta);
}


void TransformWidget::unselect() {
	mIsSelected = false;
	// change the widget colors
	if (mObjectX != nullptr){
		mObjectX->setGlobalColor(QVector3D(1.f, 0.f, 0.f));
		mObjectY->setGlobalColor(QVector3D(0.f, 1.f, 0.f));
		mObjectZ->setGlobalColor(QVector3D(0.f, 0.f, 1.f));
	}

	Object* _object = Scene::getScene()->getObject(mNameSelectedObject);
	
	if (_object != nullptr){
		QVector3D _init = mInitialSelectedObject;
		Direction _dir = mDirection;
		State _state = mState;

		std::function<void()> _action = [this, _object, _init, _state, _dir](){
			this->applyTransformation(_object, _init, _state, _dir, 0.f);
		};

		Scene::getScene()->registerAction(_action);
	}
}


QVector3D TransformWidget::getDirection(Direction fDirection) const{
	QVector3D _dir;

	switch (fDirection) {
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

	return _dir;
}


void TransformWidget::applyTransformation(Object* fObject, QVector3D fInitialSelectedObject, State fState, Direction fDirection, float fDelta) const{
    if (fObject != nullptr) {
		switch (fState) {
		case State::TRANSLATION:
			fObject->moveObject(fInitialSelectedObject + fDelta * getDirection(fDirection));
			break;

		case State::ROTATION:
			fObject->changeObjectOrientation(fInitialSelectedObject + 5.f * fDelta * getDirection(fDirection));
			break;

		case State::SCALE:
			fObject->changeObjectScale(fInitialSelectedObject.x() + 2.f * fDelta);
			break;

		default:
			break;
		}
	}
}
