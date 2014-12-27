#include "Loader.hpp"
#include "Object.hpp"
#include "ObjLoader.hpp"
#include "PlyAsciiLoader.hpp"
#include "Scene.hpp"


Loader::Loader(){
}

void Loader::createScene(){
}

void Loader::createScene(std::string fPath){
}

void Loader::loadObject(std::string fPath){

	//TODO detect file type

	Object* _object = new Object();
	ObjLoader _loader(fPath);

	if (!_loader.load(_object))
	{
		std::cerr << "Impossible to open the file ! Are you in the right path ?" << std::endl;
		QMessageBox::critical(0, "Error", "Error Opening File...");
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

