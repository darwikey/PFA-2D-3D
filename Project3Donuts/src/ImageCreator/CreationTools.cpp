#include "CreationTools.hpp"

namespace CreationTools{

	QVector3D convertToVector3D(QRgb fColor){
		return QVector3D((float)qRed(fColor) / 255.f, (float)qGreen(fColor) / 255.f, (float)qBlue(fColor) / 255.f);
	}


	QRgb convertToRgb(QVector3D fColor){
		return qRgb((int)(255.f * fColor.x()), (int)(255.f * fColor.y()), (int)(255.f * fColor.z()));
	}


	QVector3D getPixel(QVector2D fPoint, const QImage& fImage){
		int _x = (int)fPoint.x();
		int _y = (int)fPoint.y();
		float _floorX = fPoint.x() - floor(fPoint.x());
		float _floorY = fPoint.y() - floor(fPoint.y());

		_x = std::max(std::min(_x, fImage.width() - 2), 0);
		_y = std::max(std::min(_y, fImage.height() - 2), 0);

		QVector3D _p0 = convertToVector3D(fImage.pixel(_x, _y));
		QVector3D _p1 = convertToVector3D(fImage.pixel(_x + 1, _y));
		QVector3D _p2 = convertToVector3D(fImage.pixel(_x, _y + 1));
		QVector3D _p3 = convertToVector3D(fImage.pixel(_x + 1, _y + 1));

		QVector3D _p4 = (1.f - _floorX) * _p0 + _floorX * _p1;
		QVector3D _p5 = (1.f - _floorX) * _p2 + _floorX * _p3;

		return (1.f - _floorY) * _p4 + _floorY * _p5;
	}


	QVector3D getPixel(int fX, int fY, const QImage& fImage){

		fX = std::max(std::min(fX, fImage.width() - 1), 0);
		fY = std::max(std::min(fY, fImage.height() - 1), 0);

		return convertToVector3D(fImage.pixel(fX, fY));
	}


	void gammaCorrection(QImage& fImage, float fGamma){

		for (int x = 0; x < fImage.width(); x++){
			for (int y = 0; y < fImage.height(); y++){

				QRgb _p = fImage.pixel(x, y);

				float _red = qRed(_p) / 255.f;
				float _green = qGreen(_p) / 255.f;
				float _blue = qBlue(_p) / 255.f;

				_red = pow(_red, 1.f / fGamma);
				_green = pow(_green, 1.f / fGamma);
				_blue = pow(_blue, 1.f / fGamma);

				fImage.setPixel(x, y, qRgb((int)(_red * 255.f), (int)(_green * 255.f), (int)(_blue * 255.f)));

			}
		}
	}


	void convertToShadeOfGrey(QImage& fImage){
		for (int x = 0; x < fImage.width(); x++){
			for (int y = 0; y < fImage.height(); y++){
				QRgb _p = fImage.pixel(x, y);

				int _v = (11 * qRed(_p) + 16 * qGreen(_p) + 5 * qBlue(_p)) / 32;

				fImage.setPixel(x, y, qRgb(_v, _v, _v));
			}
		}
	}


	QRgb antiAliasingPixel(int fX, int fY, const QImage& fImage){

		QVector2D _coord((float)fX, (float)fY);
		QVector3D _rgbNW = getPixel(_coord + QVector2D(-0.5f, -0.5f), fImage);
		QVector3D _rgbNE = getPixel(_coord + QVector2D(0.5f, -0.5f), fImage);
		QVector3D _rgbSW = getPixel(_coord + QVector2D(-0.5f, 0.5f), fImage);
		QVector3D _rgbSE = getPixel(_coord + QVector2D(0.5f, 0.5f), fImage);
		QVector3D _rgbM = getPixel(_coord, fImage);

		const QVector3D _luma(0.299, 0.587, 0.114);
		float _lumaNW = QVector3D::dotProduct(_rgbNW, _luma);
		float _lumaNE = QVector3D::dotProduct(_rgbNE, _luma);
		float _lumaSW = QVector3D::dotProduct(_rgbSW, _luma);
		float _lumaSE = QVector3D::dotProduct(_rgbSE, _luma);
		float _lumaM = QVector3D::dotProduct(_rgbM, _luma);

		float _lumaMin = std::min(_lumaM, std::min(std::min(_lumaNW, _lumaNE), std::min(_lumaSW, _lumaSE)));
		float _lumaMax = std::max(_lumaM, std::max(std::max(_lumaNW, _lumaNE), std::max(_lumaSW, _lumaSE)));

		QVector2D _dir;
		_dir.setX(-((_lumaNW + _lumaNE) - (_lumaSW + _lumaSE)));
		_dir.setY((_lumaNW + _lumaSW) - (_lumaNE + _lumaSE));

		float _dirReduce = std::max((_lumaNW + _lumaNE + _lumaSW + _lumaSE) * (0.25 * (1.0 / 8.0)), (1.0 / 128.0));

		float _rcpDirMin = 1.f / (std::min(abs(_dir.x()), abs(_dir.y())) + _dirReduce);
		_dir *= _rcpDirMin;

		_dir = QVector2D(std::max(std::min(8.f, _dir.x()), -8.f), std::max(std::min(8.f, _dir.y()), -8.f));


		QVector2D _pos1 = _coord + _dir * (1.0 / 3.0 - 0.5);
		QVector2D _pos2 = _coord + _dir * (2.0 / 3.0 - 0.5);
		QVector3D _rgbA = (getPixel(_pos1, fImage) + getPixel(_pos2, fImage)) / 2.f;

		_pos1 = _coord + _dir * (0.0 / 3.0 - 0.5);
		_pos2 = _coord + _dir * (3.0 / 3.0 - 0.5);
		QVector3D _rgbB = _rgbA / 2.f + (getPixel(_pos1, fImage) + getPixel(_pos2, fImage)) / 4.f;

		float _lumaB = QVector3D::dotProduct(_rgbA, _luma);

		if ((_lumaB < _lumaMin) || (_lumaB > _lumaMax)){
			return convertToRgb(_rgbA);
		}

		return convertToRgb(_rgbB);

	}


	std::unique_ptr<QImage> antiAliasing(const QImage& fImage){
		std::unique_ptr<QImage> _image(new QImage(fImage.width(), fImage.height(), QImage::Format_RGB888));

		for (int x = 0; x < fImage.width(); x++){
			for (int y = 0; y < fImage.height(); y++){
				QRgb _p = antiAliasingPixel(x, y, fImage);
				_image->setPixel(x, y, _p);

			}
		}

		return _image;
	}


}