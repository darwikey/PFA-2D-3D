#include "FlipbookNormal.hpp"


void FlipbookNormal::createWindow(){
	Flipbook::createWindow();

	mGreyBox = new QCheckBox("Black and White", mWindow);
	this->insertNewWidget(mGreyBox);

	QObject::connect(mGreyBox, SIGNAL(stateChanged(int)), this, SLOT(setGrey(int)));
}


CreationFile FlipbookNormal::render(){
	std::shared_ptr<QImage> _image = this->getColorMap();

	CreationFile _file(CreationFile::Type::ANIMATED_GIF);
	_file.pushImage(_image);

	_file.pushImage(this->getDepthMap());

	return _file;
}


void FlipbookNormal::setGrey(int fIsGrey){
	mIsGrey = fIsGrey;
	this->updatePreview();
}
