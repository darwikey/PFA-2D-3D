#include "Loader.hpp"
#include "Object.hpp"
#include "ObjLoader.hpp"
#include "PlyLoader.hpp"
#include "Scene.hpp"
#include "Mesh.hpp"


Loader::Loader(){
    QSettings settings("settings.ini", QSettings::IniFormat);
    mTimer = new int(settings.value("General/timeautosave",60).toInt());
    mContinue = false;
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
    while(Scene::getScene()->getLoader()->getContinue()){
        std::this_thread::sleep_for(std::chrono::seconds(5));
        if (Scene::getScene()->getLoader()->getContinue()){
            if(!Scene::getScene()->hasName()){
                Scene::getScene()->saveScene("autoSave.xml");
            }
            else{
                std::string _path;
                std::string _name = Scene::getScene()->getName();
                _path = _name + "autoSave.xml";
                Scene::getScene()->saveScene(_path);
            }
        }
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
			QMessageBox::critical(0, "Erreur", "Erreur pendant l'ouverture du fichier...");
			return nullptr;
		}
	}
	else if (_ext == "ply")	{
		PlyLoader _loader(fPath);

		if (!_loader.load(_object))	{
			std::cerr << "Impossible to load the file ! Are you in the right path ?" << std::endl;
			QMessageBox::critical(0, "Erreur", "Erreur pendant l'ouverture du fichier...");
			return nullptr;
		}
	}
	else{
		QMessageBox::critical(0, "Error", "Erreur pendant l'ouverture du fichier, extension \"" + QString(_ext.c_str()) + "\" non supportee");
		return nullptr;
	}

    QSettings settings("settings.ini", QSettings::IniFormat);

    int _FaceNumberMax = settings.value("Viewer/FaceNumberMax",200000).toInt();

	if (_object->getFaceNumber() > _FaceNumberMax){
		// ask the user 
        int _ret;
        QMessageBox _retBox(QMessageBox::Question, QString("Project3Donut"),
			QString("Ce modele possede " + QString::number(_object->getFaceNumber()) + " polygones.\nVoulez-vous r\303\251duire le nombre de faces ?\nCela affectera juste la visualisation dans la scene et non le rendu 2D.\n"),
            QMessageBox::Yes | QMessageBox::No);
        _retBox.setButtonText(QMessageBox::Yes, "Oui");
        _retBox.setButtonText(QMessageBox::No, "Non");
        _ret = _retBox.exec();

		if (_ret == QMessageBox::Yes) {
			// Reduce the number of face
			Mesh _mesh(_object);
			_mesh.polygonReduction(_FaceNumberMax);
			Object* _newObject = _mesh.convertToModel();
			_newObject->computeColors();
			_newObject->normalizeData();

			// add a low definition model to the object
			_object->setLowModel(_newObject);
		}
	}

	_object->computeColors();
	_object->normalizeData();
	// Add the object to the scene
	Scene::getScene()->addObject(fObjectName, _object);

	return _object;
}

void Loader::stopAutoSave(){
    mContinue = false;
}

bool Loader::getContinue(){
    return mContinue;
}
