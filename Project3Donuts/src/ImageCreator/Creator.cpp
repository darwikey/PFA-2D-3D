#include "Creator.hpp"
#include "Anaglyph.hpp"
#include "AnaglyphAlgorithm1.hpp"
#include "Autostereogram.hpp"
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

	// Autostereogram registration
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


void Creator::launchAnaglyph(unsigned int fAlgoNumber){
	if (fAlgoNumber < mAnaglyphTable.size()){
		mAnaglyphTable[fAlgoNumber]->launch();
	}
}


void Creator::launchAutostereogram(unsigned int fAlgoNumber){
	if (fAlgoNumber < mAutostereogramTable.size()){
		mAutostereogramTable[fAlgoNumber]->launch();
	}
}


void Creator::launchFlipbook(unsigned int fAlgoNumber){
	if (fAlgoNumber < mFlipbookTable.size()){
		mFlipbookTable[fAlgoNumber]->launch();
	}
}


void Creator::launchPhotograph(unsigned int fAlgoNumber){
	if (fAlgoNumber < mPhotographTable.size()){
		mPhotographTable[fAlgoNumber]->launch();
	}
}


void Creator::launchAnaglyph(){
	this->launchAnaglyph(0);
}


void Creator::launchAutostereogram(){
	this->launchAutostereogram(0);
}


void Creator::launchFlipbook(){
	this->launchFlipbook(0);
}


void Creator::launchPhotograph(){
	this->launchPhotograph(0);
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

