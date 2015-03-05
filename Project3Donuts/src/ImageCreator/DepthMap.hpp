#ifndef DEPTHMAP_HPP
#define DEPTHMAP_HPP

#include "global.hpp"
#include "Creation.hpp"


// ! \class DepthMap
// ! \brief virtual DepthMap class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class DepthMap : public Creation{
public:
	//! \brief no specific constructors for flipbooks, creation constructors will be called
    
	//! \brief redefinition of virtual create method. This method can be redefined in Algorithms
    virtual void create(float fPhysicalLength, float fPhysicalWidth, Resolution fReso) = 0;
};


#endif
