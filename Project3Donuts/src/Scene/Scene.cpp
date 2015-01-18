#include "Scene.hpp"
#include "Object.hpp"
#include "Loader.hpp"
#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include "SceneRenderer.hpp"
#include "Camera.hpp"
#include "ObjLoader.hpp"
#include "TransformWidget.hpp"

Scene* Scene::mSceneInstance = nullptr;


Scene::Scene() : mLoader(new Loader()),
mSceneRenderer(nullptr),
mCamera(new Camera()),
mTransformWidget(new TransformWidget){
}


Scene* Scene::getScene(){
	if (mSceneInstance == nullptr){
		mSceneInstance = new Scene();
		mSceneInstance->mWindow = new MainWindow();
        mSceneInstance->mSceneRenderer = mSceneInstance->mWindow->ui->widget;
	}
	return mSceneInstance;
}


void Scene::addObject(const std::string& fName, Object *fObject){

	mObjects.insert(std::pair<std::string, Object*>(fName, fObject));

	// update camera position
	mCamera->repositionCamera(getBoundingSphereRadius());
}

Object* Scene::getObject(const std::string& fName){

	auto _model = mObjects.find(fName);

	if (_model != mObjects.end()){
		return _model->second;
	}
	else{
		return nullptr;
	}
}


void Scene::show(){
	mWindow->show();
}


void Scene::render(){
	for (auto _obj : mObjects){
		mSceneRenderer->render(_obj.second, false);
	}

	if (mSelectedObject.second != nullptr){
		mTransformWidget->render(mSceneRenderer, mSelectedObject.second);
	}
}


void Scene::selectObjects(QVector2D fMousePosition){
	QVector3D _rayOrigin, _rayDirection;
	mCamera->getMouseRay(fMousePosition, _rayOrigin, _rayDirection);

	for (auto it : mObjects) {
		float _intersection = 0;
		QMatrix4x4 _modelMatrix;
		_modelMatrix.translate(it.second->getPosition());
		
		bool _isCollision = it.second->getBoundingBox().isCollision(_rayOrigin, _rayDirection, _modelMatrix, _intersection);
		it.second->selectObject(_isCollision);
		if (_isCollision) {
			mSelectedObject = it;
		}
	}
}

std::string Scene::getNameSelectedObject(){
	return mSelectedObject.first;
}


SceneRenderer* Scene::getSceneRenderer(){
    if (mSceneInstance == nullptr){
        mSceneInstance = new Scene();
        mSceneInstance->mWindow = new MainWindow();
        mSceneInstance->mSceneRenderer = mSceneInstance->mWindow->ui->widget;
    }
	return mSceneRenderer;
}

Loader* Scene::getLoader(){
	return mLoader;
}

Camera* Scene::getCamera(){
	return mCamera;
}

TransformWidget * Scene::getTransformWidget(){
	return mTransformWidget;
}


float Scene::getBoundingSphereRadius(){
	float _radius = 0.f;

	for (auto _model : mObjects) {
		BoundingBox _bb = _model.second->getBoundingBox();
		float _r = 0.5f * _bb.mVector0.distanceToPoint(_bb.mVector1);
		_r += _model.second->getPosition().distanceToPoint(QVector3D(0.f, 0.f, 0.f)),
		_radius = std::max(_radius, _r);
	}

	return _radius;
}
