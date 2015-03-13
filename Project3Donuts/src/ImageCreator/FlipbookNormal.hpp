#ifndef FLIPBOOK_NORMAL_HPP
#define FLIPBOOK_NORMAL_HPP

#include "global.hpp"
#include "Flipbook.hpp"


// ! \class FlipbookNormal
// ! \brief Create a simple animation of the scene
class FlipbookNormal : public Flipbook{
	Q_OBJECT

protected:

	virtual void createWindow(bool fHasPreview = false) override;

	virtual std::unique_ptr<CreationFile> render() override;


private:
	QCheckBox* mGreyBox = nullptr;
	QLabel* mHorizontalSpeedLabel = nullptr;
	QSlider* mHorizontalSpeedSlider = nullptr;
	QLabel* mVerticalSpeedLabel = nullptr;
	QSlider* mVerticalSpeedSlider = nullptr;
	QLabel* mZoomSpeedLabel = nullptr;
	QSlider* mZoomSpeedSlider = nullptr;
	QLabel* mFrameNumberLabel = nullptr;
	QSpinBox* mFrameNumberBox = nullptr;

	bool mIsGrey = false;

	float mHorizontalSpeed = 0.f;
	float mVerticalSpeed = 0.f;
	float mZoomSpeed = 0.f;
	int mFrameNumber = 10;


private slots:
	void setGrey(int fIsGrey);

	void changeHorizontalSpeed(int fSpeed);

	void changeVerticalSpeed(int fSpeed);

	void changeZoomSpeed(int fSpeed);

	void changeFrameNumber(int fValue);
};

#endif
