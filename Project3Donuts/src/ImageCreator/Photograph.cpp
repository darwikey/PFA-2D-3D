#include "Photograph.hpp"
#include "Creator.hpp"


void Photograph::createWindow(bool fHasPreview){
	Creation::createWindow(fHasPreview);


	// Fill the list of algorithm
	std::vector<QString> _list = Creator::getCreator()->getListPhotograph();

	int i = 0;
	for (auto _str : _list)	{
		mAlgoTypeBox->addItem(_str);

		if (_str == this->metaObject()->className()){
			mAlgoTypeBox->setCurrentIndex(i);
		}

		i++;
	}

	QObject::connect(mAlgoTypeBox, SIGNAL(currentIndexChanged(int)), Creator::getCreator(), SLOT(launchPhotograph(int)));
}

