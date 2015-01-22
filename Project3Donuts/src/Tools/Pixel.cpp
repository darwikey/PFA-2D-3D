#include "Pixel.hpp"

Pixel::Pixel(){}
Pixel::Pixel(int fR, int fG, int fB){
  _mR = fR % PIXEL_MAX_COLOR ;
  _mG = fG % PIXEL_MAX_COLOR ;
  _mB = fB % PIXEL_MAX_COLOR ;
}

int Pixel::getR(){
  return _mR ;
}

int Pixel::getG(){
  return _mG ;
}

int Pixel::getB(){
  return _mB % PIXEL_MAX_COLOR ;
}
  
void Pixel::setR(int fR){
  _mR = fR % PIXEL_MAX_COLOR ;
}
void Pixel::setG(int fG){
  _mG = fG % PIXEL_MAX_COLOR ;
}
void Pixel::setB(int fB){
  _mB = fB % PIXEL_MAX_COLOR ;
}

