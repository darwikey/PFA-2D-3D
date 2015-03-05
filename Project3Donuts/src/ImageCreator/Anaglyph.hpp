#ifndef ANAGLYPH_HPP
#define ANAGLYPH_HPP

#include "global.hpp"
#include "Creation.hpp"

// ! \class Anaglyph
// ! \brief virtual Anaglyph class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class Anaglyph : public Creation{
public:


protected:

	virtual void createWindow() override;

	virtual void render() override = 0;



};

#endif
