#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "global.hpp"
#include "Point.hpp"

namespace Tools{
  // ! \class Vector
  // ! \brief Tool vector defining a vector in a three dimension place
  class Vector{
  public:
    // ! \brief Constructors for Vector class
    Vector();

    // ! \brief Two ways of defining a vector : with three values or with two points
    // ! \param Two points to calculate Vector coordonates
    Vector(Point,Point);

    // ! \brief Two ways of defining a vector : with three values or with two points
    // ! \param Three floats to fill Vector coordonates
    Vector(float,float,float);
  
    // ! \brief Getter functions
    // ! \return Value of Vector asked coordonate
    float getXValue();
    float getYValue();
    float getZValue();

    // ! \brief Setter functions
    // ! \param A point
    void setAPoint(Point);
    void setBPoint(Point);

    // ! \brief Setter functions
    // ! \param A float
    void setXValue(float);
    void setYValue(float);
    void setZValue(float);

  private:
    float x,y,z;

    // ! \brief To fill x,y,z values from two points
    // ! \param Two points to calculate Vector values 
    void fillValues(Point,Point);	
  }
}

#endif
