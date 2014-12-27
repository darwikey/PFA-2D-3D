#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "global.hpp"
#include "BoundingBox.hpp"

//! \class Object
//! \brief definition of objects that will be placed in the scene
class Object : private QOpenGLFunctions{
public:
	//! \brief Construction of the object before filling it with points
	Object();

	//! \brief To move an object depending on three values on  x, y and z coordonates
	void moveObject(float fHorizontalValue, float fVerticalValue, float fDepthValue);

	//! \brief Scaling of the object, following the given rate
	//! \param Rate for the scaling, considering the actual size of the object as rate 1
	void changeObjectSize(float fRate);

	//! \brief Moving the object from his initial orientation to a new orientation
	//! \param Two angles in radian are given on the horizontal plan and the vertical plan to move the object from his initial axe
	void changeObjectOrientation(float fHorizontalAngle, float fVerticalAngle);

	//! \brief initialize the vertex buffer object
	void initVbo();

	//! \brief draw the object
	void draw();

	//! \brief return the object bounding box 
	BoundingBox getBoundingBox();

	//! \brief tell if the vertex buffer object is initialized
	bool isVboInitialized();


private:
	BoundingBox mBoundingBox;
	
	std::vector<QVector3D> mVertices;
    std::vector<QVector2D> mUvs;
    std::vector<QVector3D> mNormals;
    std::vector<uint> mIndices;
    std::vector<QVector3D> mColor;

	bool mIsVboInitialized = false;
	GLuint mVertexbuffer = 0;
	GLuint mColorbuffer = 0;
	GLuint mElementbuffer = 0;
};


#endif
