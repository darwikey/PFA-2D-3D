#ifndef ANAGLYPH_ALGO1_HPP
#define ANAGLYPH_ALGO1_HPP

#include "global.hpp"
#include "Anaglyph.hpp"


// ! \class AnaglyphAlgo1
// ! \brief First algorithm to create an anaglyph
class AnaglyphAlgorithm1 : public Anaglyph{
protected:

	virtual void createWindow() override;

	virtual void render() override;
       
};

#endif
