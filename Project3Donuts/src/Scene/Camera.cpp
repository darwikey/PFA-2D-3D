#include "Camera.hpp"
#include "Scene.hpp"
#include "SceneRenderer.hpp"
#include "Object.hpp"

Camera::Camera() : 
mPosition(0.f, 0.f, 3.f),
mLookAtPoint(0.f, 0.f, 0.f),
mRotation(0.f, 0.f, 0.f),
mAngleOfView(60.f){
}

Camera::Camera(QVector3D fPosition, QVector3D fRotation, float fAngleOfView) :
mPosition(fPosition),
mLookAtPoint(0.f, 0.f, 0.f),
mRotation(fRotation),
mAngleOfView(fAngleOfView){
	computeViewMatrix();
}


Camera::~Camera(){
	delete mColorPixelBuffer;
	delete mDepthPixelBuffer;
}


void Camera::moveCamera(float fHorizontalRotation, float fVerticalRotation, float fZoom){
	
	//Rotation
	mRotation.setX(mRotation.x() + fHorizontalRotation);
	mRotation.setY(mRotation.y() + fVerticalRotation);

	QQuaternion _quat = QQuaternion::fromAxisAndAngle(QVector3D(0.f, -1.f, 0.f), mRotation.x());

	QVector3D _point = _quat.rotatedVector(QVector3D(0, 0, mPosition.distanceToPoint(mLookAtPoint)));

	QVector3D _vector = _quat.rotatedVector(QVector3D(-1.f, 0.f, 0.f));

	_quat = QQuaternion::fromAxisAndAngle(_vector, mRotation.y());

	mPosition = _quat.rotatedVector(_point) + mLookAtPoint;

	//Zoom
	mPosition = (mPosition - mLookAtPoint) * fZoom + mLookAtPoint;

	computeViewMatrix();
}


void Camera::moveCameraWithMouse(float fHorizontalAxe, float fVerticalAxe, float fDepthValue){

	//Rotation
	mRotation.setX(mRotation.x() + 5.f * fHorizontalAxe);
	mRotation.setY(mRotation.y() + 5.f * fVerticalAxe);

	QQuaternion _quat = QQuaternion::fromAxisAndAngle(QVector3D(0.f, -1.f, 0.f), mRotation.x());
	
	QVector3D _point = _quat.rotatedVector(QVector3D(0, 0, mPosition.distanceToPoint(mLookAtPoint)));

	QVector3D _vector = _quat.rotatedVector(QVector3D(-1.f, 0.f, 0.f));

	_quat = QQuaternion::fromAxisAndAngle(_vector, mRotation.y());
	
	mPosition = _quat.rotatedVector(_point) + mLookAtPoint;

	//Zoom
	if (fDepthValue < -0.001f)
		mPosition = (mPosition - mLookAtPoint) * 1.1f + mLookAtPoint;
	else if (fDepthValue > 0.001f)
		mPosition = (mPosition - mLookAtPoint) * 0.9f + mLookAtPoint;

	computeViewMatrix();
}


void Camera::translateCamera(QVector3D fTranslation){
	mLookAtPoint += fTranslation;
	mPosition += fTranslation;

	computeViewMatrix();
}

void Camera::translateCameraToZero(){
    mPosition -= mLookAtPoint;
    mLookAtPoint = QVector3D(0,0,0);

    computeViewMatrix();
}


void Camera::translateCameraWithMouse(float fHorizontalAxe, float fVerticalAxe){
	QQuaternion _quat = QQuaternion::fromAxisAndAngle(QVector3D(0.f, -1.f, 0.f), mRotation.x());
	QVector3D _vec1 = _quat.rotatedVector(QVector3D(1.f, 0, 0.f));

	_quat = QQuaternion::fromAxisAndAngle(QVector3D(-1.f, 0.f, 0.f), mRotation.y());
	QVector3D _vec2 = _quat.rotatedVector(QVector3D(0.f, 1.f, 0.f));

	QVector3D _translation = -fHorizontalAxe * _vec1 + fVerticalAxe * _vec2;
	_translation *= mPosition.distanceToPoint(mLookAtPoint) / 3.f;
	translateCamera(_translation);
}


void Camera::repositionCamera(float fBoundingSphereRadius){
	mPosition.normalize();
	mPosition *= 1.7f * fBoundingSphereRadius;

	computeViewMatrix();
}


