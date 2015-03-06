#ifndef PHOTOGRAPH_HPP
#define PHOTOGRAPH_HPP

#include "global.hpp"
#include "Creation.hpp"

// ! \class Photograph
// ! \brief virtual Photograph class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class Photograph : public Creation{
	Q_OBJECT

public:


protected:

	virtual void createWindow() override;

	virtual CreationFile render() override = 0;



};

#endif
