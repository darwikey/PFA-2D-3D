#include "AutostereogramAlgorithm1.hpp"


void AutostereogramAlgorithm1::createWindow(){
	Autostereogram::createWindow();
}


std::shared_ptr<QImage> AutostereogramAlgorithm1::render(){

	float _DPI = 75.f;
	/*if ( == COMPUTER_RESO)
		_DPI = 75;
	else if (fReso == PRINT_RESO)
		_DPI = 300;*/
	int _E = this->round(2.5 * _DPI);

	std::shared_ptr<QImage> _image = this->depthmapToAutostereogram(this->getDepthMap(), _E);

	return _image;
}


int AutostereogramAlgorithm1::round(float fX) {
	return (int)(fX + 0.5);
}


int AutostereogramAlgorithm1::caseXY(int fx, int fy, int fwidth) {
	return fy * fwidth + fx;
}


int AutostereogramAlgorithm1::separation(float fZ, int fE) {
	return round(1 - mu * fZ) * fE / (2 - mu * fZ);
}


std::vector<float> AutostereogramAlgorithm1::getDepth(std::shared_ptr<QImage> fImg) {
	int _width = fImg->width();
	int _height = fImg->height();

	std::vector<float> resultat(_width * _height, 0.);
	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			resultat[i * _width + j] = qGray(fImg->pixel(j, i)) / 255.f;
		}
	}
	return resultat;
}

/* This is a retranscription in C++ of the algorithm of Harold W. Thimbleby, Stuart Inglis and Ian H. Witten */
/* as presented in their article "Displaying 3D Images : Algorithm for Single Image Random Dot Stereograms" which has */
/* been publicated in IEEE Computer in 1994 */
std::shared_ptr<QImage> AutostereogramAlgorithm1::depthmapToAutostereogram(std::shared_ptr<QImage> fDepthmap, int fE) {
	const int maxX = fDepthmap->width();
	const int maxY = fDepthmap->height();

	std::vector<float> floatDepthMap = getDepth(fDepthmap);

	std::shared_ptr<QImage> toReturn (new QImage(maxX, maxY, QImage::Format_RGB888));

	for (int y = 0; y < maxY; y++){
		int* pix = new int[maxX];
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
			if (same[x] == x)
				pix[x] = rand() & 1;
			else
				pix[x] = pix[same[x]];
			int mCouleur = pix[x] * 255;
			toReturn->setPixel(x, y, qRgb(mCouleur, mCouleur, mCouleur));
		}

		delete[] same;
		delete[] pix;
	}

	return toReturn;
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
