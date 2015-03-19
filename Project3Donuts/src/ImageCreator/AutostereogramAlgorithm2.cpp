#include "AutostereogramAlgorithm2.hpp"

AutostereogramAlgorithm2::AutostereogramAlgorithm2() :
  msameLeft (0, 0),
  msameRight(0, 0)
{}

void AutostereogramAlgorithm2::createWindow(bool fHasPreview){
	Autostereogram::createWindow(fHasPreview);
}

std::unique_ptr<CreationFile> AutostereogramAlgorithm2::render(){

	std::unique_ptr<QImage> _depthmap = this->getDepthMap();

	std::unique_ptr<QImage> _image = this->depthmapToAutostereogram();
	std::unique_ptr<CreationFile> _file(new CreationFile(CreationFile::Type::IMAGE));
	_file->pushImage(std::move(_image));

	return _file;
}

void AutostereogramAlgorithm2::colorBase(int fx, int fy) {
  switch (this->mtextureStyle) {
    int xpat, ypat ;
  case TEXTUREMAP :
    xpat = (fx/moversampling) % mtexture->width() ;
    ypat = fy % mtexture->height() ;
    mred[fx] = qRed(mtexture->pixel(xpat, ypat)) ;
    mgreen[fx] = qGreen(mtexture->pixel(xpat, ypat)) ;
    mblue[fx] = qBlue(mtexture->pixel(xpat, ypat)) ;
    break ;
  case RANDNB :
    mred[fx] = (rand() & 1) * 255 ;
    mgreen[fx] = mred[fx] ;
    mblue[fx] = mred[fx] ;
    break ;
  case RANDGREY :
    mred[fx] = rand() % 255 ;
    mgreen[fx] = mred[fx] ;
    mblue[fx] = mred[fx] ;
    break ;
  case RANDCOLOR :
    mred[fx] = rand() % 255 ;
    mgreen[fx] = rand() % 255 ;
    mblue[fx] = rand() % 255 ;
    break ;
  }
}

void AutostereogramAlgorithm2::colorRandom(int fx) {
  switch (mtextureStyle) {

  case TEXTUREMAP :
    break ;
    
  case RANDNB :
    
    /* Because of resolution enhancement (which involves coloring real points with the average color of virtual points), black-and white images will actually be in shades of grey */
    
    mred[fx] = (rand()&1) * 255 ;
    mgreen[fx] = mred[fx] ;
    mblue[fx] = mred[fx] ;
    break ;
    
  case RANDGREY :
    mred[fx] = rand() %256 ;
    mgreen[fx] = mred[fx] ;
    mblue[fx] = mred[fx] ;
    break ;
    
  case RANDCOLOR :
    mred[fx] = rand() %256;
    mgreen[fx] = rand() %256;
    mblue[fx] = rand() %256;
    break ;
   
  }
}

void AutostereogramAlgorithm2::colorPixel(int fx, int fy, int * fLastLinked) {
  int xpat, ypat ;
  if (fx >= mcenter) {
    if (msameLeft[fx] == fx) {
      if (mtextureStyle == TEXTUREMAP) {
	if (*fLastLinked == (fx - 1)) {
	  mred[fx] = mred[fx - 1] ;
	  mgreen[fx] = mgreen[fx - 1] ;
	  mblue[fx] = mblue[fx - 1] ;
	}
	else {
	  xpat = (((fx + mpoffset) % mmaxsep)/moversampling) % mtexture->width() ;
	  ypat = (fy + ((fx - mcenter)/mmaxsep) * myShift) % mtexture->height() ;
	  mred[fx] = qRed(mtexture->pixel(xpat, ypat)) ;
	  mgreen[fx] = qGreen(mtexture->pixel(xpat, ypat)) ;
	  mblue[fx] = qBlue(mtexture->pixel(xpat, ypat)) ;
	}
      }
      else
	colorRandom(fx) ;
    }
    
    else {
      mred[fx] = mred[msameLeft[fx]] ;
      mgreen[fx] = mgreen[msameLeft[fx]] ;
      mblue[fx] = mblue[msameLeft[fx]] ;
      *fLastLinked = fx ;
    }
  }
  else {
    if (msameRight[fx] == fx) {
      if (mtextureStyle == TEXTUREMAP) {
	if (*fLastLinked == (fx + 1)) {
    	    mred[fx] = mred[fx + 1] ;
    	    mgreen[fx] = mgreen[fx + 1] ;
    	    mblue[fx] = mblue[fx + 1] ;
	}
	else {
	  xpat = (((fx + mpoffset) % mmaxsep)/moversampling) % mtexture->width() ;
	  ypat = (fy + ((mcenter - fx)/mmaxsep + 1) * myShift) % mtexture->height() ;
	  mred[fx] = qRed(mtexture->pixel(xpat, ypat)) ;
	  mgreen[fx] = qGreen(mtexture->pixel(xpat, ypat)) ;
	  mblue[fx] = qBlue(mtexture->pixel(xpat, ypat)) ;
	}
      }
      
      else
	colorRandom(fx) ;
    }
    else {
      mred[fx] = mred[msameRight[fx]] ;
      mgreen[fx] = mgreen[msameRight[fx]] ;
      mblue[fx] = mblue[msameRight[fx]] ;
      *fLastLinked = fx ;
    }
  }
}
  
