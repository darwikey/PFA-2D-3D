#ifndef ANAGLYPH_ALGO1_HPP
#define ANAGLYPH_ALGO1_HPP

#include "global.hpp"
#include "Anaglyph.hpp"


//! \class AnaglyphAlgorithm1
//! \brief First anaglyph algorithm based on photoshop method.
class AnaglyphAlgorithm1 : public Anaglyph{
	Q_OBJECT

protected:

	virtual void createWindow(bool fHasPreview = true) override;

	virtual std::unique_ptr<CreationFile> renderAnaglyph() override;
       
};

#endif
