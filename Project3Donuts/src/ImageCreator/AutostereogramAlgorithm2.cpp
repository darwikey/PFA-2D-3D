#include "AutostereogramAlgorithm2.hpp"

void AutostereogramAlgorithm2::createWindow(bool fHasPreview){
	Autostereogram::createWindow(fHasPreview);
}

std::unique_ptr<CreationFile> AutostereogramAlgorithm2::render(){

	std::unique_ptr<QImage> _depthmap = this->getDepthMap();

	//TODO std::unique_ptr<QImage> _image = this->depthmapToAutostereogram(*_depthmap, 75,  );


	std::unique_ptr<CreationFile> _file(new CreationFile(CreationFile::Type::IMAGE));
	//TODO _file->pushImage(std::move(_image));

	return _file;
}

void AutostereogramAlgorithm2::colorBase(int fx, int fy) {
  switch (this->_TextureStyle) {
    int xpat, ypat ;
  case TEXTUREMAP :
    xpat = (fx/_oversampling) % _texture->width() ;
    ypat = fy % _texture->height() ;
    _red[fx] = qRed(_texture->pixel(xpat, ypat)) ;
    _green[fx] = qGreen(_texture->pixel(xpat, ypat)) ;
    _blue[fx] = qBlue(_texture->pixel(xpat, ypat)) ;
    break ;
  case RANDNB :
    _red[fx] = (random() & 1) * 255 ;
    _green[fx] = _red[fx] ;
    _blue[fx] = _red[fx] ;
    break ;
  case RANDGREY :
    _red[fx] = random() % 255 ;
    _green[fx] = _red[fx] ;
    _blue[fx] = _red[fx] ;
    break ;
  case RANDCOLOR :
    _red[fx] = random() % 255 ;
    _green[fx] = random() % 255 ;
    _blue[fx] = random() % 255 ;
    break ;
  }
}

void AutostereogramAlgorithm2::colorRandom(int fx) {
  switch (fTextureStyle) {

  case TEXTUREMAP :
    break ;
    
  case RANDNB :
    
    /* Because of resolution enhancement (which involves coloring real points with the average color of virtual points), black-and white images will actually be in shades of grey */
    
    _red[fx] = (random()&1) * 255 ;
    _green[fx] = _red[fx] ;
    _blue[fx] = _red[fx] ;
    break ;
    
  case RANDGREY :
    _red[fx] = random() %256 ;
    _green[fx] = _red[fx] ;
    _blue[fx] = _red[fx] ;
    break ;
    
  case RANDCOLOR :
    _red[fx] = random() %256;
    _green[fx] = random() %256;
    _blue[fx] = random() %256;
    break ;
   
  }
}

void AutostereogramAlgorithm2::colorPixel(int fx, int fy, int * LastLinked) {
  int xpat, ypat ;
  if (fx >= _center) {
    if (_sameLeft[fx] == fx) {
      if (_textureStyle == TEXTUREMAP) {
	if (*fLastLinked == (fx - 1)) {
	  _red[fx] = _red[fx - 1] ;
	  _green[fx] = _green[fx - 1] ;
	  _blue[fx] = _blue[fx - 1] ;
	}
	else {
	  xpat = (((fx + _poffset) % _maxsep)/_oversampling) % _texture->width() ;
	  ypat = (fy + ((fx - _center)/_maxsep) * _yShift) % _texture->height() ;
	  _red[fx] = qRed(_texture->pixel(xpat, ypat)) ;
	  _green[fx] = qGreen(_texture->pixel(xpat, ypat)) ;
	  _blue[fx] = qBlue(_texture->pixel(xpat, ypat)) ;
	}
      }
      else
	colorRandom(fx, _red, _green, _blue, _textureStyle) ;
    }
    
    else {
      _red[fx] = _red[_sameLeft[fx]] ;
      _green[fx] = _green[_sameLeft[fx]] ;
      _blue[fx] = _blue[_sameLeft[fx]] ;
      *fLastLinked = fx ;
    }
  }
  else {
    if (_sameRight[fx] == fx) {
      if (_textureStyle == TEXTUREMAP) {
	if (*fLastLinked == (fx + 1)) {
    	    _red[fx] = _red[fx + 1] ;
    	    _green[fx] = _green[fx + 1] ;
    	    _blue[fx] = _blue[fx + 1] ;
	}
	else {
	  xpat = (((fx + _poffset) % _maxsep)/_oversampling) % _texture->width() ;
	  ypat = (fy + ((_center - fx)/_maxsep + 1) * _yShift) % _texture->height() ;
	  _red[fx] = qRed(_texture->pixel(xpat, ypat)) ;
	  _green[fx] = qGreen(_texture->pixel(xpat, ypat)) ;
	  _blue[fx] = qBlue(_texture->pixel(xpat, ypat)) ;
	}
      }
      
      else
	colorRandom(fx) ;
    }
    else {
      _red[fx] = _red[_sameRight[fx]] ;
      _green[fx] = _green[_sameRight[fx]] ;
      _blue[fx] = _blue[_sameRight[fx]] ;
      *fLastLinked = fx ;
    }
  }
}
  