std::unique_ptr<QImage> Camera::getColorMap(int fWidth, int fHeight, QVector3D fBackgroundColor){
	SceneRenderer* _renderer = Scene::getScene()->getSceneRenderer();

	// create the FBO
	if (mColorPixelBuffer == nullptr){
		mColorPixelBuffer = new QOpenGLFramebufferObject(fWidth, fHeight, QOpenGLFramebufferObject::Depth);

		mColorPixelBuffer->bind();
		_renderer->initOpengl();
	}

	mColorPixelBuffer->bind();
	
	// Opengl configuration
	_renderer->glViewport(0, 0, fWidth, fHeight);
	_renderer->changeBackground(fBackgroundColor);
	_renderer->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Object::switchShader(Object::Shader::COLORMAP);

	Scene::getScene()->render(true, this);

	_renderer->glFlush();

	std::unique_ptr<QImage> _image(new QImage(mColorPixelBuffer->toImage()));

	mColorPixelBuffer->release();

	return _image;
}


std::unique_ptr<QImage> Camera::getDepthMap(int fWidth, int fHeight){
	SceneRenderer* _renderer = Scene::getScene()->getSceneRenderer();

	// Create the FBO
	if (mDepthPixelBuffer == nullptr){
		mDepthPixelBuffer = new QOpenGLFramebufferObject(fWidth, fHeight, QOpenGLFramebufferObject::Depth);

		mDepthPixelBuffer->bind();
		_renderer->initOpengl();
	}

	mDepthPixelBuffer->bind();

	// Opengl configuration
	_renderer->glViewport(0, 0, fWidth, fHeight);
	_renderer->changeBackground(QVector3D(1.f, 1.f, 1.f));
	_renderer->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Object::switchShader(Object::Shader::DEPTHMAP);
	Scene::getScene()->render(true, this);

	_renderer->glFlush();
	
	std::unique_ptr<QImage> _image(new QImage(mDepthPixelBuffer->toImage()));
	
	mDepthPixelBuffer->release();

	return _image;
}


const QMatrix4x4& Camera::getViewMatrix(){	
	return mViewMatrix;
}


const QMatrix4x4& Camera::getProjectionMatrix(){
	return mProjectionMatrix;
}


void Camera::getMouseRay(QVector2D fMousePosition, QVector3D & fRayOrigin, QVector3D & fRayDirection){
	// The ray Start and End positions, in Normalized Device Coordinates
	QVector4D _rayStart(
		((float)fMousePosition.x() - 0.5f) * 2.0f,
		((float)fMousePosition.y() - 0.5f) * 2.0f,
		-1.0, // The near plane maps to Z=-1 in Normalized Device Coordinates
		1.0f
		);
	QVector4D _rayEnd(
		((float)fMousePosition.x() - 0.5f) * 2.0f,
		((float)fMousePosition.y() - 0.5f) * 2.0f,
		0.0,
		1.0f
		);

	// inverseProjectionMatrix goes from Normalized Device Coordinates to Camera Space.
	QMatrix4x4 _inverseProjectionMatrix = mProjectionMatrix.inverted();

	// inverseViewMatrix goes from Camera Space to World Space.
	QMatrix4x4 _inverseViewMatrix = mViewMatrix.inverted();

	QVector4D _rayStartCamera = _inverseProjectionMatrix * _rayStart;    
	_rayStartCamera = _rayStartCamera / _rayStartCamera.w();
	QVector4D _rayStartWorld = _inverseViewMatrix * _rayStartCamera; 
	_rayStartWorld = _rayStartWorld / _rayStartWorld.w();
	QVector4D _rayEndCamera = _inverseProjectionMatrix * _rayEnd;      
	_rayEndCamera = _rayEndCamera / _rayEndCamera.w();
	QVector4D _rayEndWorld = _inverseViewMatrix * _rayEndCamera;   
	_rayEndWorld = _rayEndWorld / _rayEndWorld.w();

	// find the direction and the origin of the ray
	fRayDirection = QVector3D(_rayEndWorld - _rayStartWorld);
	fRayDirection.normalize();

	fRayOrigin = QVector3D(_rayStartWorld);
}


void Camera::computeViewMatrix() {
	mViewMatrix = QMatrix4x4();
	mProjectionMatrix = QMatrix4x4();

	const float _zNear = 0.2f;
	const float _zFar = 10000.f;

	const QVector3D _up = QVector3D(0.0, 1.0, 0.0);


	mProjectionMatrix.perspective(mAngleOfView, 1.f, _zNear, _zFar);
	mViewMatrix.lookAt(mPosition, mLookAtPoint, _up);
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

QVector3D Camera::getLookAtPoint() const{
	return mLookAtPoint;
}

QVector3D Camera::setLookAtPoint(QVector3D fPoint)
{
    mLookAtPoint=fPoint;
}