std::unique_ptr<QImage> AutostereogramAlgorithm2::depthmapToAutostereogram() {

  /* Core variables */
  
  std::vector<float> floatDepthmap = getDepth(*(this->getDepthMap())) ;

  std::unique_ptr<QImage> fImage = this->depthmapToAutostereogram();
  
  int width = fImage->width() ;
  int height = fImage->height() ;

  std::unique_ptr<QImage> toReturn (new QImage(width, height, QImage::Format_RGB888));
  
  if (mtextureStyle == TEXTUREMAP)
    mtexture->load(mtexturePath) ;
  
  int obsDist = mdpi * 12 ;
  int E = mdpi * 2.5 ;

  myShift = mdpi/16 ;
  int maxdepth = mdpi * 12 ; // maximum depth used
  int maxsep = (int)(((long)E * maxdepth) / (maxdepth + obsDist)); 
  if (mtextureStyle == TEXTUREMAP && maxsep > mtexture->width())
    std::cout << "Texture is too narrow (should be at least " << maxsep << " pixels large); results may be affected" << std::endl ;

  /* Oversampling */
  
  int maxwidth = width * 6 ;
  int vwidth = width * moversampling ;
  int vE = E * moversampling ;
  mmaxsep = maxsep * moversampling ;
  
  /* Linking */

  msameRight.std::vector<int>::resize(maxwidth) ;
  msameLeft.std::vector<int>::resize(maxwidth) ;

  /* Coloration */
  
  mred.std::vector<int>::resize(maxwidth) ;
  mgreen.std::vector<int>::resize(maxwidth) ;
  mblue.std::vector<int>::resize(maxwidth) ;
  mcenter = (vwidth - mmaxsep)/2 ;
  mpoffset = mmaxsep - (mcenter % mmaxsep) ;
  
  for (int y = 0 ; y < height ; ++y) {
    
    int s = 0 ;
    int left, right ;

    /* Initialisation of the image : each pixel is linked with itself and the image is either completely random or set to the chosen texture */
    
    for (int x = 0 ; x < vwidth ; ++x) {
      msameLeft[x] = x ;
      msameRight[x] = x ;
      colorBase(x, y) ;
    }

    float zValue = 0.f ;
    
    for (int x = 0 ; x < vwidth ; ++x) {
      if (x % moversampling == 0) {

	/* zValue (and thus s, the stereo separation between points) will stay the same for all virtual points representing the same real point */
	
	zValue = floatDepthmap[Autostereogram::caseXY(x/moversampling, y, width)] ;
	s = vE * ((1. - mmu * zValue) / (2. - mmu * zValue)) ;
      }

      left = x - (s + (s&y&1)) / 2;
      right = left + s;

      /* Linking points (with hidden surfaces removal) */
      /* If a pair of pixels exists for a point of the 3D surface that is not visible, it will be unlinked */
      /* This is done by checking if a shorter link exists for a given pixel of the 2D image */
      
      bool isVisible = true ;

      if (left >= 0 && right < vwidth) {
	if (msameLeft[right] != right) {
	  if (msameLeft[right] < left) {
	    msameRight[msameLeft[right]] = msameLeft[right] ;
	    msameLeft[right] = right ;
	  }
	  else isVisible = false ;
	}

	if (msameRight[left] != left) {
	  if (msameRight[left] > right) {
	    msameLeft[msameRight[left]] = msameRight[left] ;
	    msameRight[left] = left ;
	  }
	  else isVisible = false ;
	}

	if (isVisible) {
	  msameLeft[right] = left ;
	  msameRight[left] = right ;
	}

      }

      /* Linking points without hidden surfaces removal */
	    
      // if (left >= 0 && right < vwidth) {
      // 	msameLeft[right] = left ;
      // }
    }

    /* Coloring points according to the chosen option  */
    
    int lastLinked = -10 ;

    for (int x = mcenter - 1 ; x >= 0 ; --x) {
      colorPixel(x, y, &lastLinked) ;
    }

    lastLinked = -10 ;
    
    for (int x = mcenter ; x < vwidth ; ++x) {
      colorPixel(x, y, &lastLinked) ;
    }  


    /* Fusion of virtual pixels in order to obtain the final image */
    
    for (int x = 0 ; x < vwidth ; x += moversampling) {
      int red = 0, green = 0, blue = 0 ;
      for (int i = 0 ; i < moversampling ; ++i) {
	red += mred[x + i] ;
	green += mgreen[x + i] ;
	blue += mblue[x + i] ;
      }
      toReturn->setPixel(x/moversampling, y, qRgb(red/moversampling, green/moversampling, blue/moversampling)) ;
    }
  }  

  return toReturn ;
}
