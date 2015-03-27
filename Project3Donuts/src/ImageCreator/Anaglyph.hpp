#ifndef ANAGLYPH_HPP
#define ANAGLYPH_HPP

#include "global.hpp"
#include "Creation.hpp"

//! \class Anaglyph
//! \brief virtual Anaglyph class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class Anaglyph : public Creation{
	Q_OBJECT
protected:

	virtual void createWindow(bool fHasPreview = true) override;

	virtual std::unique_ptr<CreationFile> render() override;
	virtual std::unique_ptr<CreationFile> renderAnaglyph() = 0;
	virtual std::unique_ptr<CreationFile> renderLeft();
	virtual std::unique_ptr<CreationFile> renderRight();

	QLabel*  mTranslationLabel = nullptr;
	QSlider* mTranslationSlider = nullptr;

	QLabel*    mChooseViewLabel = nullptr;
	QComboBox* mChooseView = nullptr;
	int        mViewSelected = 0;

	double mTranslation = 0.f;

	private slots:
	void changeTranslation(int fTranslation);
	void changeChoosenView(int fViewSelected);
};

#endif
