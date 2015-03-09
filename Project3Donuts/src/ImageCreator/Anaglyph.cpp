#include "Anaglyph.hpp"
#include "Creator.hpp"


void Anaglyph::createWindow(bool fHasPreview){
	Creation::createWindow(fHasPreview);

	// Fill the list of algorithm
	std::vector<QString> _list = Creator::getCreator()->getListAnaglyph();
	for (auto _str : _list)	{
		mAlgoTypeBox->addItem(_str);
	}
}

