#ifndef AUTOSTEREOGRAM_ALGO1_HPP
#define AUTOSTEREOGRAM_ALGO1_HPP

#include "global.hpp"

#include "Autostereogram.hpp"


// ! \class AutostereogramAlgorithm1
// ! \brief First algorithm to create an autostereogram
class AutostereogramAlgorithm1 : public Autostereogram {
public:


protected:
	virtual void createWindow() override;

	virtual std::shared_ptr<QImage> render() override;


private :
	std::vector<float> getDepth(std::shared_ptr<QImage> fImg);

	int separation(float fZ, int fE) ;
	std::shared_ptr<QImage> depthmapToAutostereogram(std::shared_ptr<QImage>, int fE);

	int round(float fX);
	int caseXY(int fx, int fy, int fwidth);


	const float mu = (1. / 3.);
};

#endif
