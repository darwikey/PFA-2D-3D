#include "Loader.hpp"
#include "Object.hpp"
#include "ObjLoader.hpp"
#include "PlyLoader.hpp"
#include "Scene.hpp"


Loader::Loader(){
}

void Loader::createScene(){
}

void Loader::createScene(std::string fPath){
}

void Loader::loadObject(std::string fPath){

	//detect file type
	// get extension
	std::string _ext = fPath.substr(fPath.find_last_of('.') + 1);

	Object* _object = new Object();

	if (_ext == "obj"){
		ObjLoader _loader(fPath);

		if (!_loader.load(_object))
		{
			std::cerr << "Impossible to load the file ! Are you in the right path ?" << std::endl;
			QMessageBox::critical(0, "Error", "Error Opening File...");
		}
	}
	else if (_ext == "ply")	{
		PlyLoader _loader(fPath);

		if (!_loader.load(_object))
		{
			std::cerr << "Impossible to load the file ! Are you in the right path ?" << std::endl;
			QMessageBox::critical(0, "Error", "Error Opening File...");
		}
	}

	_object->computeColors();
	Scene::getScene()->addObject("cube1", _object);
}

void Loader::_parseOBJFile(std::string fPath){
}
void Loader::_parsePLYBinaryFile(std::string fPath){
}
void Loader::_parsePLYAsciiFile(std::string fPath){
}

