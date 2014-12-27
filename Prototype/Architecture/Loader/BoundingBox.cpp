#include "BoundingBox.hpp"

BoundingBox::BoundingBox(){
}

BoundingBox::BoundingBox(QVector3D fOrigin, float fDeltaX = 0, float fDeltaY = 0, float fDeltaZ = 0){
}
	
BoundingBox::BoundingBox(QVector3D fVector0, QVector3D fVector2){
}
	
bool BoundingBox::isCollision(QVector3D fVector){
}
	
bool BoundingBox::isCollision(const BoundingBox& fBox){
}
	
QVector3D BoundingBox::getCenter(){
}
	
