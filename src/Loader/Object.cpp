#include "Object.hpp"
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QGuiApplication>
#include <QtGui/QScreen>

Object::Object(){
}


void Object::moveObject(float fHorizontalValue, float fVerticalValue, float fDepthValue){
}


void Object::changeObjectSize(float fRate){
}


void Object::changeObjectOrientation(float fHorizontalAngle, float fVerticalAngle){
}


void Object::initVbo() {
	glGenBuffers(1, &mVertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mVertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size()*sizeof(QVector3D), mVertices.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &mColorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, mColorbuffer);
	glBufferData(GL_ARRAY_BUFFER, mColor.size() * sizeof(QVector3D), mColor.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &mElementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(uint), mIndices.data(), GL_STATIC_DRAW);
	mIsVboInitialized = true;
}


void Object::draw() {

	glEnableVertexAttribArray(0);
	// Index buffer
	glBindBuffer(GL_ARRAY_BUFFER, mVertexbuffer);

	// Draw the triangles !

	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*) 0            // array buffer offset
		);

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, mColorbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*) 0                          // array buffer offset
		);

	// glDrawArrays(GL_TRIANGLES, 0, _model->vertices.size() );
	//not working, no shader
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mElementbuffer);
	// Draw the triangles !
	glDrawElements(
		GL_TRIANGLES,      // mode
		mIndices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*) 0           // element array buffer offset
		);


	//glDrawArrays(GL_TRIANGLES, 0, _model->vertices.size()*3);


	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}


BoundingBox Object::getBoundingBox(){
	return mBoundingBox;
}

bool Object::isVboInitialized(){
	return mIsVboInitialized;
}