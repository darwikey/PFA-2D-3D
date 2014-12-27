#ifndef PIXEL_HPP
#define PIXEL_HPP
#include "global.hpp"

// ! \class Pixel
// ! \brief Tool pixel for having three r g b values for a pixel
// ! \brief Pixel colors must be between 0 and 255
class Pixel{
public:
  //! Basic constructor, no arguments
  Pixel();
  
  //! Constructor with values
  Pixel(int, int, int);
  
  //! Getter functions for Point values
  int getR();
  int getG();
  int getB();
  
  //! Setter functions for Point values
  void setR(int);
  void setG(int);
  void setB(int);
  
private:
  //! Point attributes
  int _mR,_mG,_mB;
};

#endif