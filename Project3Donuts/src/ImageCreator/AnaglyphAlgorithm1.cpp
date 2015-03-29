#include "AnaglyphAlgorithm1.hpp"

void AnaglyphAlgorithm1::createWindow(bool fHasPreview){
  Anaglyph::createWindow(fHasPreview);


}

std::unique_ptr<CreationFile> AnaglyphAlgorithm1::renderAnaglyph(){

  std::unique_ptr<QImage> _left = this->getColorMap(0.0, 0.0, 1.0, QVector2D(mTranslation / 2, 0.0));
  std::unique_ptr<QImage> _right = this->getColorMap(0.0, 0.0, 1.0, QVector2D(-mTranslation / 2, 0.0));

  std::unique_ptr<QImage> _image(new QImage(_left->size().width(),
                                            _left->size().height(),
                                            QImage::Format_RGB32));

  for(int i=0; i<_image->size().height(); i++)
    {
      for(int j=0; j<_image->size().width(); j++)
        {
          //Create a pixel composed of :
          //the value R from the left image
          //the values G and B from the right image

          QRgb _value = qRgb(qRed(_left->pixel(j,i)),
                             qGreen(_right->pixel(j,i)),
                             qBlue(_right->pixel(j,i)));

          //Set the pixel created in the image destination
          _image->setPixel(j,i,_value);
        }
    }
	
  std::unique_ptr<CreationFile> _file( new CreationFile(CreationFile::Type::IMAGE));
  _file->pushImage(std::move(_image));
	
  return _file;
}
