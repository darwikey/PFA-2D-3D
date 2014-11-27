#include "loader.h"

Loader::Loader()
{
}

Model Loader::model = Model("dragon_vrip_res2.ply");

void Loader::setModel(string path){

    model=Model(path);
}

void Loader::show(){

    window.show();
}
