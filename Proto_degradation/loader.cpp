#include "loader.h"
#include "Mesh.h"

Loader::Loader()
{
	mModels["cube1"] = new Model("../data/cube.obj");

	// Reduce the polygon count
	Mesh _mesh(mModels["cube1"]);
	_mesh.polygonReduction(6);
	mModels["cube2"] =_mesh.convertToModel();
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
