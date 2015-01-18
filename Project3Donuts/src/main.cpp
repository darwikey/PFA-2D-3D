#include <iostream>
#include <QApplication>
#include "Scene.hpp"
#include "Loader.hpp"
#include "Object.hpp"
#include "TransformWidget.hpp"


int main(int argc, char * argv[]){
    QApplication app(argc, argv);
    Scene::getScene()->getLoader()->loadObject("resources/example/cubeout.ply", "cube1");
    Scene::getScene()->getLoader()->loadObject("resources/example/monkey.obj", "monkey1");
    Scene::getScene()->getLoader()->loadObject("resources/example/monkey.obj", "monkey2");
    Scene::getScene()->getObject("cube1")->moveObject(QVector3D(0.f, 2.f, 0.f), true);
	Scene::getScene()->getObject("monkey1")->moveObject(QVector3D(2.f, 0.f, 0.f), true);
	Scene::getScene()->getObject("monkey1")->changeObjectScale(QVector3D(1.f, 2.f, 1.f));
    Scene::getScene()->getObject("monkey1")->changeObjectOrientation(QVector3D(1.f, 0.f, 0.f));

	Scene::getScene()->getTransformWidget()->changeState(TransformWidget::State::TRANSLATION);

    Scene::getScene()->show();
    return app.exec();
}

