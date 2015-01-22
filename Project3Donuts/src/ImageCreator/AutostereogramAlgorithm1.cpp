#include "AutostereogramAlgorithm1.hpp"

#define round(X) (int)((X)+0.5)
#define mu (1/3.0)
#define E round(2.5*DPI)//to change : separation between eyes in inches
#define separation(Z) round(1-mu*Z)*E/(2-mu*Z)

float depth(Pixel * p) {
  return (float)p.getR()/255.0 ;
}    

float depth(PixelTab * pixtab, int x, int y) {
  Pixel p = pixtab.getPixel(x, y) ;
  return depth(&p) ;
}


/*
 * This is a retranscription in C++ of the algorithm of Harold W. Thimbleby, Stuart Inglis and Ian H. Witten
 * as presented in their article "Displaying 3D Images : Algorithm for Single Image Random Dot Stereograms" which has
 * been publicated in IEEE Computer in 1994
 */
std::vector<Image*> AutostereogramAlgorithm1::create(std::vector<PixelTab*> fToUse, int DPI){
  // First position of fToUse will contain the depth map created by Creator
  PixelTab *depthMap = fToUse[0];
  int maxX = depthMap.size();
  int maxY = depthMap[0].size();

  float floatDepthMap[maxX][maxY] ;
  for (int y = 0 ; y < maxY ; ++y) {
    for (int x = 0 ; x < maxX ; ++x) {
      floatDepthMap[x][y] = depth(depthMap, x, y) ;
    }
  }
  
  PixelTab *toReturn = new PixelTab(maxX,maxY);

  for (int y = 0 ; y < maxY ; y++){
    int pix[maxX];
    int same[maxX];
    int s;
    int left,right;

    for (int x = 0 ; x < maxX ; x++)
      same[x] = x;

    for (int x = 0 ; x < maxX ; x++){
      s = separation(floatDepthMap[x][y]);
      left = x - (s + (s&y&1)) / 2;
      right = left + s;
      if (0 <= left && right < maxX){
	int visible;
	int t = 1;
	float zt;

	do {
	  zt = floatDepthMap[x][y] + 2 * (2 - mu * floatDepthMap[x][y])*t/(mu*E);
	  visible = floatDepthMap[x-t][y] < zt && Z[x+t][y] < zt;
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



    for (x = maxX - 1 ; x >= 0 ; x--){
      if (same[x] == x)
	pix[x]=random()&1;
      else
	pix[x] = pix[same[x]];
      Pixel pix = new Pixel(same[x],same[x],same[x]);
      toReturn.setPixel(pix,x,y);
    }
  }

  std::vector v;
  v.push_back(toReturn);
  return v;
}

// test

// int main() {
//   PixelTab * pixtab = new PixelTab(50, 20) ;
//   return 0 ;
// }
