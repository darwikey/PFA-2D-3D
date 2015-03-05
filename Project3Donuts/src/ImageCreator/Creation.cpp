#include "Creation.hpp"
#include "Scene.hpp"
#include "Camera.hpp"


Creation::Creation(){

}


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
	//mWindow->setFixedSize(300, 300);
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


	// Preview Image
	mPreviewImage = new QLabel(mWindow);
	mPreviewImage->setFixedSize(200, 200);
	mLayout->addWidget(mPreviewImage);

	this->updatePreview();


	// Render button
	mRenderButton = new QPushButton("Render !", mWindow);
	QObject::connect(mRenderButton, SIGNAL(clicked()), this, SLOT(startRender()));
	mLayout->addWidget(mRenderButton);
}


std::shared_ptr<QImage> Creation::getColorMap(){
	return Scene::getScene()->getCamera()->getColorMap(1920, 1080);
}


std::shared_ptr<QImage> Creation::getDepthMap(){
	return Scene::getScene()->getCamera()->getDepthMap(1920, 1080);
}


void Creation::updatePreview(){
	QImage _image = this->render()->scaled(200, 200, Qt::AspectRatioMode::IgnoreAspectRatio);
	QPixmap _pixmap = QPixmap::fromImage(_image);

	if (mPreviewImage != nullptr) {
		mPreviewImage->setPixmap(_pixmap);
	}
}


void Creation::changeResolution(int fResolution){
	std::cout << fResolution;
}


void Creation::startRender(){
	QString _file = QFileDialog::getSaveFileName(mWindow, "Save", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
	std::cout << "save image : " << _file.toStdString();

	std::shared_ptr<QImage> _image = this->render();

	_image->save(_file);
}