#include "AnaglyphAlgorithm2.hpp"

const float AnaglyphAlgorithm2::mLeftFilter[9] = { 0.437, 0.449, 0.164,
-0.062, -0.062, -0.024,
-0.048, -0.050, -0.017 };

const float AnaglyphAlgorithm2::mRightFilter[9] = { -0.011, -0.032, -0.007,
0.377, 0.761, 0.009,
-0.026, -0.093, 1.234 };


void AnaglyphAlgorithm2::createWindow(bool fHasPreview){
	Anaglyph::createWindow(fHasPreview);

	// Eyes distance
	mGammaFilterLabel = new QLabel(QString("Filtre Gamma %1").arg(mGammaFilter), mWindow);
	insertNewWidget(mGammaFilterLabel);

	mGammaFilterSlider = new QSlider(Qt::Orientation::Horizontal, mWindow);
	mGammaFilterSlider->setValue(0);
	mGammaFilterSlider->setRange(10,30);
	insertNewWidget(mGammaFilterSlider);
	QObject::connect(mGammaFilterSlider,
									 SIGNAL(valueChanged(int)),
									 this,
									 SLOT(changeGammaFilter(int)));
}


std::unique_ptr<CreationFile> AnaglyphAlgorithm2::renderAnaglyph(){
	std::unique_ptr<QImage> _left = this->getColorMap(-this->mHorizontalRotation/2, -this->mVerticalRotation/2, 1.0);
	std::unique_ptr<QImage> _right = this->getColorMap(this->mHorizontalRotation, this->mVerticalRotation, 1.0);

	std::unique_ptr<QImage> _image(new QImage(_left->size().width(),
																						_left->size().height(),
																						QImage::Format_RGB32));

	float rgbLeft[3], rgbRight[3], rgb[3];	
	QRgb value;
	
	for(int i=0; i<_image->size().height(); i++)
		{
			for(int j=0; j<_image->size().width(); j++)
				{
					applyGamma(_left->pixel(j,i), rgbLeft);
					modifyLeftImage(rgbLeft);

					applyGamma(_right->pixel(j,i), rgbRight);
					modifyRightImage(rgbRight);

					for(int k=0; k<3; k++)
						{
							rgb[k] = rgbLeft[k] + rgbRight[k];
						}

					value = applyGammaRevert(rgb);
					
					_image->setPixel(j,i,value);
				}
		}
	
	std::unique_ptr<CreationFile> _file( new CreationFile(CreationFile::Type::IMAGE));
	_file->pushImage(std::move(_image));
	
	return _file;
}

void AnaglyphAlgorithm2::modifyLeftImage(float *fRgb){

	QMatrix3x3 leftFilterMatrix(mLeftFilter);
	
	QGenericMatrix<1,3,float> vector(fRgb);
	vector = leftFilterMatrix * vector;

	fRgb[0] = vector(0,0);
	fRgb[1] = vector(1,0);
	fRgb[2] = vector(2,0);
}

void AnaglyphAlgorithm2::modifyRightImage(float *fRgb){

	QMatrix3x3 rightFilterMatrix(mRightFilter);
	
	QGenericMatrix<1,3,float> vector(fRgb);
	vector = rightFilterMatrix * vector;
	
	fRgb[0] = vector(0,0);
	fRgb[1] = vector(1,0);
	fRgb[2] = vector(2,0);
}

void AnaglyphAlgorithm2::applyGamma(QRgb fPixel, float *fRgb){

	fRgb[0] = qPow((float) qRed(fPixel)   / 255, mGammaFilter);
	fRgb[1] = qPow((float) qGreen(fPixel) / 255, mGammaFilter);
	fRgb[2] = qPow((float) qBlue(fPixel)  / 255, mGammaFilter);
}

QRgb AnaglyphAlgorithm2::applyGammaRevert(float *fRgb){

	QRgb value = qRgb(255 * qPow(fRgb[0], 1 / mGammaFilter),
										255 * qPow(fRgb[1], 1 / mGammaFilter),
										255 * qPow(fRgb[2], 1 / mGammaFilter));

	return value;
}

void AnaglyphAlgorithm2::changeGammaFilter(int fGammaFilter){

	mGammaFilter = fGammaFilter / 10.f;

	mGammaFilterLabel->setText(QString("Filtre Gamma %1").arg(mGammaFilter));
}
