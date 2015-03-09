#include "Flipbook.hpp"
#include "Creator.hpp"


void Flipbook::createWindow(bool fHasPreview){
	Creation::createWindow(fHasPreview);

	// Fill the list of algorithm
	std::vector<QString> _list = Creator::getCreator()->getListFlipbook();
	for (auto _str : _list)	{
		mAlgoTypeBox->addItem(_str);
	}
}

