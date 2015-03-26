#include "AutostereogramAlgorithm1.hpp"


void AutostereogramAlgorithm1::createWindow(bool fHasPreview){
  Autostereogram::createWindow(fHasPreview);
}


std::unique_ptr<CreationFile> AutostereogramAlgorithm1::render(){

  float _DPI = 75.f;

  int _E = this->round(2.5 * _DPI);

  std::unique_ptr<QImage> _depthmap = this->getDepthMap();
  std::unique_ptr<QImage> _image = this->depthmapToAutostereogram(*_depthmap, _E);


  std::unique_ptr<CreationFile> _file(new CreationFile(CreationFile::Type::IMAGE));
  _file->pushImage(std::move(_image));

  return _file;
}


int AutostereogramAlgorithm1::round(float fX) {
  return (int)(fX + 0.5);
}


int AutostereogramAlgorithm1::separation(float fZ, int fE) {
  return round(1.f - MU * fZ) * fE / (2.f - MU * fZ);
}


/* This is a retranscription in C++ of the algorithm of Harold W. Thimbleby, Stuart Inglis and Ian H. Witten */
/* as presented in their article "Displaying 3D Images : Algorithm for Single Image Random Dot Stereograms" which has */
/* been publicated in IEEE Computer in 1994 */
std::unique_ptr<QImage> AutostereogramAlgorithm1::depthmapToAutostereogram(const QImage& fDepthmap, int fE) {
  const int _maxX = fDepthmap.width();
  const int _maxY = fDepthmap.height();

  mred.std::vector<int>::resize(_maxX) ;
  mgreen.std::vector<int>::resize(_maxX) ;
  mblue.std::vector<int>::resize(_maxX) ;

  if (mTextureStyle == TEXTUREMAP) {
    bool _isLoaded = (mTexturePath != nullptr) && mTexture.load(mTexturePath) ;
    if (!_isLoaded) {
      std::cout << "Impossible to load selected texture; switching to random colors" << std::endl ;
      mTextureStyle = RANDCOLOR ;
    }
  }

  
  std::vector<float> _floatDepthMap = getDepth(fDepthmap);

  std::unique_ptr<QImage> _toReturn (new QImage(_maxX, _maxY, QImage::Format_RGB888));

  for (int y = 0; y < _maxY; y++){
    int* _same = new int[_maxX];
    int _s;
    int _left, _right;

    for (int x = 0; x < _maxX; x++)
      _same[x] = x;

    for (int x = 0; x < _maxX; x++){
      _s = this->separation(_floatDepthMap[caseXY(x, y, _maxX)], fE);
      _left = x - (_s + (_s&y&1)) / 2;
      _right = _left + _s;
      if (0 <= _left && _right < _maxX){
	bool _visible;
	int t = 1;
	float _zt;

	do {
	  _zt = _floatDepthMap[caseXY(x, y, _maxX)]
	    + 2 * (2 - MU * _floatDepthMap[caseXY(x, y, _maxX)]) * t / (MU * fE);
	  _visible = (_floatDepthMap[caseXY(x - t, y, _maxX)] < _zt)
	    && (_floatDepthMap[caseXY(x + t, y, _maxX)] < _zt);
	  t++;
	} while (_visible && _zt < 1);

	if (_visible){
	  
	  for (int k = _same[_left]; k != _left && k != _right; k = _same[_left])
	    if (k < _right)
	      _left = k;
	    else{
	      _left = _right;
	      _right = k;
	    }
	  _same[_left] = _right;
	}
      }
    }

    for (int x = _maxX - 1; x >= 0; x--){
      if (_same[x] == x) {
	if (mTextureStyle != TEXTUREMAP)
	  colorRandom(x) ;
	else {
	  int _xt = x % mTexture.width() ;
	  int _yt = y % mTexture.height() ;
	  mred[x] = qRed(mTexture.pixel(_xt, _yt)) ;
	  mgreen[x] = qGreen(mTexture.pixel(_xt, _yt)) ;
	  mblue[x] = qBlue(mTexture.pixel(_xt, _yt)) ;
	}
      }
      else {
	mred[x] = mred[_same[x]];
	mgreen[x] = mgreen[_same[x]];
	mblue[x] = mblue[_same[x]];
      }
      _toReturn->setPixel(x, y, qRgb(mred[x], mgreen[x], mblue[x]));
    }

    delete[] _same;
  }

  return _toReturn;
}

