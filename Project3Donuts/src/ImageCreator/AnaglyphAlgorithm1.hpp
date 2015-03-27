#ifndef ANAGLYPH_ALGO1_HPP
#define ANAGLYPH_ALGO1_HPP

#include "global.hpp"
#include "Anaglyph.hpp"


//! \class AnaglyphAlgo1
//! \brief First algorithm to create an anaglyph
class AnaglyphAlgorithm1 : public Anaglyph{
	Q_OBJECT

protected:

	virtual void createWindow(bool fHasPreview = true) override;

	virtual std::unique_ptr<CreationFile> renderAnaglyph() override;
       
};

#endif
