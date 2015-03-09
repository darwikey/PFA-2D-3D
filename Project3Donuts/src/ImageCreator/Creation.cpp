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


void Creation::createWindow(bool fHasPreview){
	// Window and layout
	mWindow = new QWidget();
	//mWindow->setFixedSize(300, 300);
	mLayout = new QVBoxLayout();
	mWindow->setLayout(mLayout);

	// Title
	mTitleLabel = new QLabel("Parametrage du rendu...", mWindow);
	mLayout->addWidget(mTitleLabel);

	// Algo type
	mAlgoTypeBox = new QComboBox(mWindow);
	mLayout->addWidget(mAlgoTypeBox);

	// Resolution
	mResolutionLabel = new QLabel("R\303\251solution : ", mWindow);
	mLayout->addWidget(mResolutionLabel);

	mResolutionBox = new QComboBox(mWindow);
	mResolutionBox->addItem("300 dpi");
	mResolutionBox->addItem("200 dpi");
	mResolutionBox->addItem("100 dpi");
	mResolutionBox->addItem("72 dpi");
	mResolutionBox->setCurrentIndex(3);
	mLayout->addWidget(mResolutionBox);

	QObject::connect(mResolutionBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeResolution(int)));


	// Gamma corection
	mGammaLabel = new QLabel("Correction gamma :", mWindow);
	mLayout->addWidget(mGammaLabel);
	
	mGammaSlider = new QSlider(Qt::Orientation::Horizontal, mWindow);
	mGammaSlider->setValue(50);
	mLayout->addWidget(mGammaSlider);
	QObject::connect(mGammaSlider, SIGNAL(valueChanged(int)), this, SLOT(changeGamma(int)));


	// Antialiasing iteration
	mAntialiasingLabel = new QLabel("Anti aliasing :", mWindow);
	mLayout->addWidget(mAntialiasingLabel);

	mAntialiasingBox = new QComboBox(mWindow);
	mAntialiasingBox->addItem("aucun");
	mAntialiasingBox->addItem("1 it\303\251ration");
	mAntialiasingBox->addItem("2 it\303\251rations");
	mAntialiasingBox->addItem("3 it\303\251rations");
	mAntialiasingBox->addItem("4 it\303\251rations");
	mAntialiasingBox->addItem("5 it\303\251rations");
	mLayout->addWidget(mAntialiasingBox);

	QObject::connect(mAntialiasingBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeAntialiasing(int)));


	// Preview Image
	if (fHasPreview){
		mPreviewImage = new QLabel(mWindow);
		mPreviewImage->setFixedSize(200, 200);
		mLayout->addWidget(mPreviewImage);

		this->updatePreview();
	}


	// Render button
	mRenderButton = new QPushButton("Lancer le rendu !", mWindow);
	QObject::connect(mRenderButton, SIGNAL(clicked()), this, SLOT(startRender()));
	mLayout->addWidget(mRenderButton);
}


std::unique_ptr<QImage> Creation::getColorMap(float fHorizontalRotation, float fVerticalRotation, float fZoom){
	const Camera* _sceneCamera = Scene::getScene()->getCamera();
	
	// Create a new camera
	Camera _camera(_sceneCamera->getPosition(), _sceneCamera->getRotation(), 60.f);
	_camera.moveCamera(fHorizontalRotation, fVerticalRotation, fZoom);

	// Render
	QPoint _size = getImageSize();
	std::unique_ptr<QImage> _image = _camera.getColorMap(_size.x(), _size.y());
	
	// Image corrections
	CreationTools::gammaCorrection(*_image, mGamma);

	// Anti aliasing
	for (unsigned int i = 0; i < mAntiAliasingIteration; i++){
		_image = CreationTools::antiAliasing(*_image);
	}

	
	return _image;
}


std::unique_ptr<QImage> Creation::getDepthMap(float fHorizontalRotation, float fVerticalRotation, float fZoom){
	const Camera* _sceneCamera = Scene::getScene()->getCamera();

	// Create a new camera
	Camera _camera(_sceneCamera->getPosition(), _sceneCamera->getRotation(), 60.f);
	_camera.moveCamera(fHorizontalRotation, fVerticalRotation, fZoom);

	// Render
	QPoint _size = getImageSize();
	std::unique_ptr<QImage> _image = _camera.getDepthMap(_size.x(), _size.y());

	return _image;
}


void Creation::updatePreview(){
	if (mPreviewImage != nullptr) {

		std::unique_ptr<CreationFile> _creation = this->render();
		const QImage* _render = _creation->getFirstImage();

		if (_render) {

			// Create a low resolution image
			QImage _image = _render->scaled(200, 200, Qt::AspectRatioMode::IgnoreAspectRatio);
			QPixmap _pixmap = QPixmap::fromImage(_image);

			mPreviewImage->setPixmap(_pixmap);
		}
	}
}


void Creation::insertNewWidget(QWidget* fWidget){
	mLayout->insertWidget(mPositionNewWidget, fWidget);
	mPositionNewWidget++;
}


QPoint Creation::getImageSize(){
	QPoint _point(11.69333f, 8.26666f);
	return mResolution * _point;
}


void Creation::changeResolution(int fResolution){
	switch (fResolution){
	case 0:
		mResolution = 300.f;
		break;

	case 1:
		mResolution = 200.f;
		break;

	case 2:
		mResolution = 100.f;
		break;

	case 3:
		mResolution = 72.f;
		break;
	}
}


void Creation::startRender(){
	QString _file = QFileDialog::getSaveFileName(mWindow, "Save", QString(), "Images (*.png *.gif *.jpg *.jpeg)");
	std::cout << "save image : " << _file.toStdString() << std::endl;

	std::unique_ptr<CreationFile> _image = this->render();

	_image->save(_file);
}


void Creation::changeGamma(int fCursor){
	mGamma = ((float)fCursor / 100.f) * 2.f;
	
	if (mGamma > 1.f){
		mGamma *= 2.f;
	}
	
	this->updatePreview();
}


void Creation::changeAntialiasing(int fIteration){
	mAntiAliasingIteration = fIteration;
}