#include "AutostereogramAlgorithm2.hpp"

#define mu (1./3.)

void AutostereogramAlgorithm3::colorBase(int fx, int fy, int * fRed, int * fGreen, int * fBlue, enum Texture fTextureStyle, QImage * fTexture, int fOversamp) {
  switch (fTextureStyle) {
    int xpat, ypat ;
  case TEXTUREMAP :
    xpat = (fx/fOversamp) % fTexture->width() ;
    ypat = fy % fTexture->height() ;
    fRed[fx] = qRed(fTexture->pixel(xpat, ypat)) ;
    fGreen[fx] = qGreen(fTexture->pixel(xpat, ypat)) ;
    fBlue[fx] = qBlue(fTexture->pixel(xpat, ypat)) ;
    break ;
  case RANDNB :
    fRed[fx] = (rand() & 1) * 255 ;
    fGreen[fx] = fRed[fx] ;
    fBlue[fx] = fRed[fx] ;
    break ;
  case RANDGREY :
    fRed[fx] = rand() % 255 ;
    fGreen[fx] = fRed[fx] ;
    fBlue[fx] = fRed[fx] ;
    break ;
  case RANDCOLOR :
    fRed[fx] = rand() % 255 ;
    fGreen[fx] = rand() % 255 ;
    fBlue[fx] = rand() % 255 ;
    break ;
  }
}

