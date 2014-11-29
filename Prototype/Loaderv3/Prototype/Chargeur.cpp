#include "Chargeur.hpp"
#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include "SceneRenderer.hpp"

Chargeur::Chargeur()
{
    Scene* _scene = Scene::getInstance();
    _scene->mModels["cube1"] = new Model("B:/PFA/models/happy.ply/happy.ply");
}

void Chargeur::newModel(const std::string& fName)
{

    Scene* _scene = Scene::getInstance();
    _scene->mModels["cube1"] = new Model(fName);

}


Model* Chargeur::getModel(const std::string& fName)
{
    Scene* _scene = Scene::getInstance();
    auto _model = _scene->mModels.find(fName);

    if (_model != _scene->mModels.end()){
        return _model->second;
    }
    else{
        return nullptr;
    }
}
