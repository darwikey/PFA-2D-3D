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
  std::unique_ptr<QImage> _left = this->getColorMap(0.0,
                                                    0.0,
                                                    1.0,
                                                    QVector2D(mTranslation / 2, 0.0));
  
  std::unique_ptr<QImage> _right = this->getColorMap(0.0,
                                                     0.0,
                                                     1.0,
                                                     QVector2D(-mTranslation / 2, 0.0));

  std::unique_ptr<QImage> _image(new QImage(_left->size().width(),
                                            _left->size().height(),
                                            QImage::Format_RGB32));

  float _rgbLeft[3], _rgbRight[3], _rgb[3], _hsl[3];	
	
  for(int i=0; i<_image->size().height(); i++)
    {
      for(int j=0; j<_image->size().width(); j++)
        {
          storePixelValue(_left->pixel(j,i), _rgbLeft);
          rgbToReducedInterval(_rgbLeft);
          rgbToHsl(_rgbLeft, _hsl);
          sRgbGamma(_hsl);
          hslToRgb(_rgbLeft, _hsl);
          modifyLeftImage(_rgbLeft);

          storePixelValue(_right->pixel(j,i), _rgbRight);
          rgbToReducedInterval(_rgbRight);
          rgbToHsl(_rgbRight, _hsl);
          sRgbGamma(_hsl);
          hslToRgb(_rgbRight, _hsl);
          modifyRightImage(_rgbRight);

          for(int k=0; k<3; k++)
            {
              _rgb[k] = _rgbLeft[k] + _rgbRight[k];
            }

          rgbToHsl(_rgb, _hsl);
          sRgbGamma(_hsl);
          hslToRgb(_rgb, _hsl);
          reducedIntervalToRgb(_rgb);

          QRgb _final = qRgb(_rgb[0], _rgb[1], _rgb[2]);
          
          _image->setPixel(j,i,_final);
        }
    }
	
  std::unique_ptr<CreationFile> _file(new CreationFile(CreationFile::Type::IMAGE));
  _file->pushImage(std::move(_image));
	
  return _file;
}

void AnaglyphAlgorithm3::storePixelValue(QRgb fPixel, float *fRgb)
{
  fRgb[0] = qRed(fPixel); fRgb[1] = qGreen(fPixel); fRgb[2] = qBlue(fPixel);
}

void AnaglyphAlgorithm3::rgbToReducedInterval(float *fRgb)
{
  fRgb[0] = fRgb[0] / 255.;
  fRgb[1] = fRgb[1] / 255.;
  fRgb[2] = fRgb[2] / 255.;
}

void AnaglyphAlgorithm3::reducedIntervalToRgb(float *fRgb)
{
  fRgb[0] = fRgb[0] * 255.;
  fRgb[1] = fRgb[1] * 255.;
  fRgb[2] = fRgb[2] * 255.;

  if(fRgb[0] > 255) fRgb[0] = 255;
  if(fRgb[0] < 0)   fRgb[0] = 0;

  if(fRgb[1] > 255) fRgb[1] = 255;
  if(fRgb[1] < 0)   fRgb[1] = 0;

  if(fRgb[2] > 255) fRgb[2] = 255;
  if(fRgb[2] < 0)   fRgb[2] = 0;

}

double AnaglyphAlgorithm3::modulo(double fX, double fY)
{
  fX -= fY*abs(fX / fY);
  
  if (fX >= 0.)
    return (fX);

  else
    return (fX + fY);
}


void AnaglyphAlgorithm3::rgbToHsl(float *fRgb, float *fHsl)
{
  float _cmax = std::max(fRgb[0], std::max(fRgb[1], fRgb[2]));
  float _cmin = std::min(fRgb[0], std::min(fRgb[1], fRgb[2]));

  float _delta = _cmax - _cmin;

  fHsl[2] = (_cmax + _cmin) / 2;

  if(_delta < 0.0001)
    {
      fHsl[0] = fHsl[1] = 0;
    }

  else
    {
      fHsl[1] = _delta / (1 - abs(2 * fHsl[2] - 1));

      if(abs(_cmax - fRgb[0]) < 0.0001)
        {
          fHsl[0] = 60 * (modulo(((fRgb[1] - fRgb[2]) / _delta), 6));
        }

      else if(abs(_cmax - fRgb[1]) < 0.0001)
        {
          fHsl[0] = 60 * (((fRgb[2] - fRgb[0]) / _delta) + 2);
        }

      else
        {
          fHsl[0] = 60 * (((fRgb[1] - fRgb[2]) / _delta) + 4);
        }
    }
}

void AnaglyphAlgorithm3::hslToRgb(float *fRgb, float *fHsl)
{ 
  float _c = (1 - abs(2 * fHsl[2] - 1)) * fHsl[1];
  float _x = _c * (1 - abs((modulo((fHsl[0] / 60.), 2) - 1)));
  float _m = fHsl[2] - (_c / 2.);

  if(fHsl[0] >= 0 && fHsl[0] < 60)
    {    
      fRgb[0] = _c; fRgb[1] = _x; fRgb[2] = 0;
    }

  else if(fHsl[0] >= 60 && fHsl[0] < 120)
    {
      fRgb[0] = _x; fRgb[1] = _c; fRgb[2] = 0;
    }

  else if(fHsl[0] >= 120 && fHsl[0] < 180)
    {
      fRgb[0] = 0; fRgb[1] = _c; fRgb[2] = _x;
    }

  else if(fHsl[0] >= 180 && fHsl[0] < 240)
    {
      fRgb[0] = 0; fRgb[1] = _x; fRgb[2] = _c;
    }

  else if(fHsl[0] >= 240 && fHsl[0] < 300)
    {
      fRgb[0] = _x; fRgb[1] = 0; fRgb[2] = _c;
    }

  else
    {
      fRgb[0] = _c; fRgb[1] = 0; fRgb[2] = _x;
    }

  fRgb[0] += _m; fRgb[1] += _m; fRgb[2] += _m;
}

void AnaglyphAlgorithm3::sRgbGamma(float *fHsl)
{
  if((fHsl[1] - 0.04045) <= 0.0001)				
    fHsl[1] = fHsl[1] / 12.92;

  else
    fHsl[1] = std::pow((fHsl[1] + 0.055) / 1.055, 2.4);
}

void AnaglyphAlgorithm3::gammaCorrection(float *fHsl)
{
  if((fHsl[1] - 0.0031308) <= 0.0001)
    fHsl[1] = 12.92 * fHsl[1];

  else
    fHsl[1] = 1.055 * std::pow(fHsl[1], 0.41666) - 0.055;
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
