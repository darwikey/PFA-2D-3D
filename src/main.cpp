#include <iostream>
#include <QApplication>
#include "Scene.hpp"

using namespace std;

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    Scene _scene;
    _scene.show();
    return app.exec();
}

