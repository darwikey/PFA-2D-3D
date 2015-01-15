#ifndef ANAGLYPH_ALGO1_HPP
#define ANAGLYPH_ALGO1_HPP

#include "global.hpp"

namespace ImageCreator{
  // ! \class AnaglyphAlgo1
  // ! \brief First algorithm to create an anaglyph
  class AnaglyphAlgorithm1{
  public:
    //! \brief no specific constructors for anaglyph, creation constructors will be called
    
    //! \brief redefinition of virtual create method. This method can be redefined in Algorithms
    virtual <Image*> create(<PixelTab*> fToUse);
       
  }   
}

#endif
