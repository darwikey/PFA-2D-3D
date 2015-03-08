#include "Autostereogram.hpp"


void Autostereogram::createWindow(bool fHasPreview){
	Creation::createWindow(fHasPreview);
}


std::vector<float> Autostereogram::getDepth(const QImage& fImg) {
	int _width = fImg.width();
	int _height = fImg.height();

	std::vector<float> resultat(_width * _height, 0.);
	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			resultat[i * _width + j] = qGray(fImg.pixel(j, i)) / 255.f;
		}
	}
	return resultat;
}