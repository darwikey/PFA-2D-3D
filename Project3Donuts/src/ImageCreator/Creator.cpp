#include "Creator.hpp"
#include "Anaglyph.hpp"
#include "AnaglyphAlgorithm1.hpp"
#include "Autostereogram.hpp"
#include "Flipbook.hpp"
#include "DepthMap.hpp"


Creator* Creator::mInstance = nullptr;


Creator::Creator(){
	AnaglyphTable.push_back(new AnaglyphAlgorithm1());
}


Creator* Creator::getCreator(){
	if (mInstance == nullptr){
		mInstance = new Creator();
	}

	return mInstance;
}


void Creator::launchAnaglyph(int fAlgoNumber){
	AnaglyphTable[0]->launch();
}


void Creator::launchDepthMap(int fAlgoNumber){

}


void Creator::launchAutostereogram(int fAlgoNumber){

}


void Creator::launchFlipbook(int fAlgoNumber){

}


void Creator::launchPhotography(int fAlgoNumber){

}