void AutostereogramAlgorithm3::colorRandom(int fx, int fRed[], int * fGreen, int * fBlue, enum Texture fTextureStyle) {
  switch (fTextureStyle) {

  case TEXTUREMAP :
    break ;
    
  case RANDNB :
    
    /* Because of resolution enhancement (which involves coloring real points with the average color of virtual points), black-and white images will actually be in shades of grey */
    
    fRed[fx] = (random()&1) * 255 ;
    fGreen[fx] = fRed[fx] ;
    fBlue[fx] = fRed[fx] ;
    break ;
    
  case RANDGREY :
    fRed[fx] = random() %256 ;
    fGreen[fx] = fRed[fx] ;
    fBlue[fx] = fRed[fx] ;
    break ;
    
  case RANDCOLOR :
    fRed[fx] = random() %256;
    fGreen[fx] = random() %256;
    fBlue[fx] = random() %256;
    break ;
   
  }
}
void AutostereogramAlgorithm3::colorPixel(int fx, int fy, int * fRed, int * fGreen, int * fBlue, enum Texture fTextureStyle, QImage * fTexture, int * fSameLeft, int * fSameRight, int fOversamp, int fMaxsep, int fPoffset, int fCenter, int * fLastLinked, int fyShift) {
  int xpat, ypat ;
  if (fx >= fCenter) {
    if (fSameLeft[fx] == fx) {
      if (fTextureStyle == TEXTUREMAP) {
	if (*fLastLinked == (fx - 1)) {
	  fRed[fx] = fRed[fx - 1] ;
	  fGreen[fx] = fGreen[fx - 1] ;
	  fBlue[fx] = fBlue[fx - 1] ;
	}
	else {
	  xpat = (((fx + fPoffset) % fMaxsep)/fOversamp) % fTexture->width() ;
	  ypat = (fy + ((fx - fCenter)/fMaxsep) * fyShift) % fTexture->height() ;
	  fRed[fx] = qRed(fTexture->pixel(xpat, ypat)) ;
	  fGreen[fx] = qGreen(fTexture->pixel(xpat, ypat)) ;
	  fBlue[fx] = qBlue(fTexture->pixel(xpat, ypat)) ;
	}
      }
      else
	colorRandom(fx, fRed, fGreen, fBlue, fTextureStyle) ;
    }
    
    else {
      fRed[fx] = fRed[fSameLeft[fx]] ;
      fGreen[fx] = fGreen[fSameLeft[fx]] ;
      fBlue[fx] = fBlue[fSameLeft[fx]] ;
      *fLastLinked = fx ;
    }
  }
  else {
    if (fSameRight[fx] == fx) {
      if (fTextureStyle == TEXTUREMAP) {
	if (*fLastLinked == (fx + 1)) {
    	    fRed[fx] = fRed[fx + 1] ;
    	    fGreen[fx] = fGreen[fx + 1] ;
    	    fBlue[fx] = fBlue[fx + 1] ;
	}
	else {
	  xpat = (((fx + fPoffset) % fMaxsep)/fOversamp) % fTexture->width() ;
	  ypat = (fy + ((fCenter - fx)/fMaxsep + 1) * fyShift) % fTexture->height() ;
	  fRed[fx] = qRed(fTexture->pixel(xpat, ypat)) ;
	  fGreen[fx] = qGreen(fTexture->pixel(xpat, ypat)) ;
	  fBlue[fx] = qBlue(fTexture->pixel(xpat, ypat)) ;
	}
      }
      
      else
	colorRandom(fx, fRed, fGreen, fBlue, fTextureStyle) ;
    }
    else {
      fRed[fx] = fRed[fSameRight[fx]] ;
      fGreen[fx] = fGreen[fSameRight[fx]] ;
      fBlue[fx] = fBlue[fSameRight[fx]] ;
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

static int caseXY(int x, int y, int width) {
  return y * width + x ;
}

std::vector<QImage> AutostereogramAlgorithm3::create(int fDPI, int fHeight, int fWidth) {
  std::vector<QImage> toReturn ;
  return toReturn ;
} ;

std::vector<QImage> AutostereogramAlgorithm3::dummyCreate(QImage * fImage, int fDPI, enum Texture fTextureStyle, char * fTexture) {
  return depthmapToAutostereogram(fImage, fDPI, fTextureStyle, fTexture) ;
}

std::vector<QImage> AutostereogramAlgorithm3::depthmapToAutostereogram(QImage * fImage, int fDPI, enum Texture fTextureStyle, char * fTexture) {

  /* Core variables */
  
  std::vector<float> floatDepthmap = getDepth(*fImage) ;

  int width = fImage->width() ;
  int height = fImage->height() ;

  QImage toReturn(width, height, QImage::Format_RGB888) ;

  QImage pattern ;
  if (fTextureStyle == TEXTUREMAP)
    pattern.load(fTexture) ;
  
  int obsDist = fDPI * 12 ;
  int E = fDPI * 2.5 ;

  int yShift = fDPI/16 ;
  int maxdepth = fDPI * 12 ; // maximum depth used
  int maxsep=(int)(((long)E * maxdepth) / (maxdepth + obsDist)); 
  if (fTextureStyle == TEXTUREMAP && maxsep > pattern.width())
    std::cout << "Pattern is too narrow (should be at least " << maxsep << " pixels large); results may be affected" << std::endl ;

  /* Oversampling */
  
  int oversampling = 4 ;
  int maxwidth = width * 6 ;
  int vwidth = width * oversampling ;
  int vE = E * oversampling ;
  int vmaxsep = maxsep * oversampling ;
  
  /* Linking */
  
  int sameL[maxwidth] ;
  int sameR[maxwidth] ;

  /* Coloration */
  
  int pixR[maxwidth] ;
  int pixG[maxwidth] ;
  int pixB[maxwidth] ;
  int center = (vwidth - vmaxsep)/2 ;
  int poffset = vmaxsep - (center % vmaxsep) ;
  
  for (int y = 0 ; y < height ; ++y) {
    
    int s = 0 ;
    int left, right ;
    
    for (int x = 0 ; x < vwidth ; ++x) {
      sameL[x] = x ;
      sameR[x] = x ;
      colorBase(x, y, pixR, pixG, pixB, fTextureStyle, &pattern, oversampling) ;
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
	if (sameL[right] != right) {
	  if (sameL[right] < left) {
	    sameR[sameL[right]] = sameL[right] ;
	    sameL[right] = right ;
	  }
	  else isVisible = false ;
	}

	if (sameR[left] != left) {
	  if (sameR[left] > right) {
	    sameL[sameR[left]] = sameR[left] ;
	    sameR[left] = left ;
	  }
	  else isVisible = false ;
	}

	if (isVisible) {
	  sameL[right] = left ;
	  sameR[left] = right ;
	}

      }

      /* Linking points without hidden surfaces removal */
	    
      // if (left >= 0 && right < vwidth) {
      // 	sameL[right] = left ;
      // }
    }

    /* Coloring points according to the chosen option  */
    
    int lastLinked = -10 ;

    //    poffset = 0 ; center = 0 ; // test stuff w/o coloration from center
    for (int x = center - 1 ; x >= 0 ; --x) {
      colorPixel(x, y, pixR, pixG, pixB, fTextureStyle, &pattern, sameL, sameR, oversampling, vmaxsep, poffset, center, &lastLinked, yShift) ;
    }

    lastLinked = -10 ;
    
    for (int x = center ; x < vwidth ; ++x) {
      colorPixel(x, y, pixR, pixG, pixB, fTextureStyle, &pattern, sameL, sameR, oversampling, vmaxsep, poffset, center, &lastLinked, yShift) ;
    }  

    
    for (int x = 0 ; x < vwidth ; x += oversampling) {
      int red = 0, green = 0, blue = 0 ;
      for (int i = 0 ; i < oversampling ; ++i) {
	red += pixR[x + i] ;
	green += pixG[x + i] ;
	blue += pixB[x + i] ;
      }
      toReturn.setPixel(x/oversampling, y, qRgb(red/oversampling, green/oversampling, blue/oversampling)) ;
    }
  }  

  std::vector<QImage> v ;
  v.push_back(toReturn);
  return v ;
}
