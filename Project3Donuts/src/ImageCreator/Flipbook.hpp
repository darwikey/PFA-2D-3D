#ifndef FLIPBOOK_HPP
#define FLIPBOOK_HPP

#include "global.hpp"
class PixelTab;

// ! \class Flipbook
// ! \brief virtual Flipbook class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class Flipbook{
public:
	//! \brief no specific constructors for flipbooks, creation constructors will be called
    
	//! \brief redefinition of virtual create method. This method can be redefined in Algorithms
    virtual std::vector<PixelTab*> create(std::vector<PixelTab*> fToUse);
       
};

#endif
