#include "AnaglyphAlgorithm2.hpp"

const float AnaglyphAlgorithm2::mLeftFilter[9] = { 0.437f, 0.449f, 0.164f,
                                                   -0.062f, -0.062f, -0.024f,
                                                   -0.048f, -0.050f, -0.017f };

const float AnaglyphAlgorithm2::mRightFilter[9] = { -0.011f, -0.032f, -0.007f,
                                                    0.377f, 0.761f, 0.009f,
                                                    -0.026f, -0.093f, 1.234f };


void AnaglyphAlgorithm2::createWindow(bool fHasPreview){
  Anaglyph::createWindow(fHasPreview);

  // Eyes distance
  mGammaFilterLabel = new QLabel(QString("Filtre Gamma %1").arg(mGammaFilter), mWindow);
  insertNewWidget(mGammaFilterLabel);

  mGammaFilterSlider = new QSlider(Qt::Orientation::Horizontal, mWindow);
  mGammaFilterSlider->setValue(0);
  mGammaFilterSlider->setRange(10,100);
  insertNewWidget(mGammaFilterSlider);
  QObject::connect(mGammaFilterSlider,
                   SIGNAL(valueChanged(int)),
                   this,
                   SLOT(changeGammaFilter(int)));
}


std::unique_ptr<CreationFile> AnaglyphAlgorithm2::renderAnaglyph(){
  std::unique_ptr<QImage> _left = this->getColorMap(0.0, 0.0, 1.0, QVector2D(mTranslation / 2, 0.0));
  std::unique_ptr<QImage> _right = this->getColorMap(0.0, 0.0, 1.0, QVector2D(-mTranslation / 2, 0.0));

  std::unique_ptr<QImage> _image(new QImage(_left->size().width(),
                                            _left->size().height(),
                                            QImage::Format_RGB32));

  float _rgbLeft[3], _rgbRight[3], _rgb[3];	
  QRgb value;
	
  for(int i=0; i<_image->size().height(); i++)
    {
      for(int j=0; j<_image->size().width(); j++)
        {
          applyGamma(_left->pixel(j,i), _rgbLeft);
          modifyLeftImage(_rgbLeft);

          applyGamma(_right->pixel(j,i), _rgbRight);
          modifyRightImage(_rgbRight);

          for(int k=0; k<3; k++)
            {
              _rgb[k] = _rgbLeft[k] + _rgbRight[k];
            }

          value = applyGammaRevert(_rgb);
          _image->setPixel(j,i,value);
        }
    }
	
  std::unique_ptr<CreationFile> _file( new CreationFile(CreationFile::Type::IMAGE));
  _file->pushImage(std::move(_image));
	
  return _file;
}

void AnaglyphAlgorithm2::modifyLeftImage(float *fRgb){

  QMatrix3x3 _leftFilterMatrix(mLeftFilter);

  QGenericMatrix<1,3,float> _vector(fRgb);
  
  _vector = _leftFilterMatrix * _vector;

  fRgb[0] = std::max(std::min(_vector(0,0), 1.f), 0.f);
  fRgb[1] = std::max(std::min(_vector(1,0), 1.f), 0.f);
  fRgb[2] = std::max(std::min(_vector(2,0), 1.f), 0.f);
}

void AnaglyphAlgorithm2::modifyRightImage(float *fRgb){

  QMatrix3x3 _rightFilterMatrix(mRightFilter);
	
  QGenericMatrix<1,3,float> _vector(fRgb);
  _vector = _rightFilterMatrix * _vector;

  fRgb[0] = std::max(std::min(_vector(0,0), 1.f), 0.f);
  fRgb[1] = std::max(std::min(_vector(1,0), 1.f), 0.f);
  fRgb[2] = std::max(std::min(_vector(2,0), 1.f), 0.f);
}

void AnaglyphAlgorithm2::applyGamma(QRgb fPixel, float *fRgb){

  fRgb[0] = qPow((float) qRed(fPixel)   / 255., mGammaFilter);
  fRgb[1] = qPow((float) qGreen(fPixel) / 255., mGammaFilter);
  fRgb[2] = qPow((float) qBlue(fPixel)  / 255., mGammaFilter);
}

QRgb AnaglyphAlgorithm2::applyGammaRevert(float *fRgb){

  QRgb _value = qRgb(255 * qPow(fRgb[0], 1 / mGammaFilter),
                     255 * qPow(fRgb[1], 1 / mGammaFilter),
                     255 * qPow(fRgb[2], 1 / mGammaFilter));

  return _value;
}

void AnaglyphAlgorithm2::changeGammaFilter(int fGammaFilter){

  mGammaFilter = fGammaFilter / 10.f;

  mGammaFilterLabel->setText(QString("Filtre Gamma %1").arg(mGammaFilter));
}
