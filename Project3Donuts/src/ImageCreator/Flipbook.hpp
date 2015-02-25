#ifndef FLIPBOOK_HPP
#define FLIPBOOK_HPP

#include "../global.hpp"
class PixelTab;
class Creator;


// ! \class Flipbook
// ! \brief virtual Flipbook class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class Flipbook : public Creation{
public:
	//! \brief no specific constructors for flipbooks, creation constructors will be called
    
	//! \brief redefinition of virtual create method. This method can be redefined in Algorithms
    virtual void create(float fPhysicalLength, float fPhysicalWidth, enum Reso fReso)=0;
       
};

#endif
