#include "Scene.hpp"
#include "Object.hpp"
#include "Loader.hpp"
#include "MainWindow.hpp"


Scene::Scene() : mLoader(new Loader()),
mWindow(new MainWindow()){
}

void Scene::addObject(Object *fObject){
}


void Scene::show(){
	
}
