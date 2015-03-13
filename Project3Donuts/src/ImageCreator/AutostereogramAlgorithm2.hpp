#ifndef AUTOSTEREOGRAM_ALGO2_HPP
#define AUTOSTEREOGRAM_ALGO2_HPP

#include "global.hpp"

#include "Autostereogram.hpp"



// ! \class AutostereogramAlgorithm2
// ! \brief Second algorithm to create an autostereogram
class AutostereogramAlgorithm2 : public Autostereogram {
public:

  static std::vector<QImage> dummyCreate(QImage * fImage, int fDPI, enum Texture fTextureStyle, char * fTexture) ;

protected:
  virtual void createWindow() override;
  virtual std::shared_ptr<QImage> render() override;

  
private :

  AutostereogramAlgorithm2() ;
  void colorBase(int fx, int fy) ;
  AutostereogramAlgorithm2 * getAutostereogramAlgorithm() ;
  std::shared_ptr<QImage> depthmapToAutostereogram() ; 
  void colorPixel(int fx, int fy, int * fLastLinked) ;
  void colorRandom(int fx) ;

  const int _dpi = 75 ;
  const int _oversampling = 4 ;
  const float _mu = (1. / 3.) ;

  QImage * _texture ;

  vector<int> _red ;
  vector<int> _green ;
  vector<int> _blue ;

  vector<int> _sameLeft ;
  vector<int> _sameRight ;

  int _maxsep ;
  int _poffset ;
  int _center ;
  int _yShift ;
  
} ;
#endif
