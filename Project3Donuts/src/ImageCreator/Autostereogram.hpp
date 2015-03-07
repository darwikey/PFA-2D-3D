#ifndef AUTOSTEREOGRAM_HPP
#define AUTOSTEREOGRAM_HPP

#include "global.hpp"
#include "Creation.hpp"

enum Texture {RANDNB, RANDGREY, RANDCOLOR, TEXTUREMAP} ;

// ! \class Autostereogram
// ! \brief virtual Autostereogram class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class Autostereogram : public Creation {
public:


protected:

	virtual void createWindow() override;

	virtual std::unique_ptr<CreationFile> render() override = 0;



};


#endif
