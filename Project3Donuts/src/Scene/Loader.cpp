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
		}
	}
	else if (_ext == "ply")	{
		PlyLoader _loader(fPath);

		if (!_loader.load(_object))	{
			std::cerr << "Impossible to load the file ! Are you in the right path ?" << std::endl;
			QMessageBox::critical(0, "Error", "Error Opening File...");
		}
	}

	_object->computeColors();
	_object->computeNormals();
	Scene::getScene()->addObject(fObjectName, _object);
}

void Loader::saveScene(const std::string& fPath){
    std::string _ext = fPath.substr(fPath.find_last_of('.') + 1);

    if (_ext != "xml"){
        std::cerr << "File must have an XML extension !" << std::endl;
        QMessageBox::critical(0, "Error", "Error with File Extension...");
    }

    std::string *data = new std::string("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");

    //Scene definition
    data->append("<scene>\n");

    /*FOR EACH OBJECT IN SCENE*/
    data->append("\t<object type=\"");
    //ADD TYPE
    data->append("\" src=\"");
    //ADD SRC
    data->append("\">\n\
\t\t<scale>\n\
\t\t\t<coordinates>\n\
\t\t\t\t<x>");



/* How to get x,y,z coordinates of Camera ?*/



    data->append("</x>\n\t\t\t\t<y>");
    data->append("</y>\n\t\t\t\t<z>");
    data->append("</z>\n\
\t\t\t</coordinates>\n\
\t\t</scale>\n\
\t\t<translation>\n\
\t\t\t<coordinates>\n\
\t\t\t\t<x>");



/* How to get x,y,z coordinates of Camera ?*/



    data->append("</x>\n\t\t\t\t<y>");
    data->append("</y>\n\t\t\t\t<z>");
    data->append("</z>\n\
\t\t\t</coordinates>\n\
\t\t</translation>\n\
\t\t<rotation>\n\
\t\t\t<coordinates>\n\
\t\t\t\t<x>");



/* How to get x,y,z coordinates of Camera ?*/



    data->append("</x>\n\t\t\t\t<y>");
    data->append("</y>\n\t\t\t\t<z>");
    data->append("</z>\n\
\t\t\t</coordinates>\n\
\t\t</rotation>\n\
\t</object>\n\n");


    /*END OF OBJECT CREATION LOOP*/



    //Camera definition
    data->append("\t<camera>\n\
\t\t<translation>\n\
\t\t\t<coordinates>\n\
\t\t\t\t<x>");



             /* How to get x,y,z coordinates of Camera ?*/



    data->append("</x>\n\t\t\t\t<y>");
    data->append("</y>\n\t\t\t\t<z>");
    data->append("</z>\n\
\t\t\t</coordinates>\n\
\t\t</translation>\n\
\t\t<rotation>\n\
\t\t\t<coordinates>\n\
\t\t\t\t<x>");



/* How to get x,y,z coordinates of Camera ?*/



    data->append("</x>\n\t\t\t\t<y>");
    data->append("</y>\n\t\t\t\t<z>");
    data->append("</z>\n\
\t\t\t</coordinate>\n\
\t\t</rotation>\n\
\t</camera>\n\
</scene>");

    FILE *f = fopen(fPath.c_str(), "w");
    fprintf(f,data->c_str());
    fclose(f);
    return;
}
