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

	int separation(float fZ, int fE) ;
	std::unique_ptr<QImage> depthmapToAutostereogram(const QImage& fDepthmap, int fE);

	int round(float fX);
	int caseXY(int fx, int fy, int fwidth);


	const float mu = (1. / 3.);
};

#endif
