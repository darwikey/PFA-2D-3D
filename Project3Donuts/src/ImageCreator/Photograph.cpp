#include "Photograph.hpp"
#include "Creator.hpp"


void Photograph::createWindow(bool fHasPreview){
	Creation::createWindow(fHasPreview);

	// Fill the list of algorithm
	std::vector<QString> _list = Creator::getCreator()->getListPhotograph();
	for (auto _str : _list)	{
		mAlgoTypeBox->addItem(_str);
	}
}

