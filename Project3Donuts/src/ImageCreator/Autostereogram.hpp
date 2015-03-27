#ifndef AUTOSTEREOGRAM_HPP
#define AUTOSTEREOGRAM_HPP

#include "global.hpp"
#include "Creation.hpp"


//! \class Autostereogram
//! \brief virtual Autostereogram class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class Autostereogram : public Creation {
	Q_OBJECT
public:
	enum Texture { RANDNB, RANDGREY, RANDCOLOR, TEXTUREMAP };


protected:

	virtual void createWindow(bool fHasPreview) override;

	virtual std::unique_ptr<CreationFile> render() override = 0;

	//! \brief extracts the depth of a depthmap 
	std::vector<float> getDepth(const QImage& fImg);

	//! \brief utilitary function to facilitate data access in a vector or array
	int caseXY(int fx, int fy, int fwidth);

	//! \brief colors a pixel randomly according to the chosen texture option
	void colorRandom(int fx);

        //! \brief selected type of texture
	enum Texture mTextureStyle = RANDNB;

	QComboBox * mChooseTextureStyle = nullptr;

        //! \brief path to chosen texture
	QString mTexturePath = "";

        //! \brief chosen texture
	QImage mTexture;

	QLabel * mTextureStyleLabel = nullptr;
	QLabel * mTexturePathLabel = nullptr;

        QGroupBox * mChooseView = nullptr;
        QRadioButton * mViewAutostereogram = nullptr;
        QRadioButton * mViewDepthMap = nullptr;
        QVBoxLayout * mViewVBox = nullptr;
  
        //! \brief is true if the chosen view is the result of the chosen algorithm, false if it is the depth map
        bool mViewIsAutostereogram = true;
  
        //! \brief filled with the red value of each pixel for each line of the image
	std::vector<int> mRed;

        //! \brief filled with the green value of each pixel for each line of the image
	std::vector<int> mGreen;

        //! \brief filled with the blue value of each pixel for each line of the image
	std::vector<int> mBlue;

	const float MU = 1.f / 3.f;

	private slots :

	//! \brief changes texture style in the creation window
	void changeTextureStyle(int fSelectedTextureStyle);

        //! \brief changes selected view (depth map or autostereogram)
        void changeView();
};


#endif
