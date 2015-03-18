#include "Anaglyph.hpp"
#include "Creator.hpp"


void Anaglyph::createWindow(bool fHasPreview){
	Creation::createWindow(fHasPreview);


	// Fill the list of algorithm
	std::vector<QString> _list = Creator::getCreator()->getListAnaglyph();

	int i = 0;
	for (auto _str : _list)	{
		mAlgoTypeBox->addItem(_str);

		if (_str == this->metaObject()->className()){
			mAlgoTypeBox->setCurrentIndex(i);
		}

		i++;
	}

	QObject::connect(mAlgoTypeBox, SIGNAL(currentIndexChanged(int)), Creator::getCreator(), SLOT(launchAnaglyph(int)));

	mChooseViewLabel = new QLabel("Type de vue :", mWindow);
	insertNewWidget(mChooseViewLabel);
	
	mChooseView = new QComboBox(mWindow);
	mChooseView->addItem("Vue compos\303\251e");
	mChooseView->addItem("Vue gauche");
	mChooseView->addItem("Vue droite");
	insertNewWidget(mChooseView);

	QObject::connect(mChooseView, SIGNAL(currentIndexChanged(int)), this, SLOT(changeChoosenView(int)));
	
	// Eyes distance
	
	mHorizontalRotationLabel = new QLabel(QString("Rotation horizontale %1").arg(mHorizontalRotation),
																				mWindow);
	insertNewWidget(mHorizontalRotationLabel);

	mHorizontalRotationSlider = new QSlider(Qt::Orientation::Horizontal,
																					mWindow);
	mHorizontalRotationSlider->setValue(0);
	mHorizontalRotationSlider->setRange(0,200);
	insertNewWidget(mHorizontalRotationSlider);
	QObject::connect(mHorizontalRotationSlider,
									 SIGNAL(valueChanged(int)),
									 this,
									 SLOT(changeHorizontalRotation(int)));
	
	mVerticalRotationLabel = new QLabel(QString("Rotation verticale %1").arg(mVerticalRotation),
																			mWindow);
	insertNewWidget(mVerticalRotationLabel);

	mVerticalRotationSlider = new QSlider(Qt::Orientation::Horizontal,
																				mWindow);
	mVerticalRotationSlider->setValue(0);
	mVerticalRotationSlider->setRange(0,200);
	insertNewWidget(mVerticalRotationSlider);
	QObject::connect(mVerticalRotationSlider,
									 SIGNAL(valueChanged(int)),
									 this,
									 SLOT(changeVerticalRotation(int)));
}

void Anaglyph::changeHorizontalRotation(int fHorizontalRotation){

	mHorizontalRotation = fHorizontalRotation / 10.f;

	mHorizontalRotationLabel->setText(QString("Rotation horizontal %1").arg(mHorizontalRotation));
}

void Anaglyph::changeVerticalRotation(int fVerticalRotation){

	mVerticalRotation = fVerticalRotation / 10.f;

	mVerticalRotationLabel->setText(QString("Rotation vertical %1").arg(mVerticalRotation));
}

void Anaglyph::changeChoosenView(int fViewSelected){

	mViewSelected = fViewSelected;

	updatePreview();
}

std::unique_ptr<CreationFile> Anaglyph::render(){

	switch(mViewSelected) {

	case 1:
		return renderLeft();
		break;

	case 2:
		return renderRight();
		break;

	default:
		return renderAnaglyph();
		break;
	}
}

std::unique_ptr<CreationFile> Anaglyph::renderLeft(){

	std::unique_ptr<QImage> _left = this->getColorMap(-this->mHorizontalRotation / 2, -this->mVerticalRotation / 2, 1.0);
	
	std::unique_ptr<CreationFile> _file( new CreationFile(CreationFile::Type::IMAGE));
	_file->pushImage(std::move(_left));
		
	return _file;
}

std::unique_ptr<CreationFile> Anaglyph::renderRight(){

	std::unique_ptr<QImage> _right = this->getColorMap(this->mHorizontalRotation / 2, this->mVerticalRotation / 2, 1.0);

	std::unique_ptr<CreationFile> _file( new CreationFile(CreationFile::Type::IMAGE));
	_file->pushImage(std::move(_right));

	return _file;
}








