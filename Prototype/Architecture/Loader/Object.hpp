#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "global.hpp"

//! \class Object
//! \brief definition of objects that will be placed in the scene
class Object{
public:
  //! \brief Construction of the object before filling it with points
  Object();

  //! \brief To move an object depending on three values on  x, y and z coordonates
  void moveObject(float fHorizontalValue, float fVerticalValue, float fDepthValue);

  //! \brief Scaling of the object, following the given rate
  //! \param Rate for the scaling, considering the actual size of the object as rate 1
  void changeObjectSize(float fRate);

  //! \brief Moving the object from his initial orientation to a new orientation
  //! \param Two angles in radian are given on the horizontal plan and the vertical plan to move the object from his initial axe
  void changeObjectOrientation(float fHorizontalAngle, float fVerticalAngle);

private:
	
}


#endif
