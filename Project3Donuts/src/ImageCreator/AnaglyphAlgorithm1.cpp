#include "AnaglyphAlgorithm1.hpp"


void AnaglyphAlgorithm1::createWindow(){
	Anaglyph::createWindow();


}


void AnaglyphAlgorithm1::render(){
	QString _file = QFileDialog::getSaveFileName(mWindow, "Save", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
	std::cout << "save image : " << _file.toStdString();

	this->getColorMap()->save(_file);
}