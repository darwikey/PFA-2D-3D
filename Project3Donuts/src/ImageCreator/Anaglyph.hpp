#ifndef ANAGLYPH_HPP
#define ANAGLYPH_HPP

#include "global.hpp"
#include "Creation.hpp"

/**
 * @class Anaglyph
 * @brief virtual Anaglyph class, defines every methods needed
 * in inherited classes which defines different algorithms
 */

class Anaglyph : public Creation{
	Q_OBJECT
protected:

	virtual void createWindow(bool fHasPreview = true) override;

	virtual std::unique_ptr<CreationFile> render() override;

    //! \brief Renders the anaglyph by using the left and right views
	virtual std::unique_ptr<CreationFile> renderAnaglyph() = 0;

    //! \brief Renders the left view (shift to the right)
	virtual std::unique_ptr<CreationFile> renderLeft();

    //! \brief Renders the right view (shift to the left)
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
