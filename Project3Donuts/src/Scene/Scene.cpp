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
mTransformWidget(new TransformWidget) {
}


Scene* Scene::getScene() {
	if (mSceneInstance == nullptr) {
		mSceneInstance = new Scene();
		mSceneInstance->mWindow = new MainWindow();
		mSceneInstance->mSceneRenderer = mSceneInstance->mWindow->ui->widget;
	}
	return mSceneInstance;
}


void Scene::addObject(const std::string& fName, Object *fObject) {

	mObjects.insert(std::pair<std::string, Object*>(fName, fObject));

	// update camera position
	mCamera->repositionCamera(getBoundingSphereRadius());
}

Object* Scene::getObject(const std::string& fName) {

	auto _model = mObjects.find(fName);

	if (_model != mObjects.end()) {
		return _model->second;
	}
	else {
		return nullptr;
	}
}


void Scene::show() {
	mWindow->show();
}


void Scene::render() {
	for (auto _obj : mObjects) {
		mSceneRenderer->render(_obj.second, false);
	}

	if (mSelectedObject.second != nullptr) {
		mTransformWidget->render(mSceneRenderer, mSelectedObject.second);
	}
}


void Scene::selectObjects(QVector2D fMousePosition) {
	QVector3D _rayOrigin, _rayDirection;
	mCamera->getMouseRay(fMousePosition, _rayOrigin, _rayDirection);

	mSelectedObject = std::make_pair(std::string(), nullptr);

	float _previousIntersection = 1e20f;
	for (auto it : mObjects) {
		float _intersection = 0;
		QMatrix4x4 _modelMatrix;
		_modelMatrix.translate(it.second->getPosition());

		bool _isCollision = it.second->getBoundingBox().isCollision(_rayOrigin, _rayDirection, _modelMatrix, _intersection);
		
		if (_isCollision && _intersection < _previousIntersection) {
			mSelectedObject = it;
			_previousIntersection = _intersection;
		}

		it.second->selectObject(false);
	}

	if (mSelectedObject.second != nullptr){
		mSelectedObject.second->selectObject(true);
	}
}

std::string Scene::getNameSelectedObject() {
	return mSelectedObject.first;
}


SceneRenderer* Scene::getSceneRenderer() {
	if (mSceneInstance == nullptr) {
		mSceneInstance = new Scene();
		mSceneInstance->mWindow = new MainWindow();
		mSceneInstance->mSceneRenderer = mSceneInstance->mWindow->ui->widget;
	}
	return mSceneRenderer;
}

Loader* Scene::getLoader() {
	return mLoader;
}

Camera* Scene::getCamera() {
	return mCamera;
}

TransformWidget * Scene::getTransformWidget() {
	return mTransformWidget;
}


float Scene::getBoundingSphereRadius() {
	float _radius = 0.f;

	for (auto _model : mObjects) {
		BoundingBox _bb = _model.second->getBoundingBox();
		float _r = 0.5f * _bb.mVector0.distanceToPoint(_bb.mVector1);
		_r += _model.second->getPosition().distanceToPoint(QVector3D(0.f, 0.f, 0.f)),
			_radius = std::max(_radius, _r);
	}

	return _radius;
}

void writeCoordinates(std::string &fStr, int fX, int fY, int fZ, int fTab) {
	int _i;
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("<coordinates>\n");
	for (_i = 0; _i<fTab + 1; _i++) {
		fStr.append("\t");
	}
	fStr.append("<x>");
	fStr.append(std::to_string(fX));
	fStr.append("</x>\n");
	for (_i = 0; _i<fTab + 1; _i++) {
		fStr.append("\t");
	}
	fStr.append("<y>");
	fStr.append(std::to_string(fY));
	fStr.append("</y>\n");
	for (_i = 0; _i<fTab + 1; _i++) {
		fStr.append("\t");
	}
	fStr.append("<z>");
	fStr.append(std::to_string(fZ));
	fStr.append("</z>\n");
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("</coordinates>\n");
}

void writeTranslation(std::string &fStr, int fX, int fY, int fZ, int fTab) {
	int _i;
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("<translation>\n");
	writeCoordinates(fStr, fX, fY, fZ, fTab + 1);
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("</translation>\n");
}

void writeRotation(std::string &fStr, int fX, int fY, int fZ, int fTab) {
	int _i;
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("<rotation>\n");
	writeCoordinates(fStr, fX, fY, fZ, fTab + 1);
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("</rotation>\n");
}

void writeScale(std::string &fStr, int fX, int fY, int fZ, int fTab) {
	int _i;
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("<scale>\n");
	writeCoordinates(fStr, fX, fY, fZ, fTab + 1);
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("</scale>\n");
}

void Scene::saveScene(const std::string& fPath) {
	std::string _ext = fPath.substr(fPath.find_last_of('.') + 1);
	int _i;

	if (_ext != "xml") {
		std::cerr << "File must have an XML extension !" << std::endl;
		QMessageBox::critical(0, "Error", "Error with File Extension...");
	}

	std::string _data("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");

	//Scene definition
	_data.append("<scene>\n");

	std::map<std::string, Object*>::iterator it = mObjects.begin();
	for (it; it != mObjects.end(); ++it) {
		Object* _obj = it->second;
		QVector3D _oPosition = _obj->getPosition();
		QVector3D _oRotation = _obj->getRotation();
		QVector3D _oScale = _obj->getScale();
		_data.append("\t<object type=\"");
		//ADD TYPE
		_data.append("\" src=\"");
		//ADD SRC
		writeScale(_data, _oScale.x(), _oScale.y(), _oScale.z(), 2);
		writeTranslation(_data, _oPosition.x(), _oPosition.y(), _oPosition.z(), 2);
		writeRotation(_data, _oRotation.x(), _oRotation.y(), _oRotation.z(), 2);
		_data.append("\t</object>\n");
	}

	//Camera definition           
	QVector3D _CPosition = mCamera->getPosition();
	QVector3D _CRotation = mCamera->getRotation();

	_data.append("\t<camera>\n");
	writeTranslation(_data, _CPosition.x(), _CPosition.y(), _CPosition.z(), 2);
	writeRotation(_data, _CRotation.x(), _CRotation.y(), _CRotation.z(), 2);
	_data.append("\t</camera>\n\
</scene>");

	std::ofstream _file(fPath, std::ios::out | std::ios::trunc);
	_file << _data;
	_file.close();
}