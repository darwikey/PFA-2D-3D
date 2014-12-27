#ifndef EXEMPLE_HPP
#define EXEMPLE_HPP

#include "global.hpp"
#include "Pixel.hpp"

// ! \class PixelTab
// ! \brief Vector of pixels to define an image 
class PixelTab{
public:
  //! \brief All constructors
  PixelTab();
  PixelTab(int,int);
  PixelTab(<Pixel *> &, int,int);

  //! \brief Get a pixel by giving its row and its column
  Pixel getPixel(int,int);

  //! \brief Set a pixel at the given row and column number
  void setPixel(Pixel &,int,int);

private:
  <Pixel *> _mTable;
  int _mRow, _mColumn;
}

#endif
