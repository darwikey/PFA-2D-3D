#include "Scene.hpp"
#include "Object.hpp"
#include "Loader.hpp"
#include "MainWindow.hpp"
#include "ui_mainwindow.h"
#include "SceneRenderer.hpp"
#include "Camera.hpp"
#include "ObjLoader.hpp"
#include "TransformWidget.hpp"
#include <QtXml/QDomDocument>
#include <QtXml/QDomNamedNodeMap>
#include <QtXml/QDomNodeList>
#include <QFile>


Scene* Scene::mSceneInstance = nullptr;


Scene::Scene() : mLoader(new Loader()),
mSceneRenderer(nullptr),
mCamera(new Camera()),
mTransformWidget(new TransformWidget),
mObjects(new std::map<std::string, Object*>()){
}


Scene* Scene::getScene() {
	if (mSceneInstance == nullptr) {
		mSceneInstance = new Scene();
		mSceneInstance->mWindow = new MainWindow();
		mSceneInstance->mSceneRenderer = mSceneInstance->mWindow->ui->widget;
	}
	return mSceneInstance;
}


void Scene::addObject(const std::string& fName, Object *fObject) {

	mObjects.load()->insert(std::pair<std::string, Object*>(fName, fObject));

	// update camera position
	mCamera->repositionCamera(getBoundingSphereRadius());
}

Object* Scene::getObject(const std::string& fName) {

	auto _model = mObjects.load()->find(fName);

	if (_model != mObjects.load()->end()) {
		return _model->second;
	}
	else {
		return nullptr;
	}
}


void Scene::show() {
	mWindow->show();
}


void Scene::render(bool fRenderOnlyObject) {
	for (auto _obj : *mObjects.load()) {
		mSceneRenderer->render(_obj.second, false);
	}

	if (!fRenderOnlyObject){
		if (mSelectedObject.second != nullptr) {
			mTransformWidget->render(mSceneRenderer, mSelectedObject.second);
		}
	}
}


void Scene::selectObjects(QVector2D fMousePosition) {
	QVector3D _rayOrigin, _rayDirection;
	mCamera->getMouseRay(fMousePosition, _rayOrigin, _rayDirection);

	mSelectedObject = std::make_pair(std::string(), nullptr);

	float _previousIntersection = 1e20f;
	for (auto it : *mObjects.load()) {
		float _intersection = 0;
		QMatrix4x4 _modelMatrix;
		_modelMatrix.translate(it.second->getPosition());

		bool _isCollision = it.second->getBoundingBox().isCollision(_rayOrigin, _rayDirection, _modelMatrix, _intersection);
		
		if (_isCollision && _intersection < _previousIntersection) {
			mSelectedObject = it;
			_previousIntersection = _intersection;
		}

		it.second->selectObject(false);
	}

	if (mSelectedObject.second != nullptr){
		mSelectedObject.second->selectObject(true);
	}
}

std::string Scene::getNameSelectedObject() {
	return mSelectedObject.first;
}


SceneRenderer* Scene::getSceneRenderer() {
	if (mSceneInstance == nullptr) {
		mSceneInstance = new Scene();
		mSceneInstance->mWindow = new MainWindow();
		mSceneInstance->mSceneRenderer = mSceneInstance->mWindow->ui->widget;
	}
	return mSceneRenderer;
}

Loader* Scene::getLoader() {
	return mLoader;
}

Camera* Scene::getCamera() {
	return mCamera;
}

TransformWidget * Scene::getTransformWidget() {
	return mTransformWidget;
}


float Scene::getBoundingSphereRadius() {
	float _radius = 0.f;

	for (auto _model : *mObjects.load()) {
		BoundingBox _bb = _model.second->getBoundingBox();
		float _r = 0.5f * _bb.mVector0.distanceToPoint(_bb.mVector1);
		_r += _model.second->getPosition().distanceToPoint(QVector3D(0.f, 0.f, 0.f)),
			_radius = std::max(_radius, _r);
	}

	return _radius;
}


bool Scene::isEmptyScene(){
	return mObjects.load()->empty();
}


