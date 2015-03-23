#include "Loader.hpp"
#include "Object.hpp"
#include "ObjLoader.hpp"
#include "PlyLoader.hpp"
#include "Scene.hpp"
#include "Mesh.hpp"


Loader::Loader(){
    QSettings settings("settings.ini", QSettings::IniFormat);
    mTimer = new int(settings.value("General/timeautosave",60).toInt());
}

Loader::~Loader()
{
    delete mTimer;
}

void Loader::createScene(){
}

void Loader::createScene(std::string fPath){
}

void Loader::changeAutoSaveTimer(int fTimer)
{
    *mTimer = fTimer;
}

void autoSave(int * fTimer){
    while(true){
        std::this_thread::sleep_for(std::chrono::seconds(*fTimer));
        Scene::getScene()->saveScene("autoSave.xml");
    }
}

Object* Loader::loadObject(const std::string& fPath, const std::string& fObjectName){
    /* When we first load an object, we start a new thread in order to activate automatic save*/
    if (Scene::getScene()->isEmptyScene())
        mAutomaticSave = new std::thread(autoSave, mTimer);

	//detect file type
	// get extension
	std::string _ext = fPath.substr(fPath.find_last_of('.') + 1);

    Object* _object = new Object(fPath);

	if (_ext == "obj"){
		ObjLoader _loader(fPath);

		if (!_loader.load(_object))	{
			std::cerr << "Impossible to load the file ! Are you in the right path ?" << std::endl;
			QMessageBox::critical(0, "Error", "Error Opening File...");
			return nullptr;
		}
	}
	else if (_ext == "ply")	{
		PlyLoader _loader(fPath);

		if (!_loader.load(_object))	{
			std::cerr << "Impossible to load the file ! Are you in the right path ?" << std::endl;
			QMessageBox::critical(0, "Error", "Error Opening File...");
			return nullptr;
		}
	}
	else{
		QMessageBox::critical(0, "Error", "Error Opening File, extension \"" + QString(_ext.c_str()) + "\" not supported");
		return nullptr;
	}

	/*Mesh _mesh(_object);
	_mesh.polygonReduction(40000);
	Object* _newObject = _mesh.convertToModel();
	_object = _newObject;
	*/
	_object->computeColors();
	_object->normalizeData();
	Scene::getScene()->addObject(fObjectName, _object);

	return _object;
}
