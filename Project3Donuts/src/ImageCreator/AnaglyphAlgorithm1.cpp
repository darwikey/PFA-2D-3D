#include "AnaglyphAlgorithm1.hpp"


void AnaglyphAlgorithm1::createWindow(){
	Anaglyph::createWindow();


}


CreationFile AnaglyphAlgorithm1::render(){
	std::shared_ptr<QImage> _image = this->getColorMap();

	// TODO 

	CreationFile _file(CreationFile::Type::IMAGE);
	_file.pushImage(_image);

	return _file;
}