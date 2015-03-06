#ifndef PHOTOGRAPH_NORMAL_HPP
#define PHOTOGRAPH_NORMAL_HPP

#include "global.hpp"
#include "Photograph.hpp"


// ! \class PhotographNormal
// ! \brief Create a simple render of the scene
class PhotographNormal : public Photograph{
	Q_OBJECT

protected:

	virtual void createWindow() override;

	virtual CreationFile render() override;


private:
	QCheckBox* mGreyBox = nullptr;

	bool mIsGrey = false;


private slots:
	void setGrey(int fIsGrey);


};

#endif
