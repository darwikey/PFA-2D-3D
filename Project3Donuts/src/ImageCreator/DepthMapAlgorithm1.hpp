#ifndef DEPTHMAP_ALGO1_HPP
#define DEPTHMAP_ALGO1_HPP

#include "global.hpp"
#include "DepthMap.hpp"

// ! \class DepthMapAlgorithm1
// ! \brief First algorithm to create a depth
class DepthMapAlgorithm1 : public DepthMap{

public:

	//! \brief redefinition of virtual create method. This method can be redefined in Algorithms
	virtual void create(float fPhysicalLength, float fPhysicalWidth, Resolution fReso) override;
};


#endif
