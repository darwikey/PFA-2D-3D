#ifndef ANAGLYPH_ALGO3_HPP
#define ANAGLYPH_ALGO3_HPP

#include "global.hpp"
#include "Anaglyph.hpp"


// ! \class AnaglyphAlgo2
// ! \brief First algorithm to create an anaglyph
class AnaglyphAlgorithm3 : public Anaglyph{
  Q_OBJECT

protected:

  virtual void createWindow(bool fHasPreview = true) override;

  virtual std::unique_ptr<CreationFile> renderAnaglyph() override;

  void getMinColorAndOperate(QRgb fPixel, float *fRgb, bool sRgb);
  
  void colorCorrection(int fR, int fG, int fB, float* fRgb, bool sRgb);
  
  void modifyLeftImage (float *fRgb);
  void modifyRightImage(float *fRgb);
	
private:

  static const float mLeftFilter[9];
  static const float mRightFilter[9];
};

#endif
