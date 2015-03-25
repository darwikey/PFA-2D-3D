#include "AnaglyphAlgorithm3.hpp"

const float AnaglyphAlgorithm3::mLeftFilter[9] = { 0.437f, 0.449f, 0.164f,
                                                   -0.062f, -0.062f, -0.024f,
                                                   -0.048f, -0.050f, -0.017f };

const float AnaglyphAlgorithm3::mRightFilter[9] = { -0.011f, -0.032f, -0.007f,
                                                    0.377f, 0.761f, 0.009f,
                                                    -0.026f, -0.093f, 1.234f };


void AnaglyphAlgorithm3::createWindow(bool fHasPreview){
  Anaglyph::createWindow(fHasPreview);
  
}


std::unique_ptr<CreationFile> AnaglyphAlgorithm3::renderAnaglyph(){
  std::unique_ptr<QImage> _left = this->getColorMap(-this->mHorizontalRotation/2,
                                                    -this->mVerticalRotation/2,
                                                    1.0,
                                                    QVector2D(mTranslation / 2, 0.0));
  
  std::unique_ptr<QImage> _right = this->getColorMap(this->mHorizontalRotation,
                                                     this->mVerticalRotation,
                                                     1.0,
                                                     QVector2D(-mTranslation / 2, 0.0));

  std::unique_ptr<QImage> _image(new QImage(_left->size().width(),
                                            _left->size().height(),
                                            QImage::Format_RGB32));

  float _rgbLeft[3], _rgbRight[3], _rgb[3];	
	
  for(int i=0; i<_image->size().height(); i++)
    {
      for(int j=0; j<_image->size().width(); j++)
        {
          getMinColorAndOperate(_left->pixel(j,i), _rgbLeft, true);
          modifyLeftImage(_rgbLeft);

          getMinColorAndOperate(_right->pixel(j,i), _rgbRight, true);
          modifyRightImage(_rgbRight);

          for(int k=0; k<3; k++)
            {
              _rgb[k] = (_rgbLeft[k] + _rgbRight[k]) * 255;
            }

          QRgb _tmp = qRgb(_rgb[0], _rgb[1], _rgb[2]);
          getMinColorAndOperate(_tmp, _rgb, false);

          for(int k=0; k<3; k++)
            {
              _rgb[k] = _rgb[k] * 255;
            }

          QRgb _final = qRgb(_rgb[0], _rgb[1], _rgb[2]);
          
          _image->setPixel(j,i,_final);
        }
    }
	
  std::unique_ptr<CreationFile> _file( new CreationFile(CreationFile::Type::IMAGE));
  _file->pushImage(std::move(_image));
	
  return _file;
}

void AnaglyphAlgorithm3::getMinColorAndOperate(QRgb fPixel, float *fRgb, bool sRgb){

  float _rgb[3];
  
  if(qRed(fPixel) == qGreen(fPixel) && qRed(fPixel) == qBlue(fPixel))
    {
      fRgb[0] = qRed(fPixel)   / 255.;
      fRgb[1] = qGreen(fPixel) / 255.;
      fRgb[2] = qBlue(fPixel)  / 255.;
    }

  else if(qRed(fPixel) <= qGreen(fPixel) && qRed(fPixel) <= qBlue(fPixel))
    {
      colorCorrection(qRed(fPixel), qGreen(fPixel), qBlue(fPixel), _rgb, sRgb);
      fRgb[0] = _rgb[0];
      fRgb[1] = _rgb[1];
      fRgb[2] = _rgb[2];      
    }

  else if(qGreen(fPixel) <= qRed(fPixel) && qGreen(fPixel) <= qBlue(fPixel))
    {
      colorCorrection(qGreen(fPixel), qRed(fPixel), qBlue(fPixel), _rgb, sRgb);
      fRgb[0] = _rgb[1];
      fRgb[1] = _rgb[0];
      fRgb[2] = _rgb[2];      
    }

  else
    {
      colorCorrection(qBlue(fPixel), qRed(fPixel), qGreen(fPixel), _rgb, sRgb);
      fRgb[0] = _rgb[1];
      fRgb[1] = _rgb[2];
      fRgb[2] = _rgb[0];      
    }
}

void AnaglyphAlgorithm3::colorCorrection(int fR, int fG, int fB, float* fRgb, bool sRgb)
{
  float _saturation, _intensity = (fR + fG + fB) / 3.;

  if(!fR)
    _saturation = 0;

  else if(sRgb)
    {
      _saturation = fR / _intensity;
			
      if((_saturation - 0.04045) <= 0.0001)				
        _saturation = _saturation / 12.92;

      else
        _saturation = std::pow((_saturation + 0.055) / 1.055, 2.4);
    }

  else
    {
      _saturation = fR / _intensity;

      if((_saturation - 0.0031308) <= 0.0001)
        _saturation = 12.92 * _saturation;

      else
        _saturation = 1.055 * std::pow(_saturation, 0.41666) - 0.055;
    }
  
  fRgb[0] = _intensity * _saturation;
  fRgb[1] = (fRgb[0]*(fR+fB-2*fG) + 3*_intensity*(fG-fR)) / (fB+fG-2*fR);
  fRgb[2] = (fRgb[0]*(fR+fG-2*fB) + 3*_intensity*(fB-fR)) / (fB+fG-2*fR);

  fRgb[0] = fRgb[0] / 255.;
  fRgb[1] = fRgb[1] / 255.;
  fRgb[2] = fRgb[2] / 255.;
}

void AnaglyphAlgorithm3::modifyLeftImage(float *fRgb){

  QMatrix3x3 _leftFilterMatrix(mLeftFilter);

  QGenericMatrix<1,3,float> _vector(fRgb);
  
  _vector = _leftFilterMatrix * _vector;

  fRgb[0] = (_vector(0,0) < 1) ? ((_vector(0,0) > 0) ? _vector(0,0) : 0) : 1;
  fRgb[1] = (_vector(1,0) < 1) ? ((_vector(1,0) > 0) ? _vector(1,0) : 0) : 1;
  fRgb[2] = (_vector(2,0) < 1) ? ((_vector(2,0) > 0) ? _vector(2,0) : 0) : 1;
}

void AnaglyphAlgorithm3::modifyRightImage(float *fRgb){

  QMatrix3x3 _rightFilterMatrix(mRightFilter);
	
  QGenericMatrix<1,3,float> _vector(fRgb);
  _vector = _rightFilterMatrix * _vector;

  fRgb[0] = (_vector(0,0) < 1) ? ((_vector(0,0) > 0) ? _vector(0,0) : 0) : 1;
  fRgb[1] = (_vector(1,0) < 1) ? ((_vector(1,0) > 0) ? _vector(1,0) : 0) : 1;
  fRgb[2] = (_vector(2,0) < 1) ? ((_vector(2,0) > 0) ? _vector(2,0) : 0) : 1;
}
