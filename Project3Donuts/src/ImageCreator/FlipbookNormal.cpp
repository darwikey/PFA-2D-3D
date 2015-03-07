#include "FlipbookNormal.hpp"


void FlipbookNormal::createWindow(){
	Flipbook::createWindow();

	// Delete the preview image
	delete mPreviewImage;
	mPreviewImage = nullptr;

	// Shade of grey
	mGreyBox = new QCheckBox("Rendu en nuances de gris", mWindow);
	this->insertNewWidget(mGreyBox);

	QObject::connect(mGreyBox, SIGNAL(stateChanged(int)), this, SLOT(setGrey(int)));


	// Horizontal speed
	mHorizontalSpeedLabel = new QLabel("Vitesse horizontale", mWindow);
	this->insertNewWidget(mHorizontalSpeedLabel);

	mHorizontalSpeedSlider = new QSlider(Qt::Orientation::Horizontal, mWindow);
	mHorizontalSpeedSlider->setValue(50);
	this->insertNewWidget(mHorizontalSpeedSlider);


	// Vertical speed
	mVerticalSpeedLabel = new QLabel("Vitesse verticale", mWindow);
	this->insertNewWidget(mVerticalSpeedLabel);

	mVerticalSpeedSlider = new QSlider(Qt::Orientation::Horizontal, mWindow);
	mVerticalSpeedSlider->setValue(50);
	this->insertNewWidget(mVerticalSpeedSlider);


	// Zoom speed
	mZoomSpeedLabel = new QLabel("Vitesse du zoom", mWindow);
	this->insertNewWidget(mZoomSpeedLabel);

	mZoomSpeedSlider = new QSlider(Qt::Orientation::Horizontal, mWindow);
	mZoomSpeedSlider->setValue(50);
	this->insertNewWidget(mZoomSpeedSlider);


	QObject::connect(mHorizontalSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeHorizontalSpeed(int)));
	QObject::connect(mVerticalSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeVerticalSpeed(int)));
	QObject::connect(mZoomSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeZoomSpeed(int)));

	// Number of Frame
	mFrameNumberLabel = new QLabel("Nombre d'images", mWindow);
	this->insertNewWidget(mFrameNumberLabel);

	mFrameNumberBox = new QSpinBox(mWindow);
	mFrameNumberBox->setValue(mFrameNumber);
	this->insertNewWidget(mFrameNumberBox);

	QObject::connect(mFrameNumberBox, SIGNAL(valueChanged(int)), this, SLOT(changeFrameNumber(int)));
}


std::unique_ptr<CreationFile> FlipbookNormal::render(){
	std::unique_ptr<CreationFile> _file(new CreationFile(CreationFile::Type::ANIMATED_GIF));

	float _horizontalRotation = 0.f;
	float _verticalRotation = 0.f;
	float _zoom = 1.f;

	for (int _frame = 0; _frame < mFrameNumber; _frame++)	{
		
		_file->pushImage(this->getColorMap(_horizontalRotation, _verticalRotation, _zoom));

		_horizontalRotation += 35.f * mHorizontalSpeed;
		_verticalRotation += 8.f * mVerticalSpeed;
		_zoom *= 1.f + (0.1f * mZoomSpeed);
	}


	return _file;
}


void FlipbookNormal::setGrey(int fIsGrey){
	mIsGrey = fIsGrey;
	this->updatePreview();
}


void FlipbookNormal::changeHorizontalSpeed(int fSpeed){
	mHorizontalSpeed = (float)(fSpeed - 50) / 50.f;
}


void FlipbookNormal::changeVerticalSpeed(int fSpeed){
	mVerticalSpeed = (float)(fSpeed - 50) / 50.f;
}


void FlipbookNormal::changeZoomSpeed(int fSpeed){
	mZoomSpeed = (float)(fSpeed - 50) / 50.f;
}


void FlipbookNormal::changeFrameNumber(int fValue){
	mFrameNumber = fValue;
}