#ifndef AUTOSTEREOGRAM_ALGO1_HPP
#define AUTOSTEREOGRAM_ALGO1_HPP

#include "global.hpp"

#include "Autostereogram.hpp"
class PixelTab;

// ! \class AutostereogramAlgorithm1
// ! \brief First algorithm to create an autostereogram
class AutostereogramAlgorithm1 : public Autostereogram {
public:
  //! \brief no specific constructors for autostereograms, creation constructors will be called
  
  //! \brief redefinition of virtual create method. This method can be redefined in Algorithms
  virtual std::vector<QImage> create(int fDPI, int fHeight, int fWidth) ; //override ;

private :
  static AutostereogramAlgorithm1 * getAutostereogramAlgorithm() ;
  static int separation(float fZ, int fE) ;
  static std::vector<QImage> depthmapToAutostereogram(QImage * fDepthmap, int fE) ; 

  static int round(float fX);
  static int caseXY(int fx, int fy, int fwidth);
};

#endif
