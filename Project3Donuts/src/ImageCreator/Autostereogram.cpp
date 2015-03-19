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

	mTextureStyleLabel = new QLabel("Type de rendu : ", mWindow) ;
	insertNewWidget(mTextureStyleLabel) ;
	
	mChooseTextureStyle = new QComboBox(mWindow) ;
	mChooseTextureStyle->addItem("Aléatoire noir et blanc") ;
	mChooseTextureStyle->addItem("Aléatoire niveaux de gris") ;
	mChooseTextureStyle->addItem("Aléatoire couleur") ;
	mChooseTextureStyle->addItem("Texture") ;
	insertNewWidget(mChooseTextureStyle) ;

	QObject::connect(mChooseTextureStyle, SIGNAL(currentIndexChanged(int)), SLOT(changeTextureStyle(int))) ;
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

void Autostereogram::changeTextureStyle(int fSelectedTextureStyle){
  switch (fSelectedTextureStyle) {
  case 0 :
    mTextureStyle = RANDNB ;
    break ;
  case 1 :
    mTextureStyle = RANDGREY ;
    break ;
  case 2 :
    mTextureStyle = RANDCOLOR ;
    break ;
  case 3 :
    mTextureStyle = TEXTUREMAP ;
    mTexturePath = QFileDialog::getOpenFileName(0, "Texture...", QString());
    break ;
  }    
  updatePreview();
}

void Autostereogram::colorRandom(int fx) {
  switch (mTextureStyle) {

  case TEXTUREMAP :
    break ;
    
  case RANDNB :
    
    /* Because of resolution enhancement (which involves coloring real points with the average color of virtual points), black-and white images will actually be in shades of grey */
    
    mred[fx] = (rand()&1) * 255 ;
    mgreen[fx] = mred[fx] ;
    mblue[fx] = mred[fx] ;
    break ;
    
  case RANDGREY :
    mred[fx] = rand() %256 ;
    mgreen[fx] = mred[fx] ;
    mblue[fx] = mred[fx] ;
    break ;
    
  case RANDCOLOR :
    mred[fx] = rand() %256;
    mgreen[fx] = rand() %256;
    mblue[fx] = rand() %256;
    break ;
   
  }
}
