#include "Scene.hpp"
#include "Object.hpp"
#include "Loader.hpp"
#include "MainWindow.hpp"

Scene* Scene::mSceneInstance = nullptr;


Scene::Scene() : mLoader(new Loader()),
mWindow(new MainWindow()){
}


Scene* Scene::getScene(){
	if (mSceneInstance == nullptr){
		mSceneInstance = new Scene();
	}
	return mSceneInstance;
}


void Scene::addObject(const std::string fName, Object *fObject){

	mObjects.insert(std::pair<std::string, Object*>(fName, fObject));
}

Object* Scene::getObject(const std::string& fName){

	auto _model = mObjects.find(fName);

	if (_model != mObjects.end())
	{
		return _model->second;
	}
	else
	{
		return nullptr;
	}
}

void Scene::show(){
	mWindow->show();
}


Loader* Scene::getLoader(){
	return mLoader;
}