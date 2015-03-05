#include "AnaglyphAlgorithm1.hpp"


void AnaglyphAlgorithm1::createWindow(){
	Anaglyph::createWindow();


}


std::shared_ptr<QImage> AnaglyphAlgorithm1::render(){
	return this->getColorMap();
}