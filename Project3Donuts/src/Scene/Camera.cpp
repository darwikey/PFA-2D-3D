#include "Camera.hpp"
#include "Scene.hpp"
#include "SceneRenderer.hpp"
#include "Object.hpp"

Camera::Camera() : 
mPosition(0.f, 0.f, 3.f),
mRotation(0.f, 0.f, 0.f),
mAngleOfView(60.f){
}

Camera::Camera(QVector3D fp,QVector3D fr,float fa):
mPosition(fp[0],fp[1],fp[2]),
mRotation(fr[0],fr[1],fr[2]),
mAngleOfView(fa){
}

void Camera::moveCamera(float fHorizontalAxe, float fVerticalAxe, float fDepthValue){
	//warning wild TRIGO
	
	//mRotation += QVector3D(fHorizontalAxe, fVerticalAxe, 0.f);

	//Rotation
	QMatrix4x4 _mat;
	_mat.rotate(5.f * fVerticalAxe, QVector3D(0.f, -1.f, 0.f));
	_mat.rotate(5.f * fHorizontalAxe, QVector3D(-1.f, 0.f, 0.f));
	mPosition = _mat * mPosition;

	//Zoom
	if (fDepthValue < 0.f)
		mPosition *= 1.1f;
	else if (fDepthValue > 0.f)
		mPosition *= 0.9f;

	computeViewMatrix();
}

void Camera::repositionCamera(float fBoundingSphereRadius){
	mPosition.normalize();
	mPosition *= 1.7f * fBoundingSphereRadius;

	computeViewMatrix();
}


QImage Camera::getColorMap(){
	SceneRenderer* _renderer = Scene::getScene()->getSceneRenderer();

	if (mColorPixelBuffer == nullptr){
		mColorPixelBuffer = new QGLPixelBuffer(512, 512, _renderer->format(), _renderer);

		mColorPixelBuffer->makeCurrent();
		_renderer->initOpengl(QVector3D(0.f, 0.f, 0.4f));
	}

	mColorPixelBuffer->makeCurrent();
	_renderer->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Object::switchShader(Object::Shader::COLORMAP);

	Scene::getScene()->render(true);

	_renderer->glFlush();
	return mColorPixelBuffer->toImage();
}


QImage Camera::getDepthMap(){
	SceneRenderer* _renderer = Scene::getScene()->getSceneRenderer();

	if (mDepthPixelBuffer == nullptr){
		mDepthPixelBuffer = new QGLPixelBuffer(512, 512, _renderer->format(), _renderer);

		mDepthPixelBuffer->makeCurrent();
		_renderer->initOpengl(QVector3D(1.f, 1.f, 1.f));
	}

	mDepthPixelBuffer->makeCurrent();
	_renderer->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Object::switchShader(Object::Shader::DEPTHMAP);
	Scene::getScene()->render(true);

	_renderer->glFlush();
	return mDepthPixelBuffer->toImage();
}


const QMatrix4x4& Camera::getViewMatrix(){	
	return mViewMatrix;
}


const QMatrix4x4& Camera::getProjectionMatrix(){
	return mProjectionMatrix;
}


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
	mProjectionMatrix = QMatrix4x4();
	
	const float r = 1.f;// Scene::getScene()->getBoundingSphereRadius();

	const float _distance = r / 0.57735f; // where 0.57735f is tan(30 degrees)

	const float _zNear = 0.2f;
	const float _zFar = 10000.f;


	const QVector3D _center = QVector3D(0., 0., 0.);
	const QVector3D _up = QVector3D(0.0, 1.0, 0.0);


	mProjectionMatrix.perspective(mAngleOfView, 1.f, _zNear, _zFar);
	mViewMatrix.lookAt(mPosition, _center, _up);
}

QVector3D Camera::getPosition() const{
    return mPosition;
}

QVector3D Camera::getRotation() const{
    return mRotation;
}

float Camera::getAngleOfView() const{
    return mAngleOfView;
}
