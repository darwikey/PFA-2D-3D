#include "AutostereogramAlgorithm2.hpp"

AutostereogramAlgorithm2::AutostereogramAlgorithm2() :
msameLeft(0, 0),
msameRight(0, 0){
}


void AutostereogramAlgorithm2::createWindow(bool fHasPreview){
	Autostereogram::createWindow(fHasPreview);
}


std::unique_ptr<CreationFile> AutostereogramAlgorithm2::render(){
  
	std::unique_ptr<CreationFile> _file(new CreationFile(CreationFile::Type::IMAGE));
	
	if (mViewIsAutostereogram) {
	  std::unique_ptr<QImage> _image = this->depthmapToAutostereogram();
	  _file->pushImage(std::move(_image));
	}

	else {
	  std::unique_ptr<QImage> _depthMap = this->getDepthMap();
	  _depthMap->invertPixels();
	  _file->pushImage(std::move(_depthMap));
	}
	
	return _file;
}


void AutostereogramAlgorithm2::colorBase(int fx, int fy) {

	switch (this->mTextureStyle) {

		int xpat, ypat;

	case TEXTUREMAP:
		xpat = (fx / OVERSAMPLING) % mTexture.width();
		ypat = fy % mTexture.height();
		mRed[fx] = qRed(mTexture.pixel(xpat, ypat));
		mGreen[fx] = qGreen(mTexture.pixel(xpat, ypat));
		mBlue[fx] = qBlue(mTexture.pixel(xpat, ypat));
		break;

	case RANDNB:
		mRed[fx] = (rand() & 1) * 255;
		mGreen[fx] = mRed[fx];
		mBlue[fx] = mRed[fx];
		break;

	case RANDGREY:
		mRed[fx] = rand() % 255;
		mGreen[fx] = mRed[fx];
		mBlue[fx] = mRed[fx];
		break;

	case RANDCOLOR:
		mRed[fx] = rand() % 255;
		mGreen[fx] = rand() % 255;
		mBlue[fx] = rand() % 255;
		break;
	}
}


void AutostereogramAlgorithm2::colorPixel(int fx, int fy, int * fLastLinked) {

	int xpat, ypat;

	if (fx >= mcenter) {
		if (msameLeft[fx] == fx) {
			if (mTextureStyle == TEXTUREMAP) {
				if (*fLastLinked == (fx - 1)) {
					mRed[fx] = mRed[fx - 1];
					mGreen[fx] = mGreen[fx - 1];
					mBlue[fx] = mBlue[fx - 1];
				}

				else {
					xpat = (((fx + mpoffset) % mmaxsep) / OVERSAMPLING) % mTexture.width();
					ypat = (fy + ((fx - mcenter) / mmaxsep) * myShift) % mTexture.height();
					mRed[fx] = qRed(mTexture.pixel(xpat, ypat));
					mGreen[fx] = qGreen(mTexture.pixel(xpat, ypat));
					mBlue[fx] = qBlue(mTexture.pixel(xpat, ypat));
				}
			}

			else
				colorRandom(fx);

		}

		else {
			mRed[fx] = mRed[msameLeft[fx]];
			mGreen[fx] = mGreen[msameLeft[fx]];
			mBlue[fx] = mBlue[msameLeft[fx]];
			*fLastLinked = fx;
		}
	}

	else {
		if (msameRight[fx] == fx) {
			if (mTextureStyle == TEXTUREMAP) {
				if (*fLastLinked == (fx + 1)) {
					mRed[fx] = mRed[fx + 1];
					mGreen[fx] = mGreen[fx + 1];
					mBlue[fx] = mBlue[fx + 1];
				}

				else {
					xpat = (((fx + mpoffset) % mmaxsep) / OVERSAMPLING) % mTexture.width();
					ypat = (fy + ((mcenter - fx) / mmaxsep + 1) * myShift) % mTexture.height();
					mRed[fx] = qRed(mTexture.pixel(xpat, ypat));
					mGreen[fx] = qGreen(mTexture.pixel(xpat, ypat));
					mBlue[fx] = qBlue(mTexture.pixel(xpat, ypat));
				}
			}

			else
				colorRandom(fx);

		}

		else {
			mRed[fx] = mRed[msameRight[fx]];
			mGreen[fx] = mGreen[msameRight[fx]];
			mBlue[fx] = mBlue[msameRight[fx]];
			*fLastLinked = fx;
		}
	}
}


