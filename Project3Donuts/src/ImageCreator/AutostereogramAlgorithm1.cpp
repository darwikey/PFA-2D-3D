#include "AutostereogramAlgorithm1.hpp"
#include <QLabel>

static const float mu = 1./3. ;

int AutostereogramAlgorithm1::round(float fX) {
  return (int)(fX + 0.5) ;
}

int AutostereogramAlgorithm1::caseXY(int fx, int fy, int fwidth) {
  return fy * fwidth + fx ;
}

int AutostereogramAlgorithm1::separation(float fZ, int fE) {
  return round(1 - mu * fZ) * fE / (2 - mu * fZ) ;
}

std::vector<float> getDepth(QImage fImg) {
  int myWidth = fImg.width() ;
  int myHeight = fImg.height() ;
  std::vector<float> resultat (myWidth * myHeight, 0.) ;
  for (int i = 0 ; i < myHeight ; ++i) {
    for (int j = 0 ; j < myWidth ; ++j) {
      resultat[i * myWidth + j] = 1. - qGray(fImg.pixel(j, i))/255. ;
    }
  }
  return resultat ;
}

/* This is a retranscription in C++ of the algorithm of Harold W. Thimbleby, Stuart Inglis and Ian H. Witten */
/* as presented in their article "Displaying 3D Images : Algorithm for Single Image Random Dot Stereograms" which has */
/* been publicated in IEEE Computer in 1994 */
// void AutostereogramAlgorithm1 create(float fPhysicalLength, float fPhysicalWidth, DPI fReso);
  /* First position of fToUse will contain the depth map created by Creator */
/*  int _DPI;
  if (fReso == COMPUTER_RESO)
      _DPI = 75;
  else if (fReso == PRINT_RESO)
      _DPI = 300;
  int E = round(2.5 * _DPI) ;
  QImage *depthMap ;
  //todo : relier au reste du projet
  mPixelTable = depthmapToAutostereogram(depthMap, E) ;
}
*/
std::vector<QImage> AutostereogramAlgorithm1::depthmapToAutostereogram(QImage * fDepthmap, int fE) {
  int maxX = fDepthmap->width() ;
  int maxY = fDepthmap->height() ;

  std::vector<float> floatDepthMap = getDepth(*fDepthmap) ;
  
  QImage *toReturn = new QImage(maxX, maxY, QImage::Format_RGB888);

  for (int y = 0 ; y < maxY ; y++){
    int* pix = new int[maxX];
    int* same = new int[maxX];
    int s;
    int left,right;

    for (int x = 0 ; x < maxX ; x++)
      same[x] = x;

    for (int x = 0 ; x < maxX ; x++){
      s = AutostereogramAlgorithm1::separation(floatDepthMap[caseXY(x, y, maxX)], fE);
      left = x - (s + (s&y&1)) / 2;
      right = left + s;
      if (0 <= left && right < maxX){
	int visible;
	int t = 1;
	float zt;

	do {
	  zt = floatDepthMap[caseXY(x, y, maxX)]
	    + 2 * (2 - mu * floatDepthMap[caseXY(x, y, maxX)])*t/(mu*fE);
	  visible = (floatDepthMap[caseXY(x - t, y, maxX)] < zt)
	    && (floatDepthMap[caseXY(x + t, y, maxX)] < zt) ;
	  t++;
	} while (visible && zt<1);

	if (visible){
	  int k;
	  for (k=same[left];k != left && k!=right;k=same[left])
	    if (k<right)
	      left = k;
	    else{
	      left = right;
	      right = k;
	    }
	  same[left]=right;
	}
      }
    }

    for (int x = maxX - 1 ; x >= 0 ; x--){
      if (same[x] == x)
	pix[x] = rand() & 1;
      else
	pix[x] = pix[same[x]];
      int mCouleur = pix[x] * 255 ;
      toReturn->setPixel(x, y, qRgb(mCouleur, mCouleur, mCouleur));
    }
  }

  std::vector<QImage> v;
  v.push_back(*toReturn);
  return v;
}

// int main(int argc, char ** argv) {
//   QImage depthtest ;
//   if (!depthtest.load("../../../cahierDesCharges/cartePronfondeurs.png"))
//     std::cout << "impossible de trouver l'image" << endl ;
//   else {
//     QImage out = depthmapToAutostereogram(depthtest)[0] ;
//     QLabel mylabel ;
//     mylabel.setPixmap(QPixmap::fronmImage(myImage));
//     mylabel.show() ;
//   }
//   return 0 ;
// }
