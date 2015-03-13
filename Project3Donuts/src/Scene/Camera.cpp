#include "Camera.hpp"
#include "Scene.hpp"
#include "SceneRenderer.hpp"
#include "Object.hpp"

Camera::Camera() : 
mPosition(0.f, 0.f, 3.f),
mRotation(0.f, 0.f, 0.f),
mAngleOfView(60.f){
}

Camera::Camera(QVector3D fPosition, QVector3D fRotation, float fAngleOfView) :
mPosition(fPosition),
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

	QVector3D _point = _quat.rotatedVector(QVector3D(0, 0, mPosition.length()));

	QVector3D _vector = _quat.rotatedVector(QVector3D(-1.f, 0.f, 0.f));

	_quat = QQuaternion::fromAxisAndAngle(_vector, mRotation.y());

	mPosition = _quat.rotatedVector(_point);

	//Zoom
	mPosition *= fZoom;

	computeViewMatrix();
}


void Camera::moveCameraWithMouse(float fHorizontalAxe, float fVerticalAxe, float fDepthValue){

	//Rotation
	mRotation.setX(mRotation.x() + 5.f * fHorizontalAxe);
	mRotation.setY(mRotation.y() + 5.f * fVerticalAxe);

	QQuaternion _quat = QQuaternion::fromAxisAndAngle(QVector3D(0.f, -1.f, 0.f), mRotation.x());
	
	QVector3D _point = _quat.rotatedVector(QVector3D(0, 0, mPosition.length()));

	QVector3D _vector = _quat.rotatedVector(QVector3D(-1.f, 0.f, 0.f));

	_quat = QQuaternion::fromAxisAndAngle(_vector, mRotation.y());
	
	mPosition = _quat.rotatedVector(_point);

	//Zoom
	if (fDepthValue < -0.001f)
		mPosition *= 1.1f;
	else if (fDepthValue > 0.001f)
		mPosition *= 0.9f;

	computeViewMatrix();
}


void Camera::repositionCamera(float fBoundingSphereRadius){
	mPosition.normalize();
	mPosition *= 1.7f * fBoundingSphereRadius;

	computeViewMatrix();
}


std::unique_ptr<QImage> Camera::getColorMap(int fWidth, int fHeight, QVector3D fBackgroundColor){
	SceneRenderer* _renderer = Scene::getScene()->getSceneRenderer();

	if (mColorPixelBuffer == nullptr){
		mColorPixelBuffer = new QGLPixelBuffer(fWidth, fHeight, _renderer->format(), _renderer);

		mColorPixelBuffer->makeCurrent();
		_renderer->initOpengl(fBackgroundColor);
	}

	mColorPixelBuffer->makeCurrent();
	_renderer->glViewport(0, 0, fWidth, fHeight);
	_renderer->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Object::switchShader(Object::Shader::COLORMAP);

	Scene::getScene()->render(true, this);

	_renderer->glFlush();

	std::unique_ptr<QImage> _image(new QImage(mColorPixelBuffer->toImage()));
	return _image;
}


std::unique_ptr<QImage> Camera::getDepthMap(int fWidth, int fHeight){
	SceneRenderer* _renderer = Scene::getScene()->getSceneRenderer();

	if (mDepthPixelBuffer == nullptr){
		mDepthPixelBuffer = new QGLPixelBuffer(fWidth, fHeight, _renderer->format(), _renderer);

		mDepthPixelBuffer->makeCurrent();
		_renderer->glViewport(0, 0, fWidth, fHeight);
		_renderer->initOpengl(QVector3D(1.f, 1.f, 1.f));
	}

	mDepthPixelBuffer->makeCurrent();
	_renderer->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Object::switchShader(Object::Shader::DEPTHMAP);
	Scene::getScene()->render(true, this);

	_renderer->glFlush();
	
	std::unique_ptr<QImage> _image(new QImage(mDepthPixelBuffer->toImage()));
	return _image;
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
