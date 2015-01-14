#include <iostream>
#include <QApplication>
#include "Scene.hpp"
#include "Loader.hpp"
#include "Object.hpp"


int main(int argc, char * argv[]){
    QApplication app(argc, argv);
	Scene::getScene()->getLoader()->loadObject("C:/sources/3D/cubeout.ply", "cube1");
	Scene::getScene()->getLoader()->loadObject("C:/sources/3D/cubeout.ply", "cube2");
	Scene::getScene()->getObject("cube1")->moveObject(QVector3D(1.f, 0.5f, 0.5f));
    Scene::getScene()->show();
    return app.exec();
}

