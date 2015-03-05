#include "Creator.hpp"
#include "Anaglyph.hpp"
#include "AnaglyphAlgorithm1.hpp"
#include "Autostereogram.hpp"
#include "AutostereogramAlgorithm1.hpp"
#include "Flipbook.hpp"
#include "DepthMap.hpp"


Creator* Creator::mInstance = nullptr;


Creator::Creator(){
	mAnaglyphTable.push_back(new AnaglyphAlgorithm1());

	mAutostereogramTable.push_back(new AutostereogramAlgorithm1());
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


void Creator::launchDepthMap(unsigned int fAlgoNumber){

}


void Creator::launchAutostereogram(unsigned int fAlgoNumber){
	if (fAlgoNumber < mAutostereogramTable.size()){
		mAutostereogramTable[fAlgoNumber]->launch();
	}
}


void Creator::launchFlipbook(unsigned int fAlgoNumber){

}


void Creator::launchPhotography(unsigned int fAlgoNumber){

}

