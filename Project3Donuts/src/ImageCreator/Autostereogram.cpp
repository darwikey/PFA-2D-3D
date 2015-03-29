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

	mTextureStyleLabel = new QLabel("Type de rendu : ", mWindow);
	insertNewWidget(mTextureStyleLabel);

	mChooseTextureStyle = new QComboBox(mWindow);
	mChooseTextureStyle->addItem("Aléatoire noir et blanc");
	mChooseTextureStyle->addItem("Aléatoire niveaux de gris");
	mChooseTextureStyle->addItem("Aléatoire couleur");
	mChooseTextureStyle->addItem("Texture");
	insertNewWidget(mChooseTextureStyle);
	
	QObject::connect(mChooseTextureStyle, SIGNAL(currentIndexChanged(int)), this, SLOT(changeTextureStyle(int)));

	mChooseViewLabel = new QLabel("Vue : ", mWindow);
	insertNewWidget(mChooseViewLabel);
	
	mChooseView = new QComboBox(mWindow);
	mChooseView->addItem("Autostéréogramme");
	mChooseView->addItem("Carte de profondeur");
	insertNewWidget(mChooseView);

	QObject::connect(mChooseView, SIGNAL(currentIndexChanged(int)), this, SLOT(changeView(int)));

}


std::vector<float> Autostereogram::getDepth(const QImage& fImg) {
	int _width = fImg.width();
	int _height = fImg.height();

	// depthmap
	std::vector<float> result(_width * _height, 0.);

	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			result[i * _width + j] = qGray(fImg.pixel(j, i)) / 255.f;
		}
	}

	return result;
}


void Autostereogram::changeTextureStyle(int fSelectedTextureStyle){
	switch (fSelectedTextureStyle) {
	case 0:
		mTextureStyle = RANDNB;
		break;
	case 1:
		mTextureStyle = RANDGREY;
		break;
	case 2:
		mTextureStyle = RANDCOLOR;
		break;
	case 3:
		mTextureStyle = TEXTUREMAP;
		mTexturePath = QFileDialog::getOpenFileName(0, "Texture...", QString());
		break;
	}
	updatePreview();
}


void Autostereogram::colorRandom(int fx) {
	switch (mTextureStyle) {

	case TEXTUREMAP:
		break;

	case RANDNB:

		/*
		   Black-and white images will actually
		   be in shades of grey if there is oversampling
		   */

		mRed[fx] = (rand() & 1) * 255;
		mGreen[fx] = mRed[fx];
		mBlue[fx] = mRed[fx];
		break;

	case RANDGREY:
		mRed[fx] = rand() % 256;
		mGreen[fx] = mRed[fx];
		mBlue[fx] = mRed[fx];
		break;

	case RANDCOLOR:
		mRed[fx] = rand() % 256;
		mGreen[fx] = rand() % 256;
		mBlue[fx] = rand() % 256;
		break;

	}
}

void Autostereogram::changeView(int fSelectedView){
  mViewIsAutostereogram = (fSelectedView == 0);
  updatePreview();
}
