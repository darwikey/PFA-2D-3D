#include "PhotographNormal.hpp"


void PhotographNormal::createWindow(){
	Photograph::createWindow();

	mGreyBox = new QCheckBox("Rendu en nuances de gris", mWindow);
	this->insertNewWidget(mGreyBox);

	QObject::connect(mGreyBox, SIGNAL(stateChanged(int)), this, SLOT(setGrey(int)));
}


std::unique_ptr<CreationFile> PhotographNormal::render(){
	
	std::unique_ptr<QImage> _image = this->getColorMap();

	if (mIsGrey) {

		for (int x = 0; x < _image->width(); x++){
			for (int y = 0; y < _image->height(); y++){
				QRgb _p = _image->pixel(x, y);

				int _v = (11 * qRed(_p) + 16 * qGreen(_p) + 5 * qBlue(_p)) / 32;
			
				_image->setPixel(x, y, qRgb(_v, _v, _v));
			}
		}
	}

	std::unique_ptr<CreationFile> _file(new CreationFile(CreationFile::Type::IMAGE));
	_file->pushImage(std::move(_image));

	return _file;
}


void PhotographNormal::setGrey(int fIsGrey){
	mIsGrey = fIsGrey;
	this->updatePreview();
}
