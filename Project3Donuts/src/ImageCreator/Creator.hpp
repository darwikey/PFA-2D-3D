#ifndef CREATOR_HPP
#define CREATOR_HPP

#include "global.hpp"


class Anaglyph;
class Autostereogram;
class Flipbook;

//! \class Creator
//! \brief Creator will be in charge of creating what the user asks
class Creator{
public:

	//! \brief Creator has one method for every possible view the user wants to create
	//! \param The given parameter is a virtual Creation who reflects the type of algorithm that will be used. Eg, if the user wants to use the second algorithm for anaglyphs, wanted creation will be a AnaglyphAlgorithm2 object
    /*Creation* createAnaglyph(int fAlgoNumber, float fPhysicalLength, float fPhysicalWidth, Resolution fReso);
    Creation* createDepthMap(int fAlgoNumber, float fPhysicalLength, float fPhysicalWidth, Resolution fReso);
    Creation* createAutostereogram(int fAlgoNumber, float fPhysicalLength, float fPhysicalWidth, Resolution fReso);
    Creation* createFlipbook(int fAlgoNumber, float fPhysicalLength, float fPhysicalWidth, Resolution fReso);
    Creation* createPhotography(int fAlgoNumber, float fPhysicalLength, float fPhysicalWidth, Resolution fReso);*/

	static Creator* getCreator();

	void launchAnaglyph(unsigned int fAlgoNumber);
	void launchDepthMap(unsigned int fAlgoNumber);
	void launchAutostereogram(unsigned int fAlgoNumber);
	void launchFlipbook(unsigned int fAlgoNumber);
	void launchPhotography(unsigned int fAlgoNumber);



private:
	//! \brief Creator only has a default constructor that will be called at the program launch
	Creator();


	static Creator* mInstance;

	std::vector<Anaglyph*> mAnaglyphTable;
	std::vector<Autostereogram*> mAutostereogramTable;
	std::vector<Flipbook*> mFlipbookTable;
};


#endif
