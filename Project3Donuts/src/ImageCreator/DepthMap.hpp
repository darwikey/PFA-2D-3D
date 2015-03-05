#ifndef DEPTHMAP_HPP
#define DEPTHMAP_HPP

#include "global.hpp"
#include "Creation.hpp"


// ! \class DepthMap
// ! \brief virtual DepthMap class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class DepthMap : public Creation{
public:


protected:

	virtual void createWindow() override;

	virtual std::shared_ptr<QImage> render() override = 0;



};


#endif
