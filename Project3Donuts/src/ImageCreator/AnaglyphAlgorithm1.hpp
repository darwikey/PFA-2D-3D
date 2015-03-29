#ifndef ANAGLYPH_ALGO1_HPP
#define ANAGLYPH_ALGO1_HPP

#include "global.hpp"
#include "Anaglyph.hpp"

/**
 * @class AnaglyphAlgorithm1
 * @brief First anaglyph algorithm based on the Photoshop method.
 * This is a retranscription in C++ of the method Photoshop described in
 * the article "Creating a Color Anaglyph from a Pseudo-Stereo Pair of Images"
 * by Alkhadour W and Ipson S and Zraqou J and Qahwaji R and Haigh J
 * which has been publicated in 2009
 */
class AnaglyphAlgorithm1 : public Anaglyph{
	Q_OBJECT

protected:

	virtual void createWindow(bool fHasPreview = true) override;
    /**
     * @brief Renders the image by processing each pixel of the left and right image
     * The process is based on keeping only the red component of the left image,
     * and only the blue and green components of the right image
     */
	virtual std::unique_ptr<CreationFile> renderAnaglyph() override;
       
};

#endif
