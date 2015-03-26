#ifndef AUTOSTEREOGRAM_HPP
#define AUTOSTEREOGRAM_HPP

#include "global.hpp"
#include "Creation.hpp"


// ! \class Autostereogram
// ! \brief virtual Autostereogram class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class Autostereogram : public Creation {
	Q_OBJECT
public:
	enum Texture { RANDNB, RANDGREY, RANDCOLOR, TEXTUREMAP };


protected:

  virtual void createWindow(bool fHasPreview) override;

	virtual std::unique_ptr<CreationFile> render() override = 0;

	//! \brief extract the depth of a depthmap 
	std::vector<float> getDepth(const QImage& fImg);

  //! \brief utilitary function to facilitate data access in a vector or array
	int caseXY(int fx, int fy, int fwidth);

  //! \brief colors a pixel randomly according to the chosen texture option
  void colorRandom(int fx) ;
  
  enum Texture mTextureStyle = RANDNB ;
  QComboBox * mChooseTextureStyle = nullptr ;
  QString mTexturePath = "" ;
  QImage mTexture ;
  
  QLabel * mTextureStyleLabel = nullptr ;
  QLabel * mTexturePathLabel = nullptr ;

  std::vector<int> mred ;
  std::vector<int> mgreen ;
  std::vector<int> mblue ;

  const float MU = 1.f / 3.f ;
			 
private slots :

  //! \brief change texture style in the creation window
  void changeTextureStyle(int fSelectedTextureStyle) ;
  
};


#endif
