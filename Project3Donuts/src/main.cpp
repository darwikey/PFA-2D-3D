#include <iostream>
#include <QApplication>
#include "Scene.hpp"
#include "Loader.hpp"
#include "Object.hpp"


int main(int argc, char * argv[]){
    QApplication app(argc, argv);
	Scene::getScene()->getLoader()->loadObject("C:/sources/3D/cubeout.ply", "cube1");
	Scene::getScene()->getLoader()->loadObject("C:/sources/3D/monkey.obj", "monkey1");
	Scene::getScene()->getLoader()->loadObject("C:/sources/3D/monkey.obj", "monkey2");
	Scene::getScene()->getObject("cube1")->moveObject(QVector3D(0.f, 2.f, 0.f));
	Scene::getScene()->getObject("monkey1")->moveObject(QVector3D(2.f, 0.f, 0.f));
	//Scene::getScene()->getObject("cube3")->moveObject(QVector3D(2.f, 0.f, 0.f));
	//Scene::getScene()->getObject("cube2")->changeObjectScale(2.f);
	
    Scene::getScene()->show();
    return app.exec();
}

