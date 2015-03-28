#include <iostream>
#include <QApplication>
#include "Scene.hpp"
#include "Loader.hpp"
#include "Object.hpp"
#include "TransformWidget.hpp"

int main(int argc, char * argv[]){
	QApplication app(argc, argv);

    Scene::getScene()->getTransformWidget()->changeState(TransformWidget::State::TRANSLATION);

    Scene::getScene()->show();
    return app.exec();
}

