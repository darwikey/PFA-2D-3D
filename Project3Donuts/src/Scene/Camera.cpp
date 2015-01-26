#include "Camera.hpp"
#include "Scene.hpp"
#include "SceneRenderer.hpp"

Camera::Camera() : 
mPosition(0.f, 0.f, 3.f),
mRotation(0.f, 0.f, 0.f),
mAngleOfView(60.f){
}

/*Camera::Camera(QVector3D,QVector3D ,float){
//TODO
  }*/

void Camera::moveCamera(float fHorizontalAxe, float fVerticalAxe, float fDepthValue){
	//warning wild TRIGO
	
	//mRotation += QVector3D(fHorizontalAxe, fVerticalAxe, 0.f);

	//Rotation
	QMatrix4x4 _mat;
	_mat.rotate(5.f * fVerticalAxe, QVector3D(0.f, -1.f, 0.f));
	_mat.rotate(5.f * fHorizontalAxe, QVector3D(-1.f, 0.f, 0.f));
	mPosition = _mat * mPosition;

	//Zoom
	if (fDepthValue > 0.f)
		mPosition *= 1.1f;
	else if (fDepthValue < 0.f)
		mPosition *= 0.9f;

	computeViewMatrix();
}

void Camera::repositionCamera(float fBoundingSphereRadius){
	mPosition.normalize();
	mPosition *= 1.7f * fBoundingSphereRadius;

	computeViewMatrix();
}


/*const PixelTab& Camera::getViewPort(){
}*/


const QMatrix4x4& Camera::getViewMatrix(){	
	return mViewMatrix;
}

void Camera::applyProjectionMatrix(float fAspect){
	mProjectionMatrix = QMatrix4x4();

	const float _zNear = 1.f;
	const float _zFar = 1000.f;

	GLdouble _ymax = _zNear * tan(mAngleOfView * M_PI / 360.0);
	GLdouble _ymin = -_ymax;
	GLdouble _xmin = _ymin * fAspect;
	GLdouble _xmax = _ymax * fAspect;

	mProjectionMatrix.perspective(mAngleOfView, fAspect, _zNear, _zFar);
}

const QMatrix4x4& Camera::getProjectionMatrix(){
	return mProjectionMatrix;
}

/*
const PixelTab& Camera::getDepthMap(){
}*/


void Camera::getMouseRay(QVector2D fMousePosition, QVector3D & fRayOrigin, QVector3D & fRayDirection){
	// The ray Start and End positions, in Normalized Device Coordinates (Have you read Tutorial 4 ?)
	QVector4D _RayStart(
		((float)fMousePosition.x() - 0.5f) * 2.0f, // [0,1024] -> [-1,1]
		((float)fMousePosition.y() - 0.5f) * 2.0f, // [0, 768] -> [-1,1]
		-1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
		1.0f
		);
	QVector4D _RayEnd(
		((float)fMousePosition.x() - 0.5f) * 2.0f,
		((float)fMousePosition.y() - 0.5f) * 2.0f,
		0.0,
		1.0f
		);


	// The Projection matrix goes from Camera Space to NDC.
	// So inverse(ProjectionMatrix) goes from NDC to Camera Space.
	QMatrix4x4 _inverseProjectionMatrix = mProjectionMatrix.inverted();

	// The View Matrix goes from World Space to Camera Space.
	// So inverse(ViewMatrix) goes from Camera Space to World Space.
	QMatrix4x4 _inverseViewMatrix = mViewMatrix.inverted();

	QVector4D _RayStartCamera = _inverseProjectionMatrix * _RayStart;    
	_RayStartCamera = _RayStartCamera / _RayStartCamera.w();
	QVector4D _RayStartWorld = _inverseViewMatrix * _RayStartCamera; 
	_RayStartWorld = _RayStartWorld / _RayStartWorld.w();
	QVector4D _RayEndCamera = _inverseProjectionMatrix * _RayEnd;      
	_RayEndCamera = _RayEndCamera / _RayEndCamera.w();
	QVector4D _RayEndWorld = _inverseViewMatrix * _RayEndCamera;   
	_RayEndWorld = _RayEndWorld / _RayEndWorld.w();


	fRayDirection = QVector3D(_RayEndWorld - _RayStartWorld);
	fRayDirection.normalize();

	fRayOrigin = QVector3D(_RayStartWorld);
}


void Camera::computeViewMatrix() {
	mViewMatrix = QMatrix4x4();
	
	const QVector3D _center = QVector3D(0., 0., 0.);
	const QVector3D _up = QVector3D(0.0, 1.0, 0.0);

	mViewMatrix.lookAt(mPosition, _center, _up);
}

QVector3D Camera::getPosition(){
    return mPosition;
}

QVector3D Camera::getRotation(){
    return mRotation;
}
