#include "AnaglyphAlgorithm1.hpp"


void AnaglyphAlgorithm1::createWindow(){
	Anaglyph::createWindow();


}


std::unique_ptr<CreationFile> AnaglyphAlgorithm1::render(){
	std::unique_ptr<QImage> _image = this->getColorMap();

	// TODO 

	std::unique_ptr<CreationFile> _file( new CreationFile(CreationFile::Type::IMAGE));
	_file->pushImage(std::move(_image));

	return _file;
}