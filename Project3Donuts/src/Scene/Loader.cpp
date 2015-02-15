#include "Loader.hpp"
#include "Object.hpp"
#include "ObjLoader.hpp"
#include "PlyLoader.hpp"
#include "Scene.hpp"
#include <QtXmlPatterns/QXmlQuery>
#include <QApplication>
#include <QString>
#include <QVariant>
#include <QStringList>
#include <QStringBuilder>

Loader::Loader(){
}

void Loader::createScene(){
}

void Loader::createScene(std::string fPath){
/*    QApplication app(fPath);
    QXmlQuery query;
    QStringList results;

    QString path = app.arguments()[0];
    query.bindVariable("path", QXmlItem(QVariant(url)));

    query.setQuery("declare variable $path external;\
                      select camera from doc({$path})");
    if (query.isValid()){
        if (query.evaluateTo(&results)) {
            foreach (const QString &result, results)
                  std::cout << qPrintable(result) << std::endl;
        }
    } */
}

void Loader::loadObject(const std::string& fPath, const std::string& fObjectName){

	//detect file type
	// get extension
	std::string _ext = fPath.substr(fPath.find_last_of('.') + 1);

	Object* _object = new Object();

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
		QMessageBox::critical(0, "Error", "Error Opening File, extension \"" + QString(_ext.c_str()) + "\" not supported");
		return;
	}

	_object->computeColors();
	_object->normalizeData();
	Scene::getScene()->addObject(fObjectName, _object);
}

