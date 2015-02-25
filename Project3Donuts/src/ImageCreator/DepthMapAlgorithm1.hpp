#ifndef DEPTHMAP_ALGO1_HPP
#define DEPTHMAP_ALGO1_HPP

#include "../global.hpp"
class PixelTab;
class Creator;

// ! \class DepthMapAlgorithm1
// ! \brief First algorithm to create a depth
class DepthMapAlgorithm1{
public:
//! \brief no specific constructors for flipbooks, creation constructors will be called
    
	//! \brief redefinition of virtual create method. This method can be redefined in Algorithms
    virtual void create(float fPhysicalLength, float fPhysicalWidth, enum Reso fReso);
};


#endif
