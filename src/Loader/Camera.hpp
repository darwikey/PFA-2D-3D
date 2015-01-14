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

	//! \brief get an access to the image created for the viewport
	const PixelTab& getViewPort();
	
	QMatrix4x4 getMatrix();
	
	//! \brief get an access to the depth map
	const PixelTab& getDepthMap();

	private:
	QVector3D mPosition;
	QVector3D mRotation;
	float mAngleOfView; // in radian
};

#endif