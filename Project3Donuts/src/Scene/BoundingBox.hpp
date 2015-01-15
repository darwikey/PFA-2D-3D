#ifndef BOUNDING_BOX_HPP
#define BOUNDING_BOX_HPP

#include "global.hpp"

//! \class BoundingBox
//! \brief a box including a 3D model
struct BoundingBox{
	public:

	//! \brief default constructor
	BoundingBox();
	
	//! \brief constructor
	//! \param take origin of the box and his different size
	BoundingBox(QVector3D fOrigin, float fDeltaX = 0, float fDeltaY = 0, float fDeltaZ = 0);
	
	//! \brief constructor
	//! \param take two vector3D
	//! \note fVector0.x <= fVector1.x and fVector0.y <= fVector1.y and fVector0.z <= fVector1.z
	BoundingBox(QVector3D fVector0, QVector3D fVector2);
	
	//! \brief say if a vector is inside the bounding box
	bool isCollision(QVector3D fVector);
	
	//! \brief say if a bounding box collide this bounding box
	bool isCollision(const BoundingBox& fBox);
	
	//! \brief get the center of the box
	QVector3D getCenter();
	

	QVector3D mVector0;
	QVector3D mVector1;

};


#endif