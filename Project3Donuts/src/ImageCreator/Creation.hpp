#ifndef CREATION_HPP
#define CREATION_HPP

#include "global.hpp"
#include "CreationFile.hpp"
#include "CreationTools.hpp"


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

	virtual void createWindow(bool fHasPreview = true);

	//! \brief Creation contains virtual methods that could be redefined in other classes that inherit from this class.
	virtual std::unique_ptr<CreationFile> render() = 0;

	//! \brief render the scene and return a color map
	//! \param fHorizontalRotation in degree
	//! \param fVerticalRotation in degree
	//! \param fZoom should be > 0, 1 equals no zoom
	std::unique_ptr<QImage> getColorMap(float fHorizontalRotation = 0.f, float fVerticalRotation = 0.f, float fZoom = 1.f);

	//! brief render the scene and return a depath map
	std::unique_ptr<QImage> getDepthMap(float fHorizontalRotation = 0.f, float fVerticalRotation = 0.f, float fZoom = 1.f);

	void updatePreview();

	void insertNewWidget(QWidget* fWidget);

    //! \describe how large is the image to create in number of pixel
    //int mWidth; 
    //! \describe how high is the image to create in number of pixel
    //int mHeight;

	QWidget* mWindow = nullptr;
	QVBoxLayout* mLayout = nullptr;
	QLabel* mTitleLabel = nullptr;
	QComboBox* mResolutionBox = nullptr;
	QLabel* mGammaLabel = nullptr;
	QSlider* mGammaSlider = nullptr;
	QLabel* mAntialiasingLabel = nullptr;
	QComboBox* mAntialiasingBox = nullptr;
	QPushButton* mRenderButton = nullptr;
	QLabel* mPreviewImage = nullptr;


private:
	float mGamma = 1.f;
	int mPositionNewWidget = 6;
	unsigned int mAntiAliasingIteration = 0;


private slots:
	void changeResolution(int fResolution);

	void startRender();

	void changeGamma(int fCursor);

	void changeAntialiasing(int fIteration);

};

#endif
