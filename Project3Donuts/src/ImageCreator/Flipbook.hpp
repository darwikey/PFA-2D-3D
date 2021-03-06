#ifndef FLIPBOOK_HPP
#define FLIPBOOK_HPP

#include "global.hpp"
#include "Creation.hpp"

//! \class Flipbook
//! \brief virtual Flipbook class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class Flipbook : public Creation{
	Q_OBJECT

public:


protected:

	virtual void createWindow(bool fHasPreview = false) override;

	virtual std::unique_ptr<CreationFile> render() override = 0;



};


#endif
