#ifndef ANAGLYPH_ALGO2_HPP
#define ANAGLYPH_ALGO2_HPP

#include "global.hpp"
#include "Anaglyph.hpp"


// ! \class AnaglyphAlgo2
// ! \brief First algorithm to create an anaglyph
class AnaglyphAlgorithm2 : public Anaglyph{
	Q_OBJECT

protected:

	virtual void createWindow(bool fHasPreview = true) override;

	virtual std::unique_ptr<CreationFile> render() override;

	void modifyLeftImage (float *fRgb);
	void modifyRightImage(float *fRgb);

	void applyGamma      (QRgb fPixel, float *fRgb);
	QRgb applyGammaRevert(float *fRgb);

	QLabel*  mGammaFilterLabel  = nullptr;
	QSlider* mGammaFilterSlider = nullptr; 
	
private:

	float mLeftFilter[9] = { 0.437,  0.449,  0.164,
													-0.062, -0.062, -0.024,
													-0.048, -0.050, -0.017};
	


	float mRightFilter[9] = {-0.011, -0.032, -0.007,
													  0.377,  0.761,  0.009,
													 -0.026, -0.093,  1.234};

	float mGammaFilter = 1.f;

private slots:
	void changeGammaFilter(int fGammaFilter);
};

#endif
