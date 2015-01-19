#ifndef AUTOSTEREOGRAM_HPP
#define AUTOSTEREOGRAM_HPP

#include "global.hpp"
class PixelTab;

namespace ImageCreator{
  // ! \class Autostereogram
  // ! \brief virtual Autostereogram class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
  class Autostereogram{
  public:
    //! \brief no specific constructors for autostereograms, creation constructors will be called
    
    //! \brief redefinition of virtual create method. This method can be redefined in Algorithms
    virtual std::vector<PixelTab*> create(std::vector<PixelTab*> fToUse) =0;
       
  }   
}

#endif
