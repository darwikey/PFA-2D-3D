#include "Object.hpp"
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include "SceneRenderer.hpp"
#include "Scene.hpp"
#include "Camera.hpp"



Object::Object() : mPosition(0.f, 0.f, 0.f), 
mRotation(0.f, 0.f, 0.f),
mElementbuffer(QOpenGLBuffer::IndexBuffer){

}


void Object::moveObject(QVector3D fPosition){
	mPosition = fPosition;

	// update camera position
	Scene* _scene = Scene::getScene();
	_scene->getCamera()->repositionCamera(_scene->getBoundingSphereRadius());
}


void Object::changeObjectScale(float fScale){
	mScale = fScale;

	// update bounding box
	computeBoundingBox();

	// update camera position
	Scene* _scene = Scene::getScene();
	_scene->getCamera()->repositionCamera(_scene->getBoundingSphereRadius());
}


void Object::changeObjectOrientation(float fHorizontalAngle, float fVerticalAngle){
	//TODO

	// update camera position
	Scene* _scene = Scene::getScene();
	_scene->getCamera()->repositionCamera(_scene->getBoundingSphereRadius());
}


void Object::initVbo(SceneRenderer* fRenderer)
{
    mVAO.create();
    mVAO.bind();

    // Create a buffer and Fill it the the vertex data

    mVertexbuffer.create();
    mVertexbuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mVertexbuffer.bind();
    mVertexbuffer.allocate(mVertices.data(), mVertices.size()*sizeof(QVector3D));

    // Create a buffer and Fill it the the color data

    mColorbuffer.create();
    mColorbuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mColorbuffer.bind();
    mColorbuffer.allocate(mColor.data(), mColor.size()*sizeof(QVector3D));

    // Create a buffer and Fill it the the index data

    mElementbuffer.create();
    mElementbuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mElementbuffer.bind();
    mElementbuffer.allocate(mIndices.data(), mIndices.size() * sizeof(uint));

	initShader(fRenderer);
    initAttributes(fRenderer);
	mIsVboInitialized = true;
}

void Object::initAttributes(SceneRenderer* fRenderer)
{
    mVAO.bind();
    mShader->bind();
    mShader->enableAttributeArray(0);
    // Index buffer
    mVertexbuffer.bind();

    mShader->setAttributeBuffer(
        0,                  // attribute
        GL_FLOAT,           // type
        0,                  // stride
        3            // array buffer offset
        );

    // 2nd attribute buffer : colors
    mShader->enableAttributeArray(1);
    mColorbuffer.bind();
    mShader->setAttributeBuffer(
        1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
        GL_FLOAT,                         // type
        0,                                // stride
        3                          // array buffer offset
        );
}

void Object::initShader(SceneRenderer* fRenderer) {
	mShader = new QOpenGLShaderProgram(fRenderer);

	QString _shaderPath = "resources/shaders/StandardShading.vertexshader";
	if (!mShader->addShaderFromSourceFile(QOpenGLShader::Vertex, _shaderPath)) {
		QMessageBox::critical(0, "Error", "Error loading shader " + _shaderPath);
		exit(EXIT_FAILURE);
	}

	_shaderPath = "resources/shaders/StandardShading.fragmentshader";
	if (!mShader->addShaderFromSourceFile(QOpenGLShader::Fragment, _shaderPath)) {
		QMessageBox::critical(0, "Error", "Error loading shader " + _shaderPath);
		exit(EXIT_FAILURE);
	}


	qDebug() << mShader->log();

	mShader->link();
}

void Object::draw(SceneRenderer* fRenderer)
{
//    mElementbuffer.bind();
    mVAO.bind();
	// Draw the triangles !
	fRenderer->glDrawElements(
		GL_TRIANGLES,      // mode
		mIndices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*) 0           // element array buffer offset
		);

//    mShader->disableAttributeArray(0);
//    mShader->disableAttributeArray(0);
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


void Object::computeColors(){
	if (!mVertices.empty() && !mIndices.empty()){
		mColor.clear();
		for (unsigned int i = 0; i < mVertices.size(); i++)
		{
			GLfloat _f = (GLfloat) i / mVertices.size();
			QVector3D _ColorMod (_f, _f, _f);
			mColor.push_back(_ColorMod);
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

float Object::getScale() {
	return mScale;
}

bool Object::isVboInitialized(){
	return mIsVboInitialized;
}

QOpenGLShaderProgram * Object::getShader(){
	return mShader;
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
