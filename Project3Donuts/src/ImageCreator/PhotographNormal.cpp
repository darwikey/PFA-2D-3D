#include "PhotographNormal.hpp"


void PhotographNormal::createWindow(bool fHasPreview){
	Photograph::createWindow(fHasPreview);

	mGreyBox = new QCheckBox("Rendu en nuances de gris", mWindow);
	this->insertNewWidget(mGreyBox);

	QObject::connect(mGreyBox, SIGNAL(stateChanged(int)), this, SLOT(setGrey(int)));
}


std::unique_ptr<CreationFile> PhotographNormal::render(){
	
	std::unique_ptr<QImage> _image = this->getColorMap();

	if (mIsGrey) {
		CreationTools::convertToShadeOfGrey(*_image);
	}

	std::unique_ptr<CreationFile> _file(new CreationFile(CreationFile::Type::IMAGE));
	_file->pushImage(std::move(_image));

	return _file;
}


void PhotographNormal::setGrey(int fIsGrey){
	mIsGrey = fIsGrey;
	this->updatePreview();
}