void writeCoordinates(std::string &fStr, int fX, int fY, int fZ, int fTab) {
	int _i;
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("<coordinates>\n");
	for (_i = 0; _i<fTab + 1; _i++) {
		fStr.append("\t");
	}
	fStr.append("<x>");
	fStr.append(std::to_string(fX));
	fStr.append("</x>\n");
	for (_i = 0; _i<fTab + 1; _i++) {
		fStr.append("\t");
	}
	fStr.append("<y>");
	fStr.append(std::to_string(fY));
	fStr.append("</y>\n");
	for (_i = 0; _i<fTab + 1; _i++) {
		fStr.append("\t");
	}
	fStr.append("<z>");
	fStr.append(std::to_string(fZ));
	fStr.append("</z>\n");
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("</coordinates>\n");
}

void writeTranslation(std::string &fStr, int fX, int fY, int fZ, int fTab) {
	int _i;
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("<translation>\n");
	writeCoordinates(fStr, fX, fY, fZ, fTab + 1);
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("</translation>\n");
}

void writeRotation(std::string &fStr, int fX, int fY, int fZ, int fTab) {
	int _i;
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("<rotation>\n");
	writeCoordinates(fStr, fX, fY, fZ, fTab + 1);
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("</rotation>\n");
}

void writeScale(std::string &fStr, int fX, int fY, int fZ, int fTab) {
	int _i;
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("<scale>\n");
	writeCoordinates(fStr, fX, fY, fZ, fTab + 1);
	for (_i = 0; _i<fTab; _i++) {
		fStr.append("\t");
	}
	fStr.append("</scale>\n");
}

void Scene::saveScene(const std::string& fPath) {
	std::string _ext = fPath.substr(fPath.find_last_of('.') + 1);
	int _i;

	if (_ext != "xml") {
		std::cerr << "File must have an XML extension !" << std::endl;
		QMessageBox::critical(0, "Error", "Error with File Extension...");
	}

	std::string _data("<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");

	//Scene definition
	_data.append("<scene>\n");

    std::map<std::string, Object*>::iterator _it = mObjects.load()->begin();
    for (_it; _it != mObjects.load()->end(); ++_it) {
        Object* _obj = _it->second;
		QVector3D _oPosition = _obj->getPosition();
		QVector3D _oRotation = _obj->getRotation();
		QVector3D _oScale = _obj->getScale();
        _data.append("\t<object name=\"");
        _data.append(_it->first.c_str());
        _data.append("\" src=\"");
        _data.append(_obj->getPath().c_str());
        _data.append("\">\n");
		writeScale(_data, _oScale.x(), _oScale.y(), _oScale.z(), 2);
		writeTranslation(_data, _oPosition.x(), _oPosition.y(), _oPosition.z(), 2);
		writeRotation(_data, _oRotation.x(), _oRotation.y(), _oRotation.z(), 2);
		_data.append("\t</object>\n");
	}

	//Camera definition           
	QVector3D _CPosition = mCamera->getPosition();
	QVector3D _CRotation = mCamera->getRotation();

    _data.append("\t<camera angle=\"");
    _data.append(std::to_string(mCamera->getAngleOfView()));
    _data.append("\">\n");
	writeTranslation(_data, _CPosition.x(), _CPosition.y(), _CPosition.z(), 2);
	writeRotation(_data, _CRotation.x(), _CRotation.y(), _CRotation.z(), 2);
    _data.append("\t</camera>\n\
</scene>");

	std::ofstream _file(fPath, std::ios::out | std::ios::trunc);
	_file << _data;
	_file.close();
}


char* Scene::QStringToChar(QString in){
    int len = in.length();
    QChar *data = in.data();
    char *out = (char *)(calloc(len,sizeof(char)));
    int i;
    for (i=0 ; i<len ; i++,data++)
        out[i] = data->unicode();
    return out;
}

QVector3D* Scene::node_treatment(QDomNode *fcurrent){
    if (fcurrent->isNull()){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return new QVector3D(-1,-1,-1);
    }
    QDomNode _coordinates = fcurrent->namedItem("coordinates");

    if (_coordinates.namedItem("x").isNull() || _coordinates.namedItem("y").isNull() || _coordinates.namedItem("z").isNull()){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return new QVector3D(-1,-1,-1);
    }

    float a = _coordinates.namedItem("x").toElement().text().toFloat();
    float b = _coordinates.namedItem("y").toElement().text().toFloat();
    float c = _coordinates.namedItem("z").toElement().text().toFloat();
    QVector3D *_t = new QVector3D(a,b,c);

    return _t;
}

