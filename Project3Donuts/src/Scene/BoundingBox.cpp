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

// source :
//http://www.opengl-tutorial.org/miscellaneous/clicking-on-objects/picking-with-custom-ray-obb-function/
bool BoundingBox::isCollision(QVector3D fRayOrigin, QVector3D fRayDirection, QMatrix4x4 fModelMatrix, float & fIntersectionDistance){
	float _tMin = 0.0f;
	float _tMax = 100000.0f;

	QVector3D _OBBpositionWorldspace(fModelMatrix.column(3).x(), fModelMatrix.column(3).y(), fModelMatrix.column(3).z());

	QVector3D _delta = _OBBpositionWorldspace - fRayOrigin;

	// Test intersection with the 2 planes perpendicular to the OBB's X axis
	{
		QVector3D _xAxis(fModelMatrix.column(0).x(), fModelMatrix.column(0).y(), fModelMatrix.column(0).z());
		float e = QVector3D::dotProduct(_xAxis, _delta);
		float f = QVector3D::dotProduct(fRayDirection, _xAxis);

		if (fabs(f) > 0.001f) { // Standard case

			float _t1 = (e + mVector0.x()) / f; // Intersection with the "left" plane
			float _t2 = (e + mVector1.x()) / f; // Intersection with the "right" plane
											 // _t1 and _t2 now contain distances betwen ray origin and ray-plane intersections

											 // We want _t1 to represent the nearest intersection, 
											 // so if it's not the case, invert _t1 and _t2
			if (_t1>_t2) {
				std::swap(_t1, _t2); // swap _t1 and _t2
			}

			// _tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
			if (_t2 < _tMax)
				_tMax = _t2;
			// _tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
			if (_t1 > _tMin)
				_tMin = _t1;

			// And here's the trick :
			// If "far" is closer than "near", then there is NO intersection.
			// See the images in the tutorials for the visual explanation.
			if (_tMax < _tMin)
				return false;

		}
		else { // Rare case : the ray is almost parallel to the planes, so they don't have any "intersection"
			if (-e + mVector0.x() > 0.0f || -e + mVector1.x() < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Y axis
	// Exactly the same thing than above.
	{
		QVector3D _yAxis(fModelMatrix.column(1).x(), fModelMatrix.column(1).y(), fModelMatrix.column(1).z());
		float e = QVector3D::dotProduct(_yAxis, _delta);
		float f = QVector3D::dotProduct(fRayDirection, _yAxis);

		if (fabs(f) > 0.001f) {

			float _t1 = (e + mVector0.y()) / f;
			float _t2 = (e + mVector1.y()) / f;

			if (_t1>_t2)
				std::swap(_t1, _t2);

			if (_t2 < _tMax)
				_tMax = _t2;
			if (_t1 > _tMin)
				_tMin = _t1;
			if (_tMin > _tMax)
				return false;

		}
		else {
			if (-e + mVector0.y() > 0.0f || -e + mVector1.y() < 0.0f)
				return false;
		}
	}


	// Test intersection with the 2 planes perpendicular to the OBB's Z axis
	// Exactly the same thing than above.
	{
		QVector3D _zAxis(fModelMatrix.column(2).x(), fModelMatrix.column(2).y(), fModelMatrix.column(2).z());
		float e = QVector3D::dotProduct(_zAxis, _delta);
		float f = QVector3D::dotProduct(fRayDirection, _zAxis);

		if (fabs(f) > 0.001f) {

			float _t1 = (e + mVector0.z()) / f;
			float _t2 = (e + mVector1.z()) / f;

			if (_t1>_t2)
				std::swap(_t1, _t2);

			if (_t2 < _tMax)
				_tMax = _t2;
			if (_t1 > _tMin)
				_tMin = _t1;
			if (_tMin > _tMax)
				return false;

		}
		else {
			if (-e + mVector0.z() > 0.0f || -e + mVector1.z() < 0.0f)
				return false;
		}
	}

	fIntersectionDistance = _tMin;
	return true;
}

	
QVector3D BoundingBox::getCenter(){

	return 0.5f * (mVector0 + mVector1);
}
	
