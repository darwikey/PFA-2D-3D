#include "Object.hpp"
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include "SceneRenderer.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

Object::Shader Object::mActiveShader = Object::Shader::STANDARD_SHADING;

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


void Object::initVbo(SceneRenderer* fRenderer)
{
	if (!mVAO.isCreated()){
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
		/*mIndexbuffer.create();
		mIndexbuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
		mIndexbuffer.bind();
		mIndexbuffer.allocate(mIndices.data(), mIndices.size() * sizeof(uint));*/

		// Create a buffer and Fill it the the normal data
		mNormalBuffer.create();
		mNormalBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
		mNormalBuffer.bind();
		mNormalBuffer.allocate(mNormals.data(), mNormals.size() * sizeof(QVector3D));
	
		initShader(fRenderer);
		
		mVAO.release();
	}
    
	mIsVboInitialized = true;
}

void Object::bindAttributes(SceneRenderer* fRenderer)
{
	// first attribute buffer : vertex positions
	int _positionHandle = mShaders[mActiveShader]->attributeLocation("vertexPosition");
	mShaders[mActiveShader]->enableAttributeArray(_positionHandle);
	mVertexbuffer.bind();
	mShaders[mActiveShader]->setAttributeBuffer(_positionHandle, GL_FLOAT, 0, 3);

    // 2nd attribute buffer : colors
	_positionHandle = mShaders[mActiveShader]->attributeLocation("vertexColor");
	mShaders[mActiveShader]->enableAttributeArray(_positionHandle);
    mColorbuffer.bind();
	mShaders[mActiveShader]->setAttributeBuffer(_positionHandle, GL_FLOAT, 0, 3);

	// 3rd attribute buffer : normals
	_positionHandle = mShaders[mActiveShader]->attributeLocation("vertexNormal");
	mShaders[mActiveShader]->enableAttributeArray(_positionHandle);
	mNormalBuffer.bind();
	mShaders[mActiveShader]->setAttributeBuffer(_positionHandle, GL_FLOAT, 0, 3);
}


void Object::releaseAttributes(SceneRenderer* fRenderer)
{
	// first attribute buffer : vertex positions
	int _positionHandle = mShaders[mActiveShader]->attributeLocation("vertexPosition");
	mShaders[mActiveShader]->disableAttributeArray(_positionHandle);
	mVertexbuffer.release();

	// 2nd attribute buffer : colors
	_positionHandle = mShaders[mActiveShader]->attributeLocation("vertexColor");
	mShaders[mActiveShader]->disableAttributeArray(_positionHandle);
	mColorbuffer.release();

	// 3rd attribute buffer : normals
	_positionHandle = mShaders[mActiveShader]->attributeLocation("vertexNormal");
	mShaders[mActiveShader]->disableAttributeArray(_positionHandle);
	mNormalBuffer.release();
}


void Object::loadShader(SceneRenderer* fRenderer, Object::Shader fShader, QString fVertexShaderPath, QString fFragmentShaderPath){
	QOpenGLShaderProgram* _shader = new QOpenGLShaderProgram(fRenderer);

	if (!_shader->addShaderFromSourceFile(QOpenGLShader::Vertex, fVertexShaderPath)) {
		QMessageBox::critical(0, "Error", "Error loading vertex shader " + fVertexShaderPath);
		exit(EXIT_FAILURE);
	}

	if (!_shader->addShaderFromSourceFile(QOpenGLShader::Fragment, fFragmentShaderPath)) {
		QMessageBox::critical(0, "Error", "Error loading fragment shader " + fFragmentShaderPath);
		exit(EXIT_FAILURE);
	}
	_shader->link();

	if (fShader >= mShaders.size()){
		mShaders.resize(fShader + 1);
	}

	mShaders[fShader] = _shader;
}


void Object::initShader(SceneRenderer* fRenderer) {
    // Check the context
	QGLContext *context = fRenderer->context();
    if (!context){
        QMessageBox::critical(0, "Error", "Context Error");
      exit(EXIT_FAILURE);
    }
	
	QString _shaderPath = "resources/shaders/";

	loadShader(fRenderer, Shader::STANDARD_SHADING,_shaderPath + "StandardShading.vertexshader", _shaderPath + "StandardShading.fragmentshader");

	loadShader(fRenderer, Shader::DEBUG_NORMAL, _shaderPath + "DebugNormal.vertexshader", _shaderPath + "DebugNormal.fragmentshader");

	loadShader(fRenderer, Shader::COLORMAP, _shaderPath + "StandardShading.vertexshader", _shaderPath + "ColorMap.fragmentshader");

	loadShader(fRenderer, Shader::DEPTHMAP, _shaderPath + "StandardShading.vertexshader", _shaderPath + "DepthMap.fragmentshader");

	//qDebug() << mShader->log();

}


void Object::draw(SceneRenderer* fRenderer)
{
	// Bind Vertex Array Object
    mVAO.bind();
	// bind attributes of shaders 
	bindAttributes(fRenderer);

	// Draw triangles
	fRenderer->glDrawArrays(GL_TRIANGLES, 0, mVertices.size());

	releaseAttributes(fRenderer);
	mVAO.release();
}


void Object::computeBoundingBox(){
	mBoundingBox.mVector0 = mBoundingBox.mVector1 = QVector3D(0.f, 0.f, 0.f);

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


void Object::normalizeData(){
	computeNormals();

	std::vector<QVector3D> _vertices;
	std::vector<QVector2D> _vextureCoordinates;
	std::vector<QVector3D> _normals;
	std::vector<QVector3D> _color;

	for (unsigned int _indice : mIndices){

		if (_indice < mVertices.size()) {
			_vertices.push_back(mVertices[_indice]);
		}

		if (_indice < mNormals.size()) {
			_normals.push_back(mNormals[_indice]);
		}

		if (_indice < mColor.size()) {
			_color.push_back(mColor[_indice]);
		}
	}

	mVertices = _vertices;
	mTextureCoordinates = _vextureCoordinates;
	mNormals = _normals;
	mColor = _color;
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

void Object::switchShader(Object::Shader fShader){
	mActiveShader = fShader;
}

QOpenGLShaderProgram * Object::getShader(){

	if (mActiveShader != mCurrentShader) {
		//mIsVboInitialized = false;
		mCurrentShader = mActiveShader;
	}

	return mShaders[mActiveShader];
}

QMatrix4x4 Object::getModelMatrix(bool fWithoutScaling)
{
	QMatrix4x4 _modelMatrix;
	_modelMatrix.translate(mPosition);
	const float _radTodeg = 57.29578f;
	_modelMatrix.rotate(_radTodeg * mRotation.x(), QVector3D(1.f, 0.f, 0.f));
	_modelMatrix.rotate(_radTodeg * mRotation.y(), QVector3D(0.f, 1.f, 0.f));
	_modelMatrix.rotate(_radTodeg * mRotation.z(), QVector3D(0.f, 0.f, 1.f));
	
	if (!fWithoutScaling){
		_modelMatrix.scale(mScale);
	}

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
