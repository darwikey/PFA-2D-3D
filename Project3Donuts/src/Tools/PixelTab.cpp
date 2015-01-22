#include "PixelTab.hpp"

PixelTab::PixelTab(){}

PixelTab::PixelTab(int fWidth, int fHeight){
  mTable = std::vector<Pixel*>(fWidth * fHeight, new Pixel()) ;
  mWidth = fWidth ;
  mHeight = fHeight ;
}

PixelTab::PixelTab(std::vector<Pixel*> fTable, int fWidth, int fHeight){
  mTable = fTable ;
  mWidth = fWidth ;
  mHeight = fHeight ;
}

Pixel PixelTab::getPixel(int fRow, int fColumn){
  return *(mTable[fRow * mWidth + fColumn]) ;
}

void PixelTab::setPixel(const Pixel& fTable, int fRow, int fColumn){
  Pixel * p = mTable[fRow * mWidth + fColumn] ;
  p->setR(fTable.getR()) ;
  p->setG(fTable.getG()) ;
  p->setB(fTable.getB()) ;
}

int PixelTab::getWidth() {
  return mWidth ;
}

int PixelTab::getHeight() {
  return mHeight ;
}
