#include "Creator.hpp"
#include "Anaglyph.hpp"
#include "AnaglyphAlgorithm1.hpp"
#include "AnaglyphAlgorithm2.hpp"
#include "Autostereogram.hpp"
#include "AutostereogramDepthMap.hpp"
#include "AutostereogramAlgorithm1.hpp"
#include "AutostereogramAlgorithm2.hpp"
#include "Flipbook.hpp"
#include "FlipbookNormal.hpp"
#include "Photograph.hpp"
#include "PhotographNormal.hpp"


Creator* Creator::mInstance = nullptr;


Creator::Creator(){
	// Anaglypth registration
	mAnaglyphTable.push_back(new AnaglyphAlgorithm1());
	mAnaglyphTable.push_back(new AnaglyphAlgorithm2());

	// Autostereogram registration
	mAutostereogramTable.push_back(new AutostereogramDepthMap()) ;
	mAutostereogramTable.push_back(new AutostereogramAlgorithm1());
	mAutostereogramTable.push_back(new AutostereogramAlgorithm2());

	// Flipbook registration
	mFlipbookTable.push_back(new FlipbookNormal());

	// Photograph registration
	mPhotographTable.push_back(new PhotographNormal());
}


Creator* Creator::getCreator(){
	if (mInstance == nullptr){
		mInstance = new Creator();
	}

	return mInstance;
}


void Creator::launchAnaglyph(int fAlgoNumber){
	launchAlgorithm(mAnaglyphTable, fAlgoNumber);
}


void Creator::launchAutostereogram(int fAlgoNumber){
	launchAlgorithm(mAutostereogramTable, fAlgoNumber);
}


void Creator::launchFlipbook(int fAlgoNumber){
	launchAlgorithm(mFlipbookTable, fAlgoNumber);
}


void Creator::launchPhotograph(int fAlgoNumber){
	launchAlgorithm(mPhotographTable, fAlgoNumber);
}


std::vector<QString> Creator::getListAnaglyph() const{
	std::vector<QString> _str;
	for (auto it : mAnaglyphTable){
		_str.push_back(it->metaObject()->className());
	}

	return _str;
}


std::vector<QString> Creator::getListAutostereogram() const{
	std::vector<QString> _str;
	for (auto it : mAutostereogramTable){
		_str.push_back(it->metaObject()->className());
	}

	return _str;
}


std::vector<QString> Creator::getListFlipbook() const{
	std::vector<QString> _str;
	for (auto it : mFlipbookTable){
		_str.push_back(it->metaObject()->className());
	}

	return _str;
}


std::vector<QString> Creator::getListPhotograph() const{
	std::vector<QString> _str;
	for (auto it : mPhotographTable){
		_str.push_back(it->metaObject()->className());
	}

	return _str;
}

