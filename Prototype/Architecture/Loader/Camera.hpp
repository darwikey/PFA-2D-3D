#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Tools::PixelTable.hpp"

namespace Loader{
  //! \class Camera
  //! \brief The camera that will be used to see the three dimension scene
  class Camera{
  public:
    //! \brief Camera Basic Constructor
    Camera();

    //! \brief Camera Constructor with information about orientation and angle size
    //! \param take information about orientation vector and angle size
    Camera(QVector3D ,float);

    //! \brief Camera Constructor with given position, orientation and angle size
    //! \param take information about position, orientation vector and angle size
    Camera(Point,QVector3D ,float);


    //! \brief move the camera from its initial position with asked values
    //! \param params are about directions and values of move in those directions. horizontalAxe is about x value, verticalAxe is about y value and depthValue is about z value.
    //! \return function returns the new point of view of the scene
    PixelTable moveCamera(float horizontalAxe, float verticalAxe, float depthValue);

	
  private:
    Point position;
    QVector3D orientation;
    float AngleOfView;
  }

}

#endif