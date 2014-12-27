#include <iostream>
#include <QApplication>
#include "Scene.hpp"

using namespace std;

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    Scene::getScene()->show();
    return app.exec();
}

