#ifndef ANAGLYPH_ALGO2_HPP
#define ANAGLYPH_ALGO2_HPP

#include "global.hpp"
#include "Anaglyph.hpp"

/**
 * @class AnaglyphAlgorithm2
 * @brief Second algorithm to create an anaglyph : the least squares method.
 * This is a retranscription in C++ of the algorithm of E. Dubois
 * as presented in his article "Conversion of a Stereo Pair to Anaglyph with the Least-Squares Projection Method "
 * which has been publicated in 2009
 */
//! \class AnaglyphAlgorithm2
//! \brief Secound algorithm to create an anaglyph
class AnaglyphAlgorithm2 : public Anaglyph{
	Q_OBJECT

protected:

	virtual void createWindow(bool fHasPreview = true) override;

    /**
     * @brief Renders the image by processing each pixel of the left and right image
     * The process is based on the application of Gamma correction
     * and the matrix (given in the article) multiplication
     */
	virtual std::unique_ptr<CreationFile> renderAnaglyph() override;

    /**
     * @brief Applies the matrix given by the article to the RGB array to obtain the left view
     * and rescale RGB values between 0 and 1
     */
	void modifyLeftImage (float *fRgb);

    /**
     * @brief Applies the matrix given by the article to the RGB array to obtain the right view
     * and rescale RGB values between 0 and 1
     */
    void modifyRightImage(float *fRgb);


    /**
     * @brief Applies the gamma correction to RGB
     */
	void applyGamma      (QRgb fPixel, float *fRgb);
	QRgb applyGammaRevert(float *fRgb);

	QLabel*  mGammaFilterLabel  = nullptr;
	QSlider* mGammaFilterSlider = nullptr; 
	
private:
    //Matrix in the article (obtained with the least square method), for the left and right view
	static const float mLeftFilter[9];
	static const float mRightFilter[9];

	float mGammaFilter = 1.f;

private slots:
    /**
     * @brief Modifies the Gamma value for the Gamma correction
     */

	void changeGammaFilter(int fGammaFilter);
};

#endif
