#ifndef AUTOSTEREOGRAM_ALGO3_HPP
#define AUTOSTEREOGRAM_ALGO3_HPP

#include "global.hpp"

#include "Autostereogram.hpp"


// ! \class AutostereogramAlgorithm2
// ! \brief First algorithm to create an autostereogram
class AutostereogramAlgorithm2 : public Autostereogram {
	Q_OBJECT
public:


protected:
	virtual void createWindow(bool fHasPreview = true) override;

	virtual std::unique_ptr<CreationFile> render() override;

	
private:
	void colorBase(int fx, int fy, std::vector<int>& fRed, std::vector<int>& fGreen, std::vector<int>& fBlue, enum Texture fTextureStyle, QImage * fTexture, int fOversamp);

	std::unique_ptr<QImage> depthmapToAutostereogram(const QImage& fDepthmap, int fDPI, enum Texture fTextureStyle, char * fTexture) ; 
	
	void colorPixel(int fx, int fy, std::vector<int>& fRed, std::vector<int>& fGreen, std::vector<int>& fBlue, enum Texture fTextureStyle, QImage * fTexture, std::vector<int>& fSameLeft, std::vector<int>& fSameRight, int fOversamp, int fMaxsep, int fPoffset, int fCenter, int * fLastLinked, int fyShift);
	
	void colorRandom(int fx, std::vector<int>& fRed, std::vector<int>& fGreen, std::vector<int>& fBlue, enum Texture fTextureStyle);

	int caseXY(int x, int y, int width);


	const int oversampling = 4;
	const float mu = (1.f / 3.f);
};
#endif
