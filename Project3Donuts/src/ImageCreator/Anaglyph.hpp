#ifndef ANAGLYPH_HPP
#define ANAGLYPH_HPP

#include "global.hpp"
#include "Creation.hpp"

// ! \class Anaglyph
// ! \brief virtual Anaglyph class to define every methods that will be needed in classes that will inherit from this one and that will define different algorithms
class Anaglyph : public Creation{
	Q_OBJECT
protected:
	
	virtual void createWindow(bool fHasPreview = true) override;
	
	virtual std::unique_ptr<CreationFile> render() override = 0;
	
	QLabel*  mHorizontalRotationLabel  = nullptr;
	QSlider* mHorizontalRotationSlider = nullptr;
	QLabel*  mVerticalRotationLabel    = nullptr;
	QSlider* mVerticalRotationSlider   = nullptr;

	float mHorizontalRotation = 0.f;
	float mVerticalRotation   = 0.f;
																 
private slots:
	void changeHorizontalRotation(int fHorizontalRotation);
	void changeVerticalRotation(int fVerticalRotation);
};

#endif
