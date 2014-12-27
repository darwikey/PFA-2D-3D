#include <iostream>
#include <QApplication>
#include "Loader.hpp"

using namespace std;

int main(int argc, char * argv[])
{
    QApplication app(argc, argv);
    Loader myWin; //Ajout de notre classe myWindow
    myWin.show();   //Exécution de notre fenêtre de rendu OpenGL
    return app.exec();
}

