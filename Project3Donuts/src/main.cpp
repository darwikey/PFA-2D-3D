#include <iostream>
#include <QApplication>
#include "Scene.hpp"
#include "Loader.hpp"
#include "Object.hpp"
#include "TransformWidget.hpp"

int main(int argc, char * argv[]){
	QApplication app(argc, argv);

    Scene::getScene()->createScene("resources/example/maScene.xml");

    /*Scene::getScene()->getLoader()->loadObject("resources/example/donut.obj", "donut1");
	Scene::getScene()->getLoader()->loadObject("resources/example/donut.obj", "donut2");*/

    Scene::getScene()->getTransformWidget()->changeState(TransformWidget::State::TRANSLATION);

    //Scene::getScene()->saveScene("maScene.xml");

    Scene::getScene()->show();
    return app.exec();
}

