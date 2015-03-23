#ifndef AUTOSTEREOGRAM_ALGO2_HPP
#define AUTOSTEREOGRAM_ALGO2_HPP

#include "global.hpp"

#include "Autostereogram.hpp"


// ! \class AutostereogramAlgorithm2
// ! \brief Second algorithm to create an autostereogram
class AutostereogramAlgorithm2 : public Autostereogram {
  Q_OBJECT
public:
  AutostereogramAlgorithm2() ;

protected:

  virtual void createWindow(bool fHasPreview = true) override;
  virtual std::unique_ptr<CreationFile> render() override;

  
private :

  void colorBase(int fx, int fy) ;
  void colorPixel(int fx, int fy, int * fLastLinked) ;

  AutostereogramAlgorithm2 * getAutostereogramAlgorithm() ;
  std::unique_ptr<QImage> depthmapToAutostereogram() ;
  
  const int mdpi = 75 ;
  const int moversampling = 4 ;
  const float mmu = (1.f / 3.f) ;

  
  std::vector<int> mred ;
  std::vector<int> mgreen ;
  std::vector<int> mblue ;
  std::vector<int> msameLeft ;
  std::vector<int> msameRight ;

  int mmaxsep ;
  int mpoffset ;
  int mcenter ;
  int myShift ;

} ;

#endif
