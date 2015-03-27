#include "FlipbookNormal.hpp"


void FlipbookNormal::createWindow(bool fHasPreview){
  Flipbook::createWindow(false);

  // Shade of grey
  mGreyBox = new QCheckBox("Rendu en nuances de gris", mWindow);
  this->insertNewWidget(mGreyBox);

  QObject::connect(mGreyBox, SIGNAL(stateChanged(int)), this, SLOT(setGrey(int)));


  // Horizontal speed
  mHorizontalSpeedLabel = new QLabel(QString("Vitesse horizontale %1 deg/frame").arg(mHorizontalSpeed), mWindow);
  this->insertNewWidget(mHorizontalSpeedLabel);

  mHorizontalSpeedSlider = new QSlider(Qt::Orientation::Horizontal, mWindow);
  mHorizontalSpeedSlider->setValue(0);
  mHorizontalSpeedSlider->setRange(-225, 225);
  this->insertNewWidget(mHorizontalSpeedSlider);


  // Vertical speed
  mVerticalSpeedLabel = new QLabel(QString("Vitesse verticale %1 deg/frame").arg(mVerticalSpeed), mWindow);
  this->insertNewWidget(mVerticalSpeedLabel);

  mVerticalSpeedSlider = new QSlider(Qt::Orientation::Horizontal, mWindow);
  mVerticalSpeedSlider->setValue(0);
  mVerticalSpeedSlider->setRange(-225, 225);
  this->insertNewWidget(mVerticalSpeedSlider);


  // Zoom speed
  mZoomSpeedLabel = new QLabel(QString("Vitesse du zoom %1").arg(mZoomSpeed), mWindow);
  this->insertNewWidget(mZoomSpeedLabel);

  mZoomSpeedSlider = new QSlider(Qt::Orientation::Horizontal, mWindow);
  mZoomSpeedSlider->setValue(50);
  this->insertNewWidget(mZoomSpeedSlider);


  QObject::connect(mHorizontalSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeHorizontalSpeed(int)));
  QObject::connect(mVerticalSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeVerticalSpeed(int)));
  QObject::connect(mZoomSpeedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeZoomSpeed(int)));

  // Number of Frame
  mFrameNumberLabel = new QLabel("Nombre d'images total", mWindow);
  this->insertNewWidget(mFrameNumberLabel);

  mFrameNumberBox = new QSpinBox(mWindow);
  mFrameNumberBox->setValue(mFrameNumber);
  mFrameNumberBox->setMaximum(500);
  this->insertNewWidget(mFrameNumberBox);

  QObject::connect(mFrameNumberBox, SIGNAL(valueChanged(int)), this, SLOT(changeFrameNumber(int)));

  // Frame per second
  mFramePerSecondLabel = new QLabel("Nombre d'images par seconde", mWindow);
  this->insertNewWidget(mFramePerSecondLabel);

  mFramePerSecondBox = new QSpinBox(mWindow);
  mFramePerSecondBox->setValue(mFramePerSecond);
  mFramePerSecondBox->setMaximum(20);
  this->insertNewWidget(mFramePerSecondBox);

  QObject::connect(mFramePerSecondBox, SIGNAL(valueChanged(int)), this, SLOT(changeFramePerSecond(int)));

  // Separate image
  mSeparateImageBox = new QCheckBox("Sauvegarder dans des images s\303\251par\303\251es", mWindow);
  this->insertNewWidget(mSeparateImageBox);

  QObject::connect(mSeparateImageBox, SIGNAL(stateChanged(int)), this, SLOT(setSeparateImage(int)));
}


std::unique_ptr<CreationFile> FlipbookNormal::render(){
  //delay between each frame
  float _delay = mFrameNumber / mFramePerSecond;
  
  //Type of image
  CreationFile::Type _imageType = CreationFile::Type::ANIMATED_GIF;
  if (mIsSeparateImage){
    _imageType = CreationFile::Type::SEPARATED_IMAGE;
  }

  std::unique_ptr<CreationFile> _file(new CreationFile(_imageType, _delay));

  float _horizontalRotation = 0.f;
  float _verticalRotation = 0.f;
  float _zoom = 1.f;

  for (int _frame = 0; _frame < mFrameNumber; _frame++) {

    // get color map
    std::unique_ptr<QImage> _image = this->getColorMap(_horizontalRotation, _verticalRotation, _zoom);

    if (mIsGrey){
      CreationTools::convertToShadeOfGrey(*_image);
    }

    // add a new image
    _file->pushImage(std::move(_image));

    // move the camera
    _horizontalRotation += mHorizontalSpeed;
    _verticalRotation += mVerticalSpeed;
    _zoom *= 1.f + (0.1f * mZoomSpeed);
  }


  return _file;
}


void FlipbookNormal::setGrey(int fIsGrey){
  mIsGrey = fIsGrey;
}


void FlipbookNormal::changeHorizontalSpeed(int fSpeed){
  mHorizontalSpeed = fSpeed / 10.f;

  mHorizontalSpeedLabel->setText(QString("Vitesse horizontale %1 deg/frame").arg(mHorizontalSpeed));
}


void FlipbookNormal::changeVerticalSpeed(int fSpeed){
  mVerticalSpeed = fSpeed / 10.f;

  mVerticalSpeedLabel->setText(QString("Vitesse verticale %1 deg/frame").arg(mVerticalSpeed));
}


void FlipbookNormal::changeZoomSpeed(int fSpeed){
  mZoomSpeed = (float)(fSpeed - 50) / 50.f;

  mZoomSpeedLabel->setText(QString("Vitesse zoom %1").arg(mZoomSpeed));
}


void FlipbookNormal::changeFrameNumber(int fValue){
  mFrameNumber = fValue;
}


void FlipbookNormal::changeFramePerSecond(int fValue){
  mFramePerSecond = fValue;
}


void FlipbookNormal::setSeparateImage(int fValue){
  mIsSeparateImage = fValue;
}
