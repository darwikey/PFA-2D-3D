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

  mChooseViewLabel = new QLabel("Type de vue :", mWindow);
  insertNewWidget(mChooseViewLabel);
	
  mChooseView = new QComboBox(mWindow);
  mChooseView->addItem("Vue compos\303\251e");
  mChooseView->addItem("Vue gauche");
  mChooseView->addItem("Vue droite");
  insertNewWidget(mChooseView);

  QObject::connect(mChooseView, SIGNAL(currentIndexChanged(int)), this, SLOT(changeChoosenView(int)));
	
  // Eyes distance
  mTranslation = 0.074f;
  
  mTranslationLabel = new QLabel(QString("Translation %1").arg(mTranslation),
                                      mWindow);
  insertNewWidget(mTranslationLabel);

  mTranslationSlider = new QSlider(Qt::Orientation::Horizontal,
                                        mWindow);
  mTranslationSlider->setValue(74);
  
  mTranslationSlider->setRange(0,250);
  insertNewWidget(mTranslationSlider);
  QObject::connect(mTranslationSlider,
                   SIGNAL(valueChanged(int)),
                   this,
                   SLOT(changeTranslation(int)));
}

void Anaglyph::changeTranslation(int fTranslation){

  mTranslation = fTranslation / 1000.f;

  mTranslationLabel->setText(QString("Translation %1").arg(mTranslation));
}

void Anaglyph::changeChoosenView(int fViewSelected){

  mViewSelected = fViewSelected;

  updatePreview();
}

std::unique_ptr<CreationFile> Anaglyph::render(){

  switch(mViewSelected) {

  case 1:
    return renderLeft();
    break;

  case 2:
    return renderRight();
    break;

  default:
    return renderAnaglyph();
    break;
  }
}

std::unique_ptr<CreationFile> Anaglyph::renderLeft(){

  std::unique_ptr<QImage> _left = this->getColorMap(0.0, 0.0, 1.0, QVector2D(mTranslation / 2, 0.0));
	
  std::unique_ptr<CreationFile> _file( new CreationFile(CreationFile::Type::IMAGE));
  _file->pushImage(std::move(_left));
		
  return _file;
}

std::unique_ptr<CreationFile> Anaglyph::renderRight(){

  std::unique_ptr<QImage> _right = this->getColorMap(0.0, 0.0, 1.0, QVector2D(-mTranslation / 2, 0.0));

  std::unique_ptr<CreationFile> _file( new CreationFile(CreationFile::Type::IMAGE));
  _file->pushImage(std::move(_right));

  return _file;
}








