#ifndef CREATOR_HPP
#define CREATOR_HPP

#include "global.hpp"


class Anaglyph;
class Autostereogram;
class Flipbook;
class Photograph;

//! \class Creator
//! \brief Creator will be in charge of creating what the user asks
class Creator{
public:

	//! \brief get instance of Creator
	static Creator* getCreator();

	//! \brief display a window where the user is able to configure and render
	//! \param The id of the algorithm that will be used.
	void launchAnaglyph(unsigned int fAlgoNumber);

	//! \brief display a window where the user is able to configure and render
	//! \param The id of the algorithm that will be used.
	void launchAutostereogram(unsigned int fAlgoNumber);

	//! \brief display a window where the user is able to configure and render
	//! \param The id of the algorithm that will be used.
	void launchFlipbook(unsigned int fAlgoNumber);

	//! \brief display a window where the user is able to configure and render
	//! \param The id of the algorithm that will be used.
	void launchPhotograph(unsigned int fAlgoNumber);



private:
	//! \brief Creator only has a default constructor
	Creator();


	static Creator* mInstance;

	std::vector<Anaglyph*> mAnaglyphTable;
	std::vector<Autostereogram*> mAutostereogramTable;
	std::vector<Flipbook*> mFlipbookTable;
	std::vector<Photograph*> mPhotographTable;
};


#endif
