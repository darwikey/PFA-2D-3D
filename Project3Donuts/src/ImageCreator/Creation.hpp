#ifndef CREATION_HPP
#define CREATION_HPP

#include "global.hpp"

class PixelTab;
class Creator;


  // ! \class Creation
  // ! \brief Creation is the basic virtual class for the creation of any other image. However, this basic virtual class also corresponds to basic Photography
class Creation : public QObject{
	Q_OBJECT

public:
    //! \brief default constructor.
	Creation();

	//! \brief show the window
	void launch();


protected:

	virtual void createWindow();

	//! \brief Creation contains virtual methods that could be redefined in other classes that inherit from this class.
	virtual std::shared_ptr<QImage> render() = 0;

	std::shared_ptr<QImage> getColorMap();

	std::shared_ptr<QImage> getDepthMap();

	void updatePreview();

	void gammaCorrection(std::shared_ptr<QImage> fImage);


    //! \describe how large is the image to create in number of pixel
    //int mWidth; 
    //! \describe how high is the image to create in number of pixel
    //int mHeight;

	QWidget* mWindow = nullptr;
	QVBoxLayout* mLayout = nullptr;
	QLabel* mLabel = nullptr;
	QComboBox* mResolutionBox = nullptr;
	QSlider* mGammaSlider = nullptr;
	QPushButton* mRenderButton = nullptr;
	QLabel* mPreviewImage = nullptr;

	float mGamma = 1.f;


private slots:
	void changeResolution(int fResolution);

	void startRender();

	void changeGamma(int fCursor);
};

#endif
