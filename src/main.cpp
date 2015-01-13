#include <iostream>
#include <QApplication>
#include "Scene.hpp"
#include "Loader.hpp"


int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
	Scene::getScene()->getLoader()->loadObject("C:/sources/3D/cubeout.ply");
    Scene::getScene()->show();
    return app.exec();
}

