#ifndef FLIPBOOK_ALGO1_HPP
#define FLIPBOOK_ALGO1_HPP

#include "global.hpp"
#include "Flipbook.hpp"


// ! \class FlipbookAlgorithm1
// ! \brief First algorithm to create an flipbook
class FlipbookAlgorithm1 : public Flipbook{

public:

	//! \brief redefinition of virtual create method. This method can be redefined in Algorithms
    virtual void create(float fPhysicalLength, float fPhysicalWidth, Resolution fReso) override;
};


#endif
