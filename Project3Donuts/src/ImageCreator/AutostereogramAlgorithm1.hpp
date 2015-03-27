#ifndef AUTOSTEREOGRAM_ALGO1_HPP
#define AUTOSTEREOGRAM_ALGO1_HPP

#include "global.hpp"

#include "Autostereogram.hpp"


// ! \class AutostereogramAlgorithm1
// ! \brief First algorithm to create an autostereogram
class AutostereogramAlgorithm1 : public Autostereogram {
	Q_OBJECT
public:


protected:
	virtual void createWindow(bool fHasPreview = true) override;

	virtual std::unique_ptr<CreationFile> render() override;


private :

	//! \brief Calculates the separation between two points in the autostereogram that will correspond to one point of the 3D image
	//! \param fZ is the depth of the 3D image, fE is the distance between the eyes
	int separation(float fZ, int fE) ;

	//! \brief Generates an autostereogram from a depth map
	std::unique_ptr<QImage> depthmapToAutostereogram(const QImage& fDepthmap, int fE);

	//! \brief A function that rounds a number to the closest integer
	int round(float fX);

};

#endif
