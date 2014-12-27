#include "Object.hpp"
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>
#include "SceneRenderer.hpp"


Object::Object(){
}


void Object::moveObject(float fHorizontalValue, float fVerticalValue, float fDepthValue){
}


void Object::changeObjectSize(float fRate){
}


void Object::changeObjectOrientation(float fHorizontalAngle, float fVerticalAngle){
}


void Object::initVbo(SceneRenderer* fRenderer)
{
	fRenderer->glGenBuffers(1, &mVertexbuffer);
	fRenderer->glBindBuffer(GL_ARRAY_BUFFER, mVertexbuffer);
	fRenderer->glBufferData(GL_ARRAY_BUFFER, mVertices.size()*sizeof(QVector3D), mVertices.data(), GL_STATIC_DRAW);

	fRenderer->glGenBuffers(1, &mColorbuffer);
	fRenderer->glBindBuffer(GL_ARRAY_BUFFER, mColorbuffer);
	fRenderer->glBufferData(GL_ARRAY_BUFFER, mColor.size() * sizeof(QVector3D), mColor.data(), GL_STATIC_DRAW);

	fRenderer->glGenBuffers(1, &mElementbuffer);
	fRenderer->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementbuffer);
	fRenderer->glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(uint), mIndices.data(), GL_STATIC_DRAW);
	mIsVboInitialized = true;
}


void Object::draw(SceneRenderer* fRenderer)
{

	fRenderer->glEnableVertexAttribArray(0);
	// Index buffer
	fRenderer->glBindBuffer(GL_ARRAY_BUFFER, mVertexbuffer);

	// Draw the triangles !

	fRenderer->glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*) 0            // array buffer offset
		);

	// 2nd attribute buffer : colors
	fRenderer->glEnableVertexAttribArray(1);
	fRenderer->glBindBuffer(GL_ARRAY_BUFFER, mColorbuffer);
	fRenderer->glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*) 0                          // array buffer offset
		);

	// glDrawArrays(GL_TRIANGLES, 0, _model->vertices.size() );
	//not working, no shader
	fRenderer->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementbuffer);
	// Draw the triangles !
	fRenderer->glDrawElements(
		GL_TRIANGLES,      // mode
		mIndices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*) 0           // element array buffer offset
		);


	//glDrawArrays(GL_TRIANGLES, 0, _model->vertices.size()*3);


	fRenderer->glDisableVertexAttribArray(0);
	fRenderer->glDisableVertexAttribArray(1);
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
}


void Object::computeColors(){
	if (mVertices.size() > 0 && mIndices.size() > 0){
		for (unsigned int i = 0; i < mVertices.size(); i++)
		{
			GLfloat _f = (GLfloat) i / mVertices.size();
			QVector3D _ColorMod (_f, _f, _f);
			mColor.push_back(_ColorMod);
		}

	}
}


BoundingBox Object::getBoundingBox(){
	return mBoundingBox;
}

bool Object::isVboInitialized(){
	return mIsVboInitialized;
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
