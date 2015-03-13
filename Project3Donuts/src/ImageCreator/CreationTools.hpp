#ifndef CREATION_TOOLS_HPP
#define CREATION_TOOLS_HPP

#include "global.hpp"

namespace CreationTools{

	QVector3D convertToVector3D(QRgb fColor);
	QRgb convertToRgb(QVector3D fColor);

	QVector3D getPixel(QVector2D fPoint, const QImage& fImage);
	QVector3D getPixel(int fX, int fY, const QImage& fImage);

	void gammaCorrection(QImage& fImage, float fGamma);

	void convertToShadeOfGrey(QImage& fImage);

	QRgb antiAliasingPixel(int fX, int fY, const QImage& fImage);

	std::unique_ptr<QImage> antiAliasing(const QImage& fImage);

}


#endif
