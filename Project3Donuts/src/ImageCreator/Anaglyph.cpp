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

	// Eyes distance
	mHorizontalRotationLabel = new QLabel("Rotation horizontale",
																				mWindow);
	insertNewWidget(mHorizontalRotationLabel);

	mHorizontalRotationSlider = new QSlider(Qt::Orientation::Horizontal,
																					mWindow);
	mHorizontalRotationSlider->setValue(10);
	insertNewWidget(mHorizontalRotationSlider);
	QObject::connect(mHorizontalRotationSlider,
									 SIGNAL(valueChanged(int)),
									 this,
									 SLOT(changeHorizontalRotation(int)));

	mVerticalRotationLabel = new QLabel("Rotation verticale",
																			mWindow);
	insertNewWidget(mVerticalRotationLabel);

	mVerticalRotationSlider = new QSlider(Qt::Orientation::Horizontal,
																				mWindow);
	mVerticalRotationSlider->setValue(10);
	insertNewWidget(mVerticalRotationSlider);
	QObject::connect(mVerticalRotationSlider,
									 SIGNAL(valueChanged(int)),
									 this,
									 SLOT(changeVerticalRotation(int)));
}

void Anaglyph::changeHorizontalRotation(int fHorizontalRotation){

	mHorizontalRotation = fHorizontalRotation / 10.f;
}

void Anaglyph::changeVerticalRotation(int fVerticalRotation){

	mVerticalRotation = fVerticalRotation / 10.f;
}