std::unique_ptr<QImage> AutostereogramAlgorithm2::depthmapToAutostereogram() {

	/* Core variables */
	std::unique_ptr<QImage> _depthMap = this->getDepthMap();
	std::vector<float> _floatDepthMap = getDepth(*(_depthMap));

	int _width = _depthMap->width();
	int _height = _depthMap->height();

	std::unique_ptr<QImage> toReturn(new QImage(_width, _height, QImage::Format_RGB888));

	if (mTextureStyle == TEXTUREMAP)
		mTexture.load(mTexturePath);

	int _obsDist = mResolution * 12;
	int _E = mResolution * 2.5;

	myShift = mResolution / 16;

	int _maxdepth = mResolution * 12; // maximum depth used
	int _maxsep = (int)(((long)_E * _maxdepth) / (_maxdepth + _obsDist));

	if (mTextureStyle == TEXTUREMAP && _maxsep > mTexture.width())
		std::cout << "Texture is too narrow (should be at least " << _maxsep << " pixels large); results may be affected" << std::endl;

	/* Oversampling */
	int _maxwidth = _width * 6;
	int _vwidth = _width * OVERSAMPLING;
	int _vE = _E * OVERSAMPLING;

	mmaxsep = _maxsep * OVERSAMPLING;

	/* Linking */
	msameRight.std::vector<int>::resize(_maxwidth);
	msameLeft.std::vector<int>::resize(_maxwidth);

	/* Coloration */

	mRed.std::vector<int>::resize(_maxwidth);
	mGreen.std::vector<int>::resize(_maxwidth);
	mBlue.std::vector<int>::resize(_maxwidth);

	mcenter = (_vwidth - mmaxsep) / 2;
	mpoffset = mmaxsep - (mcenter % mmaxsep);

	//	std::cout << "All variables succesfully initialized" << std::endl;

	for (int y = 0; y < _height; ++y) {

		int _s = 0;
		int _left, _right;

		/* Initialisation of the image : each pixel is linked with itself and the image is either completely random or set to the chosen texture */

		for (int x = 0; x < _vwidth; ++x) {
			msameLeft[x] = x;
			msameRight[x] = x;
			colorBase(x, y);
		}

		//std::cout << "Resulting image initialized" << std::endl;

		float _zValue = 0.f;

		for (int x = 0; x < _vwidth; ++x) {
			if (x % OVERSAMPLING == 0) {

				/*
					_zValue (and thus _s, the stereo separation between points) will stay the same for
					all virtual points representing the same real point
					*/

				_zValue = 1. - _floatDepthMap[Autostereogram::caseXY(x / OVERSAMPLING, y, _width)];
				_s = _vE * ((1. - MU * _zValue) / (2. - MU * _zValue));
			}

			_left = x - (_s + (_s&y & 1)) / 2;
			_right = _left + _s;

			/* Linking points (with hidden surfaces removal) */
			/* If a pair of pixels exists for a point of the 3D surface that is not visible, it will be unlinked */
			/* This is done by checking if a shorter link exists for a given pixel of the 2D image */

			bool _isVisible = true;

			//std::cout << "Beginning pixel linking...";

			if (_left >= 0 && _right < _vwidth) {
				if (msameLeft[_right] != _right) {
					if (msameLeft[_right] < _left) {
						msameRight[msameLeft[_right]] = msameLeft[_right];
						msameLeft[_right] = _right;
					}

					else _isVisible = false;
				}

				if (msameRight[_left] != _left) {
					if (msameRight[_left] > _right) {
						msameLeft[msameRight[_left]] = msameRight[_left];
						msameRight[_left] = _left;
					}

					else _isVisible = false;
				}

				if (_isVisible) {
					msameLeft[_right] = _left;
					msameRight[_left] = _right;
				}
			}

			//std::cout << "done." << std::endl;
		}

		/* Coloring points according to the chosen option */
		int _lastLinked = -10;

		//std::cout << "Coloring...";

		for (int x = mcenter - 1; x >= 0; --x) {
			colorPixel(x, y, &_lastLinked);
		}

		_lastLinked = -10;

		for (int x = mcenter; x < _vwidth; ++x) {
			colorPixel(x, y, &_lastLinked);
		}

		//std::cout << "done." << std::endl;

		/* Fusion of virtual pixels in order to obtain the final image */

		//std::cout << "Pixel fusion...";

		for (int x = 0; x < _vwidth; x += OVERSAMPLING) {
			int _red = 0, _green = 0, _blue = 0;
			for (int i = 0; i < OVERSAMPLING; ++i) {
				_red += mRed[x + i];
				_green += mGreen[x + i];
				_blue += mBlue[x + i];
			}

			toReturn->setPixel(x / OVERSAMPLING, y, qRgb(_red / OVERSAMPLING, _green / OVERSAMPLING, _blue / OVERSAMPLING));
		}

		//std::cout << "done." << std::endl;
	}

	return toReturn;
}
