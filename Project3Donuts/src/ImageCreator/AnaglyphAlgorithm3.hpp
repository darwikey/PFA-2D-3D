#ifndef ANAGLYPH_ALGO3_HPP
#define ANAGLYPH_ALGO3_HPP

#include "global.hpp"
#include "Anaglyph.hpp"


//! \class AnaglyphAlgorithm3
//! \brief Third algorithm to create an anaglyph
class AnaglyphAlgorithm3 : public Anaglyph{
	Q_OBJECT

protected:

	virtual void createWindow(bool fHasPreview = true) override;

	virtual std::unique_ptr<CreationFile> renderAnaglyph() override;

	void storePixelValue(QRgb fPixel, float *fRgb);

	void rgbToReducedInterval(float *fRgb);
	void reducedIntervalToRgb(float *fRgb);

	void rgbToHsl(float *fRgb, float *fHsl);
	void hslToRgb(float *fRgb, float *fHsl);

	void sRgbGamma(float *fHsl);
	void gammaCorrection(float *fHsl);

	void modifyLeftImage(float *fRgb);
	void modifyRightImage(float *fRgb);

private:

	static const float mLeftFilter[9];
	static const float mRightFilter[9];
};

#endif
