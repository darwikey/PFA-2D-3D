#ifndef POINT_HPP
#define POINT_HPP
#include "global.hpp"

// ! \class Point
// ! \brief Tool point for a three dimension position
class Point{
public:
  //! Basic constructor, no arguments
  Point();

  //! Constructor with values
  Point(float, float, float);
  
  //! Getter functions for Point values
  float getX();
  float getY();
  float getZ();
  
  //! Setter functions for Point values
  void setX(float);
  void setY(float);
  void setZ(float);
  
private:
  //! Point attributes
  float _mX,_mY,_mZ;
}

#endif
