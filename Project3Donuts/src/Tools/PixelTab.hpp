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
  PixelTab(int fWidth, int fHeight);
  PixelTab(std::vector<Pixel*>, int fWidth, int fHeight);

  //! \brief Get a pixel by giving its row and its column
  Pixel getPixel(int,int);

  //! \brief Set a pixel at the given row and column number
  void setPixel(const Pixel& ,int,int);

  //! \brief Get table width
  int getWidth() ;
  //! \brief Get table height
  int getHeight() ;
  
private:
  std::vector<Pixel*> mTable;
  size_t mWidth, mHeight;
};

#endif
