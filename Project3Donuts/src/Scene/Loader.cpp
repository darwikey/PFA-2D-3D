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

void autoSave(){
    while(true){
		std::this_thread::sleep_for(std::chrono::seconds(10));
        Scene::getScene()->saveScene("autoSave.xml");
		std::cout << "saving done" << std::endl;
    }
}

void Loader::loadObject(const std::string& fPath, const std::string& fObjectName){
    /* When we first load an object, we start a new thread in order to activate automatic save*/
    if (Scene::getScene()->isEmptyScene())
        mAutomaticSave = new std::thread(autoSave);

	//detect file type
	// get extension
	std::string _ext = fPath.substr(fPath.find_last_of('.') + 1);

    Object* _object = new Object(fPath);

	if (_ext == "obj"){
		ObjLoader _loader(fPath);

		if (!_loader.load(_object))	{
			std::cerr << "Impossible to load the file ! Are you in the right path ?" << std::endl;
			QMessageBox::critical(0, "Error", "Error Opening File...");
			return;
		}
	}
	else if (_ext == "ply")	{
		PlyLoader _loader(fPath);

		if (!_loader.load(_object))	{
			std::cerr << "Impossible to load the file ! Are you in the right path ?" << std::endl;
			QMessageBox::critical(0, "Error", "Error Opening File...");
			return;
		}
	}
	else{
        printf("chemin %s extension %s \n", fPath.c_str(), _ext.c_str());
		QMessageBox::critical(0, "Error", "Error Opening File, extension \"" + QString(_ext.c_str()) + "\" not supported");
		return;
	}

	_object->computeColors();
	_object->normalizeData();
	Scene::getScene()->addObject(fObjectName, _object);
}
