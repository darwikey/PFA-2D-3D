#ifndef CREATION_HPP
#define CREATION_HPP

#include "global.hpp"
#include "CreationFile.hpp"
#include "CreationTools.hpp"


class Creator;


  //! \class Creation
  //! \brief Creation is the basic virtual class for the creation of any other image. 
class Creation : public QObject{
	Q_OBJECT

public:
    //! \brief default constructor.
	Creation();

	//! \brief show the window
	void launch();

	//! \brief hide the window (and lost the focus)
	void hide();

protected:
	//! \brief create a new window, add all the widgets
	//! \param fHasPreview tell if the window has a preview image
	virtual void createWindow(bool fHasPreview = true);

	//! \brief Creation contains virtual methods that could be redefined in other classes that inherit from this class.
	virtual std::unique_ptr<CreationFile> render() = 0;

	//! \brief render the scene and return a color map
	//! \param fHorizontalRotation in degree
	//! \param fVerticalRotation in degree
	//! \param fZoom should be > 0, 1 equals no zoom
	std::unique_ptr<QImage> getColorMap(float fHorizontalRotation = 0.f, float fVerticalRotation = 0.f, float fZoom = 1.f, QVector2D fTranslation = QVector2D(0.f, 0.f));

	//! \brief render the scene and return a depath map
	std::unique_ptr<QImage> getDepthMap(float fHorizontalRotation = 0.f, float fVerticalRotation = 0.f, float fZoom = 1.f, QVector3D fTranslation = QVector3D(0.f, 0.f, 0.f));

	//! \brief put a new widget in the interface window
	void insertNewWidget(QWidget* fWidget);

	//! \brief compute the size of render image with the resolution
	QPoint getImageSize();


	// Widget
	QWidget* mWindow = nullptr;
	QVBoxLayout* mVLayoutMenu   = nullptr;
	QVBoxLayout* mVLayoutRender = nullptr;
	QHBoxLayout* mHLayout = nullptr;
	QLabel* mTitleLabel = nullptr;
	QComboBox* mAlgoTypeBox = nullptr;
	QLabel* mResolutionLabel = nullptr;
	QComboBox* mResolutionBox = nullptr;
	QLabel* mGammaLabel = nullptr;
	QSlider* mGammaSlider = nullptr;
	QPushButton* mBackgroundColorButton = nullptr;
	QLabel* mAntialiasingLabel = nullptr;
	QComboBox* mAntialiasingBox = nullptr;
	QPushButton* mRenderButton = nullptr;
	QPushButton* mSaveButton = nullptr;
	QLabel* mPreviewImage = nullptr;


private:
	float mResolution = 72.f;
	float mGamma = 1.f;
	int mPositionNewWidget = 9;
	unsigned int mAntiAliasingIteration = 0;
	const QSize mPreviewImageSize = QSize(600, 600);
	QVector3D mBackgroundColor = QVector3D(0.5f, 0.5f, 0.5f);
				
public slots:
	void updatePreview();
																				 
private slots:
	void changeResolution(int fResolution);

	void startRender();

	void changeGamma(int fCursor);

	void changeAntialiasing(int fIteration);

	void changeBackgroundColor();
};

#endif
