#include "BoundingBox.hpp"

BoundingBox::BoundingBox(){
}

BoundingBox::BoundingBox(QVector3D fOrigin, float fDeltaX, float fDeltaY, float fDeltaZ) : mVector0(fOrigin){
	mVector1 = mVector0 + QVector3D(fDeltaX, fDeltaY, fDeltaZ);
}
	
BoundingBox::BoundingBox(QVector3D fVector0, QVector3D fVector1) : mVector0(fVector0),
mVector1(fVector1)
{
}
	
bool BoundingBox::isCollision(QVector3D fPoint){

	return(fPoint.x() >= mVector0.x() && fPoint.x() < mVector1.x()
		   && fPoint.y() >= mVector0.y() && fPoint.y() < mVector1.y()
		   && fPoint.z() >= mVector0.z() && fPoint.z() < mVector1.z());
}
	
bool BoundingBox::isCollision(const BoundingBox& fBox){
	
	return !((fBox.mVector0.x() >= mVector1.x())
			|| (fBox.mVector1.x() <= mVector0.x())
			|| (fBox.mVector0.y() >= mVector1.y())
			|| (fBox.mVector1.y() <= mVector0.y())
			|| (fBox.mVector0.z() >= mVector1.z())
			|| (fBox.mVector1.z() <= mVector0.z()));
}
	
QVector3D BoundingBox::getCenter(){

	return 0.5f * (mVector0 + mVector1);
}
	
