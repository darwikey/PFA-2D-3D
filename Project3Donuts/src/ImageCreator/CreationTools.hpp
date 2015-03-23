#ifndef CREATION_TOOLS_HPP
#define CREATION_TOOLS_HPP

#include "global.hpp"


namespace CreationTools{
	//! \brief convert Qt color to standard opengl color
	QVector3D convertToVector3D(QRgb fColor);

	//! \brief convert standard opengl color to Qt color
	QRgb convertToRgb(QVector3D fColor);

	//! \brief return the pixel in the fImage at fPoint position
	//! \note interpolate the value
	QVector3D getPixel(QVector2D fPoint, const QImage& fImage);
	
	//! \brief return the pixel in the fImage at (fX, fY)
	QVector3D getPixel(int fX, int fY, const QImage& fImage);

	//! \brief apply gamma correction 
	void gammaCorrection(QImage& fImage, float fGamma);

	//! \brief convert colored image to grey scale image
	void convertToShadeOfGrey(QImage& fImage);

	//! \brief apply antialiasing filter to one pixel
	QRgb antiAliasingPixel(int fX, int fY, const QImage& fImage);

	//! \brief apply antialiasing filter in order to smooth sharp edges
	std::unique_ptr<QImage> antiAliasing(const QImage& fImage);

}


#endif
