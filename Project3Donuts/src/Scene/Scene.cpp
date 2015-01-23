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

	mSelectedObject = std::make_pair(std::string(), nullptr);

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


void Scene::saveScene(const std::string& fPath) {
	std::string _ext = fPath.substr(fPath.find_last_of('.') + 1);

	if (_ext != "xml") {
		std::cerr << "File must have an XML extension !" << std::endl;
		QMessageBox::critical(0, "Error", "Error with File Extension...");
	}

	// open the file and clear it
	std::ofstream _file(fPath, std::ios::out | std::ios::trunc);

	_file << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";

	//Scene definition
	_file << "<scene>\n";

	/*FOR EACH OBJECT IN SCENE*/
	for (auto _it = mObjects.begin(); _it != mObjects.end(); ++_it) {
		Object* _object = _it->second;

		_file << "\t<object type=\"";
		_file << "\" name=\"" << _it->first;
		//ADD TYPE
		_file << "\" src=\"";
		//ADD SRC
		_file << "\">\n\
\t\t<scale>\n\
\t\t\t<coordinates>\n\
\t\t\t\t<x>" << _object->getPosition().x();

		_file << "</x>\n\t\t\t\t<y>";
		_file << "</y>\n\t\t\t\t<z>";
		_file << "</z>\n\
\t\t\t</coordinates>\n\
\t\t</scale>\n\
\t\t<translation>\n\
\t\t\t<coordinates>\n\
\t\t\t\t<x>";

		_file << "</x>\n\t\t\t\t<y>";
		_file << "</y>\n\t\t\t\t<z>";
		_file << "</z>\n\
\t\t\t</coordinates>\n\
\t\t</translation>\n\
\t\t<rotation>\n\
\t\t\t<coordinates>\n\
\t\t\t\t<x>";

		_file << "</x>\n\t\t\t\t<y>";
		_file << "</y>\n\t\t\t\t<z>";
		_file << "</z>\n\
\t\t\t</coordinates>\n\
\t\t</rotation>\n\
\t</object>\n\n";

	} //END OF OBJECT CREATION LOOP


	//Camera definition
	_file << "\t<camera>\n\
\t\t<translation>\n\
\t\t\t<coordinates>\n\
\t\t\t\t<x>";


	/* How to get x,y,z coordinates of Camera ?*/

	_file << "</x>\n\t\t\t\t<y>";
	_file << "</y>\n\t\t\t\t<z>";
	_file << "</z>\n\
\t\t\t</coordinates>\n\
\t\t</translation>\n\
\t\t<rotation>\n\
\t\t\t<coordinates>\n\
\t\t\t\t<x>";

	_file << "</x>\n\t\t\t\t<y>";
	_file << "</y>\n\t\t\t\t<z>";
	_file << "</z>\n\
\t\t\t</coordinate>\n\
\t\t</rotation>\n\
\t</camera>\n\
</scene>";

	_file.close();
}
