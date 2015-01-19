#ifndef FLIPBOOK_ALGO1_HPP
#define FLIPBOOK_ALGO1_HPP

#include "global.hpp"
class PixelTab;

// ! \class FlipbookAlgorithm1
// ! \brief First algorithm to create an flipbook
class FlipbookAlgorithm1{
public:
//! \brief no specific constructors for flipbooks, creation constructors will be called
    
	//! \brief redefinition of virtual create method. This method can be redefined in Algorithms
    virtual std::vector<PixelTab*> create(std::vector<PixelTab*> fToUse);
       
};


#endif
