#include "Creation.hpp"
#include "Scene.hpp"
#include "Camera.hpp"


Creation::Creation(){

}


void Creation::launch(){
	if (mWindow == nullptr){
		this->createWindow();
		mWindow->show();
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

	// Title
	mTitleLabel = new QLabel("Parametrage du rendu...", mWindow);
	mLayout->addWidget(mTitleLabel);

	// Resolution
	mResolutionBox = new QComboBox(mWindow);
	mResolutionBox->addItem("75 dpi");
	mResolutionBox->addItem("300 dpi");
	mLayout->addWidget(mResolutionBox);

	QObject::connect(mResolutionBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeResolution(int)));


	// Gamma corection
	mGammaLabel = new QLabel("Correction gamma :", mWindow);
	mLayout->addWidget(mGammaLabel);
	
	mGammaSlider = new QSlider(Qt::Orientation::Horizontal, mWindow);
	mGammaSlider->setValue(50);
	mLayout->addWidget(mGammaSlider);
	QObject::connect(mGammaSlider, SIGNAL(valueChanged(int)), this, SLOT(changeGamma(int)));


	// Preview Image
	mPreviewImage = new QLabel(mWindow);
	mPreviewImage->setFixedSize(200, 200);
	mLayout->addWidget(mPreviewImage);

	this->updatePreview();


	// Render button
	mRenderButton = new QPushButton("Rendre !", mWindow);
	QObject::connect(mRenderButton, SIGNAL(clicked()), this, SLOT(startRender()));
	mLayout->addWidget(mRenderButton);
}


std::shared_ptr<QImage> Creation::getColorMap(float fHorizontalRotation, float fVerticalRotation, float fZoom){
	const Camera* _sceneCamera = Scene::getScene()->getCamera();
	
	// Create a new camera
	Camera _camera(_sceneCamera->getPosition(), _sceneCamera->getRotation(), 60.f);
	_camera.moveCamera(fHorizontalRotation, fVerticalRotation, fZoom);

	// Render
	std::shared_ptr<QImage> _image = _camera.getColorMap(1920, 1080);
	
	// Image corrections
	this->gammaCorrection(_image);
	
	return _image;
}


std::shared_ptr<QImage> Creation::getDepthMap(float fHorizontalRotation, float fVerticalRotation, float fZoom){
	const Camera* _sceneCamera = Scene::getScene()->getCamera();

	// Create a new camera
	Camera _camera(_sceneCamera->getPosition(), _sceneCamera->getRotation(), 60.f);
	_camera.moveCamera(fHorizontalRotation, fVerticalRotation, fZoom);

	// Render
	std::shared_ptr<QImage> _image = _camera.getDepthMap(1920, 1080);

	return _image;
}


void Creation::updatePreview(){
	std::shared_ptr<QImage> _render = this->render().getFirstImage();
	
	if (_render) {

		QImage _image = _render->scaled(200, 200, Qt::AspectRatioMode::IgnoreAspectRatio);
		QPixmap _pixmap = QPixmap::fromImage(_image);

		if (mPreviewImage != nullptr) {
			mPreviewImage->setPixmap(_pixmap);
		}
	}
}


void Creation::gammaCorrection(std::shared_ptr<QImage> fImage){
	
	for (int x = 0; x < fImage->width(); x++){
		for (int y = 0; y < fImage->height(); y++){
	
			QRgb _p = fImage->pixel(x, y);
		
			float _red = qRed(_p) / 255.f;
			float _green = qGreen(_p) / 255.f;
			float _blue = qBlue(_p) / 255.f;
		
			_red = pow(_red, 1.f / mGamma);
			_green = pow(_green, 1.f / mGamma);
			_blue = pow(_blue, 1.f / mGamma);
		
			fImage->setPixel(x, y, qRgb((int)(_red * 255.f), (int)(_green * 255.f), (int)(_blue * 255.f)));
			
		}
	}
}


void Creation::insertNewWidget(QWidget* fWidget){
	mLayout->insertWidget(4, fWidget);
}


void Creation::changeResolution(int fResolution){
	//TODO
}


void Creation::startRender(){
	QString _file = QFileDialog::getSaveFileName(mWindow, "Save", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
	std::cout << "save image : " << _file.toStdString();

	CreationFile _image = this->render();

	_image.save(_file);
}


void Creation::changeGamma(int fCursor){
	mGamma = ((float)fCursor / 100.f) * 2.f;
	
	if (mGamma > 1.f){
		mGamma *= 2.f;
	}
	
	this->updatePreview();
}
