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


bool BoundingBox::isCollision(QVector3D fRayOrigin, QVector3D fRayDirection, QMatrix4x4 fModelMatrix, float & fIntersectionDistance){
	float tMin = 0.0f;
	float tMax = 100000.0f;

	QVector3D OBBposition_worldspace(fModelMatrix.column(3).x(), fModelMatrix.column(3).y(), fModelMatrix.column(3).z());

	QVector3D delta = OBBposition_worldspace - fRayOrigin;

	// Test intersection with the 2 planes perpendicular to the OBB's X axis
	{
		QVector3D xaxis(fModelMatrix.column(0).x(), fModelMatrix.column(0).y(), fModelMatrix.column(0).z());
		float e = QVector3D::dotProduct(xaxis, delta);
		float f = QVector3D::dotProduct(fRayDirection, xaxis);

		if (fabs(f) > 0.001f) { // Standard case

			float t1 = (e + mVector0.x()) / f; // Intersection with the "left" plane
			float t2 = (e + mVector1.x()) / f; // Intersection with the "right" plane
											 // t1 and t2 now contain distances betwen ray origin and ray-plane intersections

											 // We want t1 to represent the nearest intersection, 
											 // so if it's not the case, invert t1 and t2
			if (t1>t2) {
				float w = t1; t1 = t2; t2 = w; // swap t1 and t2
			}

			// tMax is the nearest "far" intersection (amongst the X,Y and Z planes pairs)
			if (t2 < tMax)
				tMax = t2;
			// tMin is the farthest "near" intersection (amongst the X,Y and Z planes pairs)
			if (t1 > tMin)
				tMin = t1;

			// And here's the trick :
			// If "far" is closer than "near", then there is NO intersection.
			// See the images in the tutorials for the visual explanation.
			if (tMax < tMin)
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
		QVector3D yaxis(fModelMatrix.column(1).x(), fModelMatrix.column(1).y(), fModelMatrix.column(1).z());
		float e = QVector3D::dotProduct(yaxis, delta);
		float f = QVector3D::dotProduct(fRayDirection, yaxis);

		if (fabs(f) > 0.001f) {

			float t1 = (e + mVector0.y()) / f;
			float t2 = (e + mVector1.y()) / f;

			if (t1>t2) { float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
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
		QVector3D zaxis(fModelMatrix.column(2).x(), fModelMatrix.column(2).y(), fModelMatrix.column(2).z());
		float e = QVector3D::dotProduct(zaxis, delta);
		float f = QVector3D::dotProduct(fRayDirection, zaxis);

		if (fabs(f) > 0.001f) {

			float t1 = (e + mVector0.z()) / f;
			float t2 = (e + mVector1.z()) / f;

			if (t1>t2) { float w = t1; t1 = t2; t2 = w; }

			if (t2 < tMax)
				tMax = t2;
			if (t1 > tMin)
				tMin = t1;
			if (tMin > tMax)
				return false;

		}
		else {
			if (-e + mVector0.z() > 0.0f || -e + mVector1.z() < 0.0f)
				return false;
		}
	}

	fIntersectionDistance = tMin;
	return true;
}

	
QVector3D BoundingBox::getCenter(){

	return 0.5f * (mVector0 + mVector1);
}
	
