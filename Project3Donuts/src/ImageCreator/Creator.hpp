#ifndef CREATOR_HPP
#define CREATOR_HPP

#include <iostream>
#include "../global.hpp"
#include "Creation.hpp"
class PixelTab;

//! \class Creator
//! \brief Creator will be in charge of creating what the user asks
class Creator{
public:
	//! \brief Creator only has a default constructor that will be called at the program launch
	Creator();

	//! \brief Creator has one method for every possible view the user wants to create
	//! \param The given parameter is a virtual Creation who reflects the type of algorithm that will be used. Eg, if the user wants to use the second algorithm for anaglyphs, wanted creation will be a AnaglyphAlgorithm2 object
    Creation createAnaglyph(int fAlgoNumber, float fPhysicalLength, float fPhysicalWidth, enum Reso fReso);
    Creation createDepthMap(int fAlgoNumber, float fPhysicalLength, float fPhysicalWidth, enum Reso fReso);
    Creation createAutostereogram(int fAlgoNumber, float fPhysicalLength, float fPhysicalWidth, enum Reso fReso);
    Creation createFlipbook(int fAlgoNumber, float fPhysicalLength, float fPhysicalWidth, enum Reso fReso);
    Creation createPhotography(int fAlgoNumber, float fPhysicalLength, float fPhysicalWidth, enum Reso fReso);

private:
    Creation *mCreation;
};


#endif
