#include "FlipbookNormal.hpp"


void FlipbookNormal::createWindow(){
	Flipbook::createWindow();

	//mGreyBox = new QCheckBox("Black and White", mWindow);
	//mLayout->insertWidget(2, mGreyBox);

	//QObject::connect(mGreyBox, SIGNAL(stateChanged(int)), this, SLOT(setGrey(int)));
}


std::shared_ptr<QImage> FlipbookNormal::render(){
	std::shared_ptr<QImage> _image = this->getColorMap();


	return _image;
}
