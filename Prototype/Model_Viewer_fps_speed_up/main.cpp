#include <iostream>
#include <QApplication>

#include "Loader.h"

using namespace std;

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);

	//Exécution de notre fenêtre de rendu OpenGL
    Loader::getInstance()->show(); 
    return app.exec();
}

