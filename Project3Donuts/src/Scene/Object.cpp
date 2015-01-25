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
mScale(1.f, 1.f, 1.f),
mIndexbuffer(QOpenGLBuffer::IndexBuffer){

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


void Object::initVbo(SceneRenderer* fRenderer)
{
    mVAO.create();
    mVAO.bind();

    // Create a buffer and Fill it the the vertex data
    mVertexbuffer.create();
    mVertexbuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mVertexbuffer.bind();
    mVertexbuffer.allocate(mVertices.data(), mVertices.size() * sizeof(QVector3D));

    // Create a buffer and Fill it the the color data
    mColorbuffer.create();
    mColorbuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mColorbuffer.bind();
    mColorbuffer.allocate(mColor.data(), mColor.size() * sizeof(QVector3D));

    // Create a buffer and Fill it the the index data
    mIndexbuffer.create();
    mIndexbuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    mIndexbuffer.bind();
    mIndexbuffer.allocate(mIndices.data(), mIndices.size() * sizeof(uint));

	// Create a buffer and Fill it the the normal data
	mNormalBuffer.create();
	mNormalBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
	mNormalBuffer.bind();
	mNormalBuffer.allocate(mNormals.data(), mNormals.size() * sizeof(QVector3D));

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
        0,                  // attribute (use in the shader)
        GL_FLOAT,           // type
        0,                  // offset
        3					// size of one element
        );

    // 2nd attribute buffer : colors
    mShader->enableAttributeArray(1);
    mColorbuffer.bind();
    mShader->setAttributeBuffer(1, GL_FLOAT, 0, 3);

	// 3rd attribute buffer : normals
	mShader->enableAttributeArray(2);
	mNormalBuffer.bind();
	mShader->setAttributeBuffer(2, GL_FLOAT, 0, 3);
}

void Object::initShader(SceneRenderer* fRenderer) {
/*    QGLContext *context = fRenderer->context();
    if (!context){
        QMessageBox::critical(0, "Error", "Context Error");
      exit(EXIT_FAILURE);
    }
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

	mShader->link();*/
}

void Object::draw(SceneRenderer* fRenderer)
{
//    mElementbuffer.bind();
    /*mVAO.bind();
	// Draw the triangles !
	fRenderer->glDrawElements(
		GL_TRIANGLES,      // mode
		mIndices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*) 0           // element array buffer offset
		);*/

	for (auto _indice : mIndices)
	{

		if (1){//TODO check
			QVector3D _v = getModelMatrix() * mVertices[_indice];
			glVertex3f(_v.x(), _v.y(), _v.z());
			QVector3D _c = mColor[_indice];
			glColor3f(_c.x(), _c.y(), _c.z());
	
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

bool Object::isVboInitialized(){
	return mIsVboInitialized;
}

QOpenGLShaderProgram * Object::getShader(){
	return mShader;
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