bool Scene::camera_treatment(QDomNode *fcurrent){
    printf("CAMERA\n");

    QDomNodeList _subNodes = fcurrent->childNodes();
    if (_subNodes.length() != 2){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return false;
    }

    if (!fcurrent->hasAttributes()){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return false;
    }

    //take translation
    QDomNode _translation = fcurrent->namedItem("translation");
    QVector3D *_t = node_treatment(&_translation);
    if (_t->x()==-1 && _t->y()==-1 && _t->z()==-1){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return false;
    }

    //take rotation
    QDomNode _rotation = fcurrent->namedItem("rotation");
    QVector3D *_r = node_treatment(&_rotation);
    if (_r->x()==-1 && _r->y()==-1 && _r->z()==-1){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return false;
    }

    //take angle
    QDomNamedNodeMap _attributes = fcurrent->attributes();
    if (_attributes.length() != 1){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return false;
    }
    QDomNode _att = _attributes.item(0);
    float _angle = _att.toElement().text().toFloat();

    printf("FLOAT %f\n",_angle);

    delete mCamera;
    mCamera = new Camera(*_t,*_r,_angle);

    return true;
}

bool Scene::object_treatment(QDomNode *fcurrent){
    printf("OBJECT\n");

    QDomNodeList _subNodes = fcurrent->childNodes();
    if (_subNodes.length() != 3){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return false;
    }

    //take translation
    QDomNode _translation = fcurrent->namedItem("translation");
    QVector3D *_t = node_treatment(&_translation);
    if (_t->x()==-1 && _t->y()==-1 && _t->z()==-1){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return false;
    }

    //take rotation
    QDomNode _rotation = fcurrent->namedItem("rotation");
    QVector3D *_r = node_treatment(&_rotation);
    if (_r->x()==-1 && _r->y()==-1 && _r->z()==-1){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return false;
    }

    //take scale
    QDomNode _scale = fcurrent->namedItem("scale");
    QVector3D *_s = node_treatment(&_scale);
    if (_s->x()==-1 && _s->y()==-1 && _s->z()==-1){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return false;
    }

    //take attributes
    QDomNamedNodeMap _attributes = fcurrent->attributes();
    if (_attributes.length() != 2){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return false;
    }
    QDomNode _name = _attributes.namedItem("name");
    QDomNode _src = _attributes.namedItem("src");
    if (_name.isNull() || _src.isNull()){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be used !\n");
        return false;
    }

    QString _n = _name.toAttr().value();
    QString _p = _src.toAttr().value();

    printf("nom %s source %s\n",QStringToChar(_n),QStringToChar(_p));

    Scene::getScene()->getLoader()->loadObject(QStringToChar(_n),QStringToChar(_p));
    Object *o = Scene::getScene()->getObject(_n.toStdString());
    o->moveObject(*_t,false);
    o->changeObjectScale(*_s,false);
    o->changeObjectOrientation(*_r,false);

    return true;
}

void Scene::createScene(const QString &fPath){
    QDomDocument *dom = new QDomDocument("my_xml");
    QFile xml_doc(fPath);

    //Opening file
    if(!xml_doc.open(QIODevice::ReadOnly)){
        QMessageBox::warning(0,"Error : opening file","The XML document can not be opened");
        return;
    }
    if (!dom->setContent(&xml_doc)){
        xml_doc.close();
        QMessageBox::warning(0,"Error : linking file","This XML file can not be linked with DOM document");
        return;
    }

    //Selecting first node scene
    QDomElement dom_element = dom->documentElement();
    QDomNodeList _cameraNode = dom_element.elementsByTagName("camera");
    if (_cameraNode.length() != 1){
        xml_doc.close();
        QMessageBox::warning(0,"Error : bad file","XML document for loading scene must contain one and only one instance of camera");
        return;
    }
    QDomNode _cam = _cameraNode.item(0);
    bool c = camera_treatment(&_cam);
    if (!c){
        xml_doc.close();
        QMessageBox::warning(0,"Error : bad file","XML document for loading scene must contain one and only one instance of camera");
        return;
    }
    QDomNodeList _objectsNode = dom_element.elementsByTagName("object");
    int i;
    QDomNode _current;
    bool o;
    for (i=0;i<_objectsNode.length();i++){
        _current = _objectsNode.item(i);
        o = object_treatment(&_current);
        if (!o){
            xml_doc.close();
            QMessageBox::warning(0,"Error : bad file","Error with one of the objects defined");
            return;
        }
    }

    xml_doc.close();
}
