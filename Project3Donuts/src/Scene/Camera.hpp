#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "global.hpp"

class PixelTab;

//! \class Camera
//! \brief The camera that will be used to see the three dimension scene
class Camera{
public:
	//! \brief Camera Basic Constructor
	Camera();


	//! \brief Camera Constructor with given position, orientation and angle size
	//! \param take information about position, orientation vector and angle size
	Camera(QVector3D fPosition, QVector3D fRotation, float fAngleOfView);


	//! \brief destructor
	~Camera();


	//! \brief move the camera from its initial position with asked values
	//! \param params are about directions and values of move in those directions. horizontalAxe is about x value, verticalAxe is about y value and depthValue is about z value.
	void moveCamera(float fHorizontalRotation, float fVerticalRotation, float fZoom);

	//! \brief move the camera from its initial position with the value of the mouse
	//! \param params are about directions and values of move in those directions. horizontalAxe is about x value, verticalAxe is about y value and depthValue is about z value.
	void moveCameraWithMouse(float fHorizontalAxe, float fVerticalAxe, float fDepthValue);

	//! \brief translate the camera and the look at point
	void translateCamera(QVector3D fTranslation);

	//! \brief translate the camera from its initial position with the value of the mouse; change the look at point
	void translateCameraWithMouse(float fHorizontalAxe, float fVerticalAxe);

	//! \brief move the camera in order to see all the object
	//! \param the bounding sphere radius of the scene objects
	void repositionCamera(float fBoundingSphereRadius);

	//! \brief get an access to the image
	std::unique_ptr<QImage> getColorMap(int fWidth, int fHeight, QVector3D fBackgroundColor);
	
	//! \brief get an access to the depth map
	std::unique_ptr<QImage> getDepthMap(int fWidth, int fHeight);

	//! \brief get the view matrix associate with the camera
	const QMatrix4x4& getViewMatrix();

	//! \brief get the projection matrix associate with the camera
	const QMatrix4x4& getProjectionMatrix();

	//! \brief get the ray from th camera to the mouse
	//! \param fMousePosition, position of the mouse in the screen
	//! \param fRayOrigin, get ray origin in world space
	//! \param fRayDirection, get ray direction in world space
	void getMouseRay(QVector2D fMousePosition, QVector3D& fRayOrigin, QVector3D& fRayDirection);

	//! \brief return the camera position
    QVector3D getPosition() const;

	//! \brief return the camera rotation
    QVector3D getRotation() const;

	//! \brief return the camera angle of view
    float getAngleOfView() const;

	//! \brief return the point that the camera look at
	QVector3D getLookAtPoint() const;


private:
	// \brief compute the view matrix
	void computeViewMatrix();

	QVector3D mPosition;
	QVector3D mLookAtPoint;
	QVector3D mRotation;
	float mAngleOfView; // in degree
	QMatrix4x4 mViewMatrix;
	QMatrix4x4 mProjectionMatrix;

	QOpenGLFramebufferObject* mColorPixelBuffer = nullptr;
	QOpenGLFramebufferObject* mDepthPixelBuffer = nullptr;
};

#endif
