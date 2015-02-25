#ifndef ANAGLYPH_HPP
#define ANAGLYPH_HPP

#include "../global.hpp"
class Creator;
class PixelTab;

// ! \class Anaglyph
// ! \brief virtual Anaglyph class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class Anaglyph : public Creation{
public:
    //! \brief no specific constructors for anaglyphs, creation constructors will be called
    
    //! \brief redefinition of virtual create method. This method can be redefined in Algorithms
    virtual void create(float fPhysicalLength, float fPhysicalWidth, enum Reso fReso)=0;
};

#endif
