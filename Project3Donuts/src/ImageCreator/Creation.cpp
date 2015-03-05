#include "Creation.hpp"
#include "Scene.hpp"
#include "Camera.hpp"


void Creation::launch(){
	if (mWindow == nullptr){
		this->createWindow();
	}
	else{
		mWindow->show();
	}
}


void Creation::createWindow(){
	// Window and layout
	mWindow = new QWidget();
	mWindow->setFixedSize(300, 150);
	mLayout = new QVBoxLayout();
	mWindow->setLayout(mLayout);

	// Text
	mLabel = new QLabel("Parametrage du rendu...", mWindow);
	mLayout->addWidget(mLabel);

	// Resolution
	mResolutionBox = new QComboBox(mWindow);
	mResolutionBox->addItem("75 dpi");
	mResolutionBox->addItem("300 dpi");
	mLayout->addWidget(mResolutionBox);

	QObject::connect(mResolutionBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeResolution(int)));


	// Render button
	mRenderButton = new QPushButton("Render !", mWindow);
	QObject::connect(mRenderButton, SIGNAL(clicked()), this, SLOT(startRender()));
	mLayout->addWidget(mRenderButton);
}


QImage Creation::getColorMap(){
	return Scene::getScene()->getCamera()->getColorMap(1920, 1080);
}


QImage Creation::getDepthMap(){
	return Scene::getScene()->getCamera()->getDepthMap(1920, 1080);
}


void Creation::changeResolution(int fResolution){
	std::cout << fResolution;
}


void Creation::startRender(){
	this->render();
}