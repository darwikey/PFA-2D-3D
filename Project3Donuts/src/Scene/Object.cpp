#include "Object.hpp"
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include "SceneRenderer.hpp"
#include "Scene.hpp"
#include "Camera.hpp"


Object::Object() : mPosition(0.f, 0.f, 0.f), 
mRotation(0.f, 0.f, 0.f),
mScale(1.f, 1.f, 1.f){
}


void Object::moveObject(QVector3D fPosition, bool fUpdateCamera){
	mPosition = fPosition;

	// update camera position
	if (fUpdateCamera){
		Scene* _scene = Scene::getScene();
		_scene->getCamera()->repositionCamera(_scene->getBoundingSphereRadius());
	}
}


void Object::changeObjectScale(float fScale, bool fUpdateCamera){
	mScale = QVector3D(fScale, fScale, fScale);

	// update bounding box
	computeBoundingBox();

	// update camera position
	if (fUpdateCamera) {
		Scene* _scene = Scene::getScene();
		_scene->getCamera()->repositionCamera(_scene->getBoundingSphereRadius());
	}
}


void Object::changeObjectScale(QVector3D fScale, bool fUpdateCamera) {
	mScale = fScale;

	// update bounding box
	computeBoundingBox();

	// update camera position
	if (fUpdateCamera) {
		Scene* _scene = Scene::getScene();
		_scene->getCamera()->repositionCamera(_scene->getBoundingSphereRadius());
	}
}


void Object::changeObjectOrientation(QVector3D fRotation, bool fUpdateCamera){
	mRotation = fRotation;

	// update camera position
	if (fUpdateCamera) {
		Scene* _scene = Scene::getScene();
		_scene->getCamera()->repositionCamera(_scene->getBoundingSphereRadius());
	}
}


void Object::draw(SceneRenderer* fRenderer){
    Camera* _camera = Scene::getScene()->getCamera();
	const QMatrix4x4 _ViewProjMatrix = _camera->getViewMatrix() * getModelMatrix();

	for (auto _indice = mIndices.begin(); _indice != mIndices.end(); ) {
		for (uint i = 0; i < 3 && _indice != mIndices.end(); i++) {
			if (1) {//TODO check
				//Normal
				if (i == 0) {
					QVector3D _n = mNormals[*_indice];
                    //glNormal3f(_n.x(), _n.y(), _n.z());
				}

				//Color
				QVector3D _c = mColor[*_indice];
				if (mIsSelected) {
					_c += QVector3D(0.2f, 0.1f, -0.1f);
				}
                //glColor3f(_c.x(), _c.y(), _c.z());

				// Vertex position
				QVector3D _v = _ViewProjMatrix * mVertices[*_indice];
                //glVertex3f(_v.x(), _v.y(), _v.z());
			}
			++_indice;
		}
	}
}


void Object::computeBoundingBox(){
	for (QVector3D _v : mVertices) {
		mBoundingBox.mVector0.setX((_v.x() < mBoundingBox.mVector0.x()) ? _v.x() : mBoundingBox.mVector0.x());
		mBoundingBox.mVector1.setX((mBoundingBox.mVector1.x() < _v.x()) ? _v.x() : mBoundingBox.mVector1.x());
		mBoundingBox.mVector0.setY((_v.y() < mBoundingBox.mVector0.y()) ? _v.y() : mBoundingBox.mVector0.y());
		mBoundingBox.mVector1.setY((mBoundingBox.mVector1.y() < _v.y()) ? _v.y() : mBoundingBox.mVector1.y());
		mBoundingBox.mVector0.setZ((_v.z() < mBoundingBox.mVector0.z()) ? _v.z() : mBoundingBox.mVector0.z());
		mBoundingBox.mVector1.setZ((mBoundingBox.mVector1.z() < _v.z()) ? _v.z() : mBoundingBox.mVector1.z());
	}
	mBoundingBox.mVector0 *= mScale;
	mBoundingBox.mVector1 *= mScale;
}


void Object::computeColors(QVector3D fColor) {
	if (!mVertices.empty() && !mIndices.empty()) {
		mColor.clear();
		for (unsigned int i = 0; i < mVertices.size(); i++) {
			mColor.push_back(fColor);
		}
	}
}

void Object::computeNormals(){
	mNormals.clear();
	// each 3 vertices we have a triangle
	for (size_t i = 0; i < mIndices.size(); i += 3){
		if (i + 2 < mIndices.size()){
			uint _indice0 = mIndices[i];
			uint _indice1 = mIndices[i + 1];
			uint _indice2 = mIndices[i + 2];

			if (_indice0 < mVertices.size() && _indice1 < mVertices.size() && _indice2 < mVertices.size()){
				QVector3D _normal = QVector3D::crossProduct(mVertices[_indice1] - mVertices[_indice0], mVertices[_indice2] - mVertices[_indice0]);
				_normal.normalize();

				uint _maxIndices = std::max(std::max(_indice0, _indice1), _indice2);
				if (_maxIndices >= mNormals.size()) {
					mNormals.resize(_maxIndices + 1);
				}

				// one normal for each vertex
				mNormals[_indice0] = _normal;
				mNormals[_indice1] = _normal;
				mNormals[_indice2] = _normal;
			}
		}
	}
}


void Object::selectObject(bool fIsSelected) {
	mIsSelected = fIsSelected;
}

bool Object::isObjectSelected() {
	return mIsSelected;
}

BoundingBox Object::getBoundingBox(){
	return mBoundingBox;
}

QVector3D Object::getPosition() {
	return mPosition;
}

QVector3D Object::getRotation() {
	return mRotation;
}

QVector3D Object::getScale() {
	return mScale;
}


QMatrix4x4 Object::getModelMatrix()
{
	QMatrix4x4 _modelMatrix;
	_modelMatrix.translate(mPosition);
	const float _radTodeg = 57.29578f;
	_modelMatrix.rotate(_radTodeg * mRotation.x(), QVector3D(1.f, 0.f, 0.f));
	_modelMatrix.rotate(_radTodeg * mRotation.y(), QVector3D(0.f, 1.f, 0.f));
	_modelMatrix.rotate(_radTodeg * mRotation.z(), QVector3D(0.f, 0.f, 1.f));
	_modelMatrix.scale(mScale);

	return _modelMatrix;
}


void Object::pushVertice(QVector3D fValue){
	mVertices.push_back(fValue);
}

void Object::pushNormal(QVector3D fValue){
	mNormals.push_back(fValue);
}

void Object::pushIndice(uint fValue){
	mIndices.push_back(fValue);
}

void Object::pushColor(QVector3D fValue){
	mColor.push_back(fValue);
}

void Object::pushTextureCoordinate(QVector2D fValue){
	mTextureCoordinates.push_back(fValue);
}
