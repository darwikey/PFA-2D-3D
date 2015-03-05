#ifndef FLIPBOOK_NORMAL_HPP
#define FLIPBOOK_NORMAL_HPP

#include "global.hpp"
#include "FlipBook.hpp"


// ! \class FlipbookNormal
// ! \brief Create a simple animation of the scene
class FlipbookNormal : public Flipbook{
	//Q_OBJECT

protected:

	virtual void createWindow() override;

	virtual std::shared_ptr<QImage> render() override;


private:



//private slots:



};

#endif
