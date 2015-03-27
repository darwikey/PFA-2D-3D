#ifndef AUTOSTEREOGRAM_ALGO2_HPP
#define AUTOSTEREOGRAM_ALGO2_HPP

#include "global.hpp"

#include "Autostereogram.hpp"


//! \class AutostereogramAlgorithm2
//! \brief Second algorithm to create an autostereogram
class AutostereogramAlgorithm2 : public Autostereogram {
  Q_OBJECT
public:
  AutostereogramAlgorithm2() ;
  
protected:
  
  virtual void createWindow(bool fHasPreview = true) override;
  virtual std::unique_ptr<CreationFile> render() override;
  
  
private :
  
  //! \brief Colors the image with random points or a texture before any linking is done
  void colorBase(int fx, int fy) ;
  
  //! \brief Colors a pixel the same as the other one in its pair or a new color if it's not linked
  void colorPixel(int fx, int fy, int * fLastLinked) ;

  //! \brief Returns the autostereogram calculated from its depthmap
  std::unique_ptr<QImage> depthmapToAutostereogram() ;
  
  const static int DPI = 75 ;
  const static int OVERSAMPLING = 4 ;

  std::vector<int> msameLeft ;
  std::vector<int> msameRight ;

  int mmaxsep = 0;
  int mpoffset = 0;
  int mcenter = 0;
  int myShift = 0;
  
} ;

#endif
