#ifndef CREATOR_HPP
#define CREATOR_HPP

#include <iostream>

//! \class Creator
//! \brief Creator will be in charge of creating what the user asks
class Creator{
public:
	//! \brief Creator only has a default constructor that will be called at the program launch
	Creator();

	//! \brief Creator has one method for every possible view the user wants to create
	//! \param The given parameter is a virtual Creation who reflects the type of algorithm that will be used. Eg, if the user wants to use the second algorithm for anaglyphs, wanted creation will be a AnaglyphAlgorithm2 object
	<Image*> createAnaglyph(Creation *fWanted);
	<Image*> createDepthMap(Creation *fWanted);
	<Image*> createAutostereogram(Creation *fWanted);
	<Image*> createFlipbook(Creation *fWanted);
	<Image*> createPhotography(Creation *fWanted);
}


#endif
