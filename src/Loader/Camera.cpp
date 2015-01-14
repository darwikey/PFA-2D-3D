#include "Camera.hpp"


Camera::Camera() : 
mPosition(0.f, 0.f, 3.f),
mRotation(0.f, 0.f, 0.f),
mAngleOfView(1.f){
	computeViewMatrix();
}

/*Camera::Camera(QVector3D,QVector3D ,float){
  }*/

void Camera::moveCamera(float fHorizontalAxe, float fVerticalAxe, float fDepthValue){
	//warning wild TRIGO
	float _radius = mPosition.distanceToPoint(QVector3D(0.f, 0.f, 0.f));
	//mRotation += QVector3D(fHorizontalAxe, fVerticalAxe, 0.f);

	QMatrix4x4 _mat;
	_mat.rotate(5.f * fVerticalAxe, QVector3D(0.f, -1.f, 0.f));
	_mat.rotate(5.f * fHorizontalAxe, QVector3D(-1.f, 0.f, 0.f));
	mPosition = _mat * mPosition;

	computeViewMatrix();
}

/*const PixelTab& Camera::getViewPort(){
}*/


const QMatrix4x4& Camera::getViewMatrix(){	
	return mViewMatrix;
}

/*
const PixelTab& Camera::getDepthMap(){
}*/


void Camera::computeViewMatrix() {
	mViewMatrix = QMatrix4x4();
	
	const float r = 1.f;
	const float _distance = r / 0.57735f; // where 0.57735f is tan(30 degrees)

	const float _zNear = 1.f;
	const float _zFar = 1000.f;


	const QVector3D _center = QVector3D(0., 0., 0.);
	const QVector3D _up = QVector3D(0.0, 1.0, 0.0);


	mViewMatrix.frustum(-r, +r, -r, +r, _zNear, _zFar);
	mViewMatrix.lookAt(mPosition, _center, _up);
}