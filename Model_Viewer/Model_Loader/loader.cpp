#include "loader.h"

Loader::Loader()
{
}

Model Loader::model = Model("cube.obj");

void Loader::setModel(string path){

    model=Model(path);
}

void Loader::show(){

    window.show();
}