static std::vector<float> getDepth(QImage fImg) {
  const int myWidth = fImg.width() ;
  const int myHeight = fImg.height() ;
  std::vector<float> resultat (myWidth * myHeight, 0.) ;
  for (int i = 0 ; i < myHeight ; ++i) {
    for (int j = 0 ; j < myWidth ; ++j) {
      resultat[i * myWidth + j] = (float)qGray(fImg.pixel(j, i))/255. ;
    }
  }
  return resultat ;
}


std::unique_ptr<QImage> AutostereogramAlgorithm2::depthmapToAutostereogram(QImage * fImage, enum Texture fTextureStyle, char * fTexture) {

  /* Core variables */
  
  std::vector<float> floatDepthmap = getDepth(*fImage) ;

  int width = fImage->width() ;
  int height = fImage->height() ;

  std::unique_ptr<QImage> toReturn (new QImage(maxX, maxY, QImage::Format_RGB888));

  if (ftextureStyle == TEXTUREMAP)
    _texture->load(fTexture) ;
  
  int obsDist = _dpi * 12 ;
  int E = _dpi * 2.5 ;

  _yShift = _dpi/16 ;
  int maxdepth = _dpi * 12 ; // maximum depth used
  int maxsep = (int)(((long)E * maxdepth) / (maxdepth + obsDist)); 
  if (fTextureStyle == TEXTUREMAP && maxsep > _texture->width())
    std::cout << "Texture is too narrow (should be at least " << maxsep << " pixels large); results may be affected" << std::endl ;

  /* Oversampling */
  
  _oversampling = 4 ;
  int maxwidth = width * 6 ;
  int vwidth = width * _oversampling ;
  int vE = E * _oversampling ;
  _maxsep = maxsep * _oversampling ;
  
  /* Linking */
  
  _sameLeft = new vector<int>(maxwidth, 0) ;
  _sameRight = new vector<int>(maxwidth, 0) ;

  /* Coloration */
  
  int _red[maxwidth] ;
  int _green[maxwidth] ;
  int _blue[maxwidth] ;
  int center = (vwidth - vmaxsep)/2 ;
  int poffset = vmaxsep - (center % vmaxsep) ;
  
  for (int y = 0 ; y < height ; ++y) {
    
    int s = 0 ;
    int left, right ;
    
    for (int x = 0 ; x < vwidth ; ++x) {
      _sameLeft[x] = x ;
      _sameRight[x] = x ;
      colorBase(x, y, _red, _green, _blue, fTextureStyle, &_texture, oversampling) ;
    }

    float zValue ;
    
    for (int x = 0 ; x < vwidth ; ++x) {
      if (x % oversampling == 0) {

	/* zValue (and thus s, the stereo separation between points) will stay the same for all virtual points representing the same real point */
	
	zValue = floatDepthmap[caseXY(x/oversampling, y, width)] ;
	s = vE * ((1. - mu * zValue) / (2. - mu * zValue)) ;
      }

      left = x - (s + (s&y&1)) / 2;
      right = left + s;

      /* Linking points (with hidden surfaces removal) */
      
      bool isVisible = true ;

      if (left >= 0 && right < vwidth) {
	if (_sameLeft[right] != right) {
	  if (_sameLeft[right] < left) {
	    _sameRight[_sameLeft[right]] = _sameLeft[right] ;
	    _sameLeft[right] = right ;
	  }
	  else isVisible = false ;
	}

	if (_sameRight[left] != left) {
	  if (_sameRight[left] > right) {
	    _sameLeft[_sameRight[left]] = _sameRight[left] ;
	    _sameRight[left] = left ;
	  }
	  else isVisible = false ;
	}

	if (isVisible) {
	  _sameLeft[right] = left ;
	  _sameRight[left] = right ;
	}

      }

      /* Linking points without hidden surfaces removal */
	    
      // if (left >= 0 && right < vwidth) {
      // 	_sameLeft[right] = left ;
      // }
    }

    /* Coloring points according to the chosen option  */
    
    int lastLinked = -10 ;

    //    poffset = 0 ; center = 0 ; // test stuff w/o coloration from center
    for (int x = center - 1 ; x >= 0 ; --x) {
      colorPixel(x, y, &lastLinked) ;
    }

    lastLinked = -10 ;
    
    for (int x = center ; x < vwidth ; ++x) {
      colorPixel(x, y) ;
    }  


    /* Fusion of virtual pixels in order to obtain the final image */
    
    for (int x = 0 ; x < vwidth ; x += oversampling) {
      int red = 0, green = 0, blue = 0 ;
      for (int i = 0 ; i < oversampling ; ++i) {
	red += _red[x + i] ;
	green += _green[x + i] ;
	blue += _blue[x + i] ;
      }
      toReturn->setPixel(x/oversampling, y, qRgb(red/oversampling, green/oversampling, blue/oversampling)) ;
    }
  }  

  return toReturn ;
}
