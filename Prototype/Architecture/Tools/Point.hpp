#ifndef POINT_HPP
#define POINT_HPP
#include "global.hpp"

namespace Tools{
  // ! \class Point
  // ! \brief Tool point for a three dimension position
  class Point{
  public:
    //! Basic constructor, no arguments
    Point();

    //! Constructor with values
    Point(float, float, float);
  
    //! Getter functions for Point values
    void getX();
    void getY();
    void getZ();
  
    //! Setter functions for Point values
    void setX(float);
    void setY(float);
    void setZ(float);
  
  private:
    //! Point attributes
    float x,y,z;
  }
}

#endif
