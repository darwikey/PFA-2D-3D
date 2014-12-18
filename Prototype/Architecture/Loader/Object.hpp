#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <cstdio>
#include "Tools::Point.hpp"

namespace Loader{
  // ! \class Object
  // ! \brief definition of objects that will be placed in the scene
  class Object{
  public:
    //! \brief Construction of the object before filling it with points
    Object();
    
    //! \brief To move an object depending on three values on  x, y and z coordonates
    moveObject(float horizontalValue, float verticalValue, float depthValue);
    
  private:
    <Point> points;	
  }
}
