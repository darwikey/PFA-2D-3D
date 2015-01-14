#include "Scene.hpp"
#include "Object.hpp"
#include "Loader.hpp"
#include "MainWindow.hpp"
#include "SceneRenderer.hpp"
#include "Camera.hpp"

Scene* Scene::mSceneInstance = nullptr;


Scene::Scene() : mLoader(new Loader()),
mSceneRenderer(new SceneRenderer()),
mCamera(new Camera()),
mWindow(nullptr){
}


Scene* Scene::getScene(){
	if (mSceneInstance == nullptr){
		mSceneInstance = new Scene();
		mSceneInstance->mWindow = new MainWindow();
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


void Scene::render(){
	for (auto _obj : mObjects){
		mSceneRenderer->render(_obj.second);
	}
}


SceneRenderer* Scene::getSceneRenderer(){
	return mSceneRenderer;
}

Loader* Scene::getLoader(){
	return mLoader;
}

Camera* Scene::getCamera(){
	return mCamera;
}