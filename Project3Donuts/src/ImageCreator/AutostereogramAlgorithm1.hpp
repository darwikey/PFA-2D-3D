#ifndef AUTOSTEREOGRAM_ALGO1_HPP
#define AUTOSTEREOGRAM_ALGO1_HPP

#include "global.hpp"
class PixelTab;

namespace ImageCreator{
  // ! \class AutostereogramAlgorithm1
  // ! \brief First algorithm to create an autostereogram
  class AutostereogramAlgorithm1{
  public:
    //! \brief no specific constructors for autostereograms, creation constructors will be called
    
    //! \brief redefinition of virtual create method. This method can be redefined in Algorithms
    virtual std::vector<PixelTab*> create(std::vector<PixelTab*>fToUse);
  };
}

#endif
