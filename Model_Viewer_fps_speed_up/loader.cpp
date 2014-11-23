#include "loader.h"

Loader::Loader()
{
    mModels["cube1"] = new Model("bunny.ply");
}


Model* Loader::getModel(const std::string& fName)
{
	auto _model = mModels.find(fName);

	if (_model != mModels.end()){
		return _model->second;
	}
	else{
		return nullptr;
	}
}

void Loader::show(){

    mWindow.show();
}
