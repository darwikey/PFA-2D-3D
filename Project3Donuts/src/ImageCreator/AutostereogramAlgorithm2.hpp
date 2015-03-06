#ifndef AUTOSTEREOGRAM_ALGO3_HPP
#define AUTOSTEREOGRAM_ALGO3_HPP

#include "global.hpp"

#include "Autostereogram.hpp"

const static int oversampling = 4 ;

// ! \class AutostereogramAlgorithm3
// ! \brief First algorithm to create an autostereogram
class AutostereogramAlgorithm3 : public Autostereogram {
public:
  //! \brief no specific constructors for autostereograms, creation constructors will be called
  
  //! \brief redefinition of virtual create method. This method can be redefined in Algorithms
  virtual std::vector<QImage> create(int fDPI, int fHeight, int fWidth) ;
  static std::vector<QImage> dummyCreate(QImage * fImage, int fDPI, enum Texture fTextureStyle, char * fTexture) ;
  
private :
  static void colorBase(int fx, int fy, int * fRed, int * fGreen, int * fBlue, enum Texture fTextureStyle, QImage * fTexture, int fOversamp) ;
  static AutostereogramAlgorithm3 * getAutostereogramAlgorithm() ;
  static std::vector<QImage> depthmapToAutostereogram(QImage * fDepthmap, int fDPI, enum Texture fTextureStyle, char * fTexture) ; 
  static void colorPixel(int fx, int fy, int * fRed, int * fGreen, int * fBlue, enum Texture fTextureStyle, QImage * fTexture, int * fSameLeft, int * fSameRight, int fOversamp, int fMaxsep, int fPoffset, int fCenter, int * fLastLinked, int fyShift) ;
  static void colorRandom(int fx, int * fRed, int * fGreen, int * fBlue, enum Texture fTextureStyle) ;
} ;
#endif
