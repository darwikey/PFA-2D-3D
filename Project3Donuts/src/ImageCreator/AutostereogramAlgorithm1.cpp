#include "AutostereogramAlgorithm1.hpp"


void AutostereogramAlgorithm1::createWindow(bool fHasPreview){
  Autostereogram::createWindow(fHasPreview);
}


std::unique_ptr<CreationFile> AutostereogramAlgorithm1::render(){

  float _DPI = 75.f;
  //TODO
  /*if ( == COMPUTER_RESO)
    _DPI = 75;
    else if (fReso == PRINT_RESO)
    _DPI = 300;*/
  int _E = this->round(2.5 * _DPI);

  std::unique_ptr<QImage> _depthmap = this->getDepthMap();
  std::unique_ptr<QImage> _image = this->depthmapToAutostereogram(*_depthmap, _E);


  std::unique_ptr<CreationFile> _file(new CreationFile(CreationFile::Type::IMAGE));
  _file->pushImage(std::move(_image));
  _file->pushImage(std::move(_depthmap));

  return _file;
}


int AutostereogramAlgorithm1::round(float fX) {
  return (int)(fX + 0.5);
}


int AutostereogramAlgorithm1::separation(float fZ, int fE) {
  return round(1 - mu * fZ) * fE / (2 - mu * fZ);
}


/* This is a retranscription in C++ of the algorithm of Harold W. Thimbleby, Stuart Inglis and Ian H. Witten */
/* as presented in their article "Displaying 3D Images : Algorithm for Single Image Random Dot Stereograms" which has */
/* been publicated in IEEE Computer in 1994 */
std::unique_ptr<QImage> AutostereogramAlgorithm1::depthmapToAutostereogram(const QImage& fDepthmap, int fE) {
  const int maxX = fDepthmap.width();
  const int maxY = fDepthmap.height();

  mred.std::vector<int>::resize(maxX) ;
  mgreen.std::vector<int>::resize(maxX) ;
  mblue.std::vector<int>::resize(maxX) ;

  if (mTextureStyle == TEXTUREMAP) {
    if (mTexturePath != nullptr) {
      std::cout << "Texture at " << mTexturePath.toUtf8().constData() << std::endl ;
      mTexture.load(mTexturePath) ;
    }
    else {
      std::cout << "No texture selected; switching to random colors" << std::endl ;
      mTextureStyle = RANDCOLOR ;
    }
  }

  
  std::vector<float> floatDepthMap = getDepth(fDepthmap);

  std::unique_ptr<QImage> toReturn (new QImage(maxX, maxY, QImage::Format_RGB888));

  for (int y = 0; y < maxY; y++){
    int* same = new int[maxX];
    int s;
    int left, right;

    for (int x = 0; x < maxX; x++)
      same[x] = x;

    for (int x = 0; x < maxX; x++){
      s = this->separation(floatDepthMap[caseXY(x, y, maxX)], fE);
      left = x - (s + (s&y & 1)) / 2;
      right = left + s;
      if (0 <= left && right < maxX){
	int visible;
	int t = 1;
	float zt;

	do {
	  zt = floatDepthMap[caseXY(x, y, maxX)]
	    + 2 * (2 - mu * floatDepthMap[caseXY(x, y, maxX)])*t / (mu*fE);
	  visible = (floatDepthMap[caseXY(x - t, y, maxX)] < zt)
	    && (floatDepthMap[caseXY(x + t, y, maxX)] < zt);
	  t++;
	} while (visible && zt < 1);

	if (visible){
	  int k;
	  for (k = same[left]; k != left && k != right; k = same[left])
	    if (k < right)
	      left = k;
	    else{
	      left = right;
	      right = k;
	    }
	  same[left] = right;
	}
      }
    }

    for (int x = maxX - 1; x >= 0; x--){
      if (same[x] == x) {
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
	mred[x] = mred[same[x]];
	mgreen[x] = mgreen[same[x]];
	mblue[x] = mblue[same[x]];
      }
      toReturn->setPixel(x, y, qRgb(mred[x], mgreen[x], mblue[x]));
    }

    delete[] same;
  }

  return toReturn;
}

