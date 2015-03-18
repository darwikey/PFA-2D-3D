#include "Autostereogram.hpp"
#include "Creator.hpp"

int Autostereogram::caseXY(int fx, int fy, int fwidth) {
	return fy * fwidth + fx;
}

void Autostereogram::createWindow(bool fHasPreview){
	Creation::createWindow(fHasPreview);

	// Fill the list of algorithms
	std::vector<QString> _list = Creator::getCreator()->getListAutostereogram();

	int i = 0;
	for (auto _str : _list)	{
		mAlgoTypeBox->addItem(_str);

		if (_str == this->metaObject()->className()){
			mAlgoTypeBox->setCurrentIndex(i);
		}

		i++;
	}

	QObject::connect(mAlgoTypeBox, SIGNAL(currentIndexChanged(int)), Creator::getCreator(), SLOT(launchAutostereogram(int)));
	
	mChooseTextureStyle = new QComboBox(mWindow) ;
	mChooseTextureStyle->addItem("Aléatoire noir et blanc") ;
	mChooseTextureStyle->addItem("Aléatoire niveaux de gris") ;
	mChooseTextureStyle->addItem("Aléatoire couleur") ;
	mChooseTextureStyle->addItem("Texture") ;
	insertNewWidget(mChooseTextureStyle) ;

	//mtexturePath = QFileDialog::getOpenFileName(0, "Texture...", QString(), "Fichiers image");

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
