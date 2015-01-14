#include "Camera.hpp"


Camera::Camera() : 
mPosition(0.f, 0.f, -1.f),
mRotation(0.f, 0.f, 0.f),
mAngleOfView(1.f){
}

/*Camera::Camera(QVector3D,QVector3D ,float){
  }*/

void Camera::moveCamera(float fHorizontalAxe, float fVerticalAxe, float fDepthValue){
	//warning wild TRIGO
	float _radius = mPosition.distanceToPoint(QVector3D(0.f, 0.f, 0.f));
	mRotation += QVector3D(fHorizontalAxe, fVerticalAxe, 0.f);
	
}

/*const PixelTab& Camera::getViewPort(){
}*/


QMatrix4x4 Camera::getMatrix(){
	QMatrix4x4 _matrix;

	float r = 1.f;
    float _distance = r / 0.57735f; // where 0.57735f is tan(30 degrees)

    float _zNear = _distance - r;
    float _zFar = _distance + r;


    QVector3D _eye = QVector3D(0., 0., _distance);
    QVector3D _center = QVector3D(0., 0., 0.);
    QVector3D _up = QVector3D(0.0, 1.0, 0.0);

	
    _matrix.frustum(-r, +r, -r, +r, _zNear, _zFar);
    _matrix.lookAt(_eye, _center, _up);
    _matrix.translate(mPosition.x(), mPosition.y(), mPosition.z());
    _matrix.rotate(mRotation.x(), 1.0f, 0.0f, 0.0f);
    _matrix.rotate(mRotation.y(), 0.0f, 1.0f, 0.0f);
    _matrix.rotate(mRotation.z(), 0.0f, 0.0f, 1.0f);
	
	return _matrix;
}

/*
const PixelTab& Camera::getDepthMap(){
}*/
