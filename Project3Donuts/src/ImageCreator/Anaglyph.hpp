#ifndef ANAGLYPH_HPP
#define ANAGLYPH_HPP

#include "global.hpp"
class PixelTab;

namespace ImageCreator{
  // ! \class Anaglyph
  // ! \brief virtual Anaglyph class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
  class Anaglyph{
  public:
    //! \brief no specific constructors for anaglyphs, creation constructors will be called
    
    //! \brief redefinition of virtual create method. This method can be redefined in Algorithms
    virtual std::vector<PixelTab*> create(std::vector<PixelTab*> fToUse);
       
  }   
}

#endif
