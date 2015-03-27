#ifndef ANAGLYPH_ALGO2_HPP
#define ANAGLYPH_ALGO2_HPP

#include "global.hpp"
#include "Anaglyph.hpp"


//! \class AnaglyphAlgorithm2
//! \brief Secound algorithm to create an anaglyph
class AnaglyphAlgorithm2 : public Anaglyph{
	Q_OBJECT

protected:

	virtual void createWindow(bool fHasPreview = true) override;

	virtual std::unique_ptr<CreationFile> renderAnaglyph() override;

	void modifyLeftImage (float *fRgb);
	void modifyRightImage(float *fRgb);

	void applyGamma      (QRgb fPixel, float *fRgb);
	QRgb applyGammaRevert(float *fRgb);

	QLabel*  mGammaFilterLabel  = nullptr;
	QSlider* mGammaFilterSlider = nullptr; 
	
private:

	static const float mLeftFilter[9];

	static const float mRightFilter[9];

	float mGammaFilter = 1.f;

private slots:
	void changeGammaFilter(int fGammaFilter);
};

#endif
