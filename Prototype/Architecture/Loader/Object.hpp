#ifndef OBJECT_HPP
#define OBJECT_HPP


#include "global.hpp"
#include "BoundingBox.hpp"

//! \class Object
//! \brief definition of objects that will be placed in the scene
class Object{
	public:
	//! \brief Construction of the object before filling it with points
	Object();

	//! \brief To move an object depending on three values on  x, y and z coordonates
	moveObject(float horizontalValue, float verticalValue, float depthValue);

	private:
	BoundingBox mBoundingBox;
	
	std::vector<QVector3D> mVertices;
    std::vector<QVector2D> mUvs;
    std::vector<QVector3D> mNormals;
    std::vector<uint> mIndices;
    std::vector<QVector3D> mColor;
}


#endif