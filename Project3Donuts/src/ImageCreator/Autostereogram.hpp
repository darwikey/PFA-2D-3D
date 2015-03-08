#ifndef AUTOSTEREOGRAM_HPP
#define AUTOSTEREOGRAM_HPP

#include "global.hpp"
#include "Creation.hpp"


// ! \class Autostereogram
// ! \brief virtual Autostereogram class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class Autostereogram : public Creation {
public:
	enum Texture { RANDNB, RANDGREY, RANDCOLOR, TEXTUREMAP };


protected:

	virtual void createWindow(bool fHasPreview) override;

	virtual std::unique_ptr<CreationFile> render() override = 0;

	//! \brief extract the depth of a depthmap 
	std::vector<float> getDepth(const QImage& fImg);


};


#endif
