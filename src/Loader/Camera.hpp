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
	Camera(QVector3D,QVector3D ,float);


	//! \brief move the camera from its initial position with asked values
	//! \param params are about directions and values of move in those directions. horizontalAxe is about x value, verticalAxe is about y value and depthValue is about z value.
	void moveCamera(float fHorizontalAxe, float fVerticalAxe, float fDepthValue);

	//! \brief move the camera in order to see all the object
	//! \param the bounding sphere radius of the scene objects
	void repositionCamera(float fBoundingSphereRadius);

	//! \brief get an access to the image created for the viewport
	const PixelTab& getViewPort();
	
	//! \brief get the view matrix associate with the camera
	const QMatrix4x4& getViewMatrix();

	//! \brief get the projection matrix associate with the camera
	const QMatrix4x4& getProjectionMatrix();
	
	//! \brief get an access to the depth map
	const PixelTab& getDepthMap();


private:
	// \brief compute the view matrix
	void computeViewMatrix();

	QVector3D mPosition;
	QVector3D mRotation;
	float mAngleOfView; // in degree
	QMatrix4x4 mViewMatrix;
	QMatrix4x4 mProjectionMatrix;
};

#endif