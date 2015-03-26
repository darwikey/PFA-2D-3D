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


void Creation::hide(){
	if (mWindow != nullptr)	{
		mWindow->hide();
	}
}


void Creation::createWindow(bool fHasPreview){
	// Window and layout
	mWindow = new QWidget();
	//mWindow->setFixedSize(300, 300);
	mHLayout = new QHBoxLayout();
	mWindow->setLayout(mHLayout);

	mVLayoutMenu   = new QVBoxLayout();
	mVLayoutRender = new QVBoxLayout();

	mHLayout->addLayout(mVLayoutMenu);
	mHLayout->addLayout(mVLayoutRender);

	// Title
	mTitleLabel = new QLabel("Parametrage du rendu...", mWindow);
	mVLayoutMenu->addWidget(mTitleLabel);

	// Algo type
	mAlgoTypeBox = new QComboBox(mWindow);
	mVLayoutMenu->addWidget(mAlgoTypeBox);

	// Resolution
	mResolutionLabel = new QLabel("R\303\251solution : ", mWindow);
	mVLayoutMenu->addWidget(mResolutionLabel);

	mResolutionBox = new QComboBox(mWindow);
	mResolutionBox->addItem("300 dpi");
	mResolutionBox->addItem("200 dpi");
	mResolutionBox->addItem("100 dpi");
	mResolutionBox->addItem("72 dpi");
	mResolutionBox->setCurrentIndex(3);
	mVLayoutMenu->addWidget(mResolutionBox);
	
	QObject::connect(mResolutionBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeResolution(int)));

	// Gamma corection
	mGammaLabel = new QLabel("Correction gamma :", mWindow);
	mVLayoutMenu->addWidget(mGammaLabel);
	
	mGammaSlider = new QSlider(Qt::Orientation::Horizontal, mWindow);
	mGammaSlider->setValue(50);
	mVLayoutMenu->addWidget(mGammaSlider);
	QObject::connect(mGammaSlider, SIGNAL(valueChanged(int)), this, SLOT(changeGamma(int)));


	// Background color
	QPushButton* mBackgroundColorButton = new QPushButton("Couleur du fond", mWindow);
	mVLayoutMenu->addWidget(mBackgroundColorButton);
	QObject::connect(mBackgroundColorButton, SIGNAL(clicked()), this, SLOT(changeBackgroundColor()));


	// Antialiasing iteration
	mAntialiasingLabel = new QLabel("Anti aliasing :", mWindow);
	mVLayoutMenu->addWidget(mAntialiasingLabel);

	mAntialiasingBox = new QComboBox(mWindow);
	mAntialiasingBox->addItem("aucun");
	mAntialiasingBox->addItem("1 it\303\251ration");
	mAntialiasingBox->addItem("2 it\303\251rations");
	mAntialiasingBox->addItem("3 it\303\251rations");
	mAntialiasingBox->addItem("4 it\303\251rations");
	mAntialiasingBox->addItem("5 it\303\251rations");
	mVLayoutMenu->addWidget(mAntialiasingBox);

	QObject::connect(mAntialiasingBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeAntialiasing(int)));


	// Preview Image
	if (fHasPreview){
		mPreviewImage = new QLabel(mWindow);
		mPreviewImage->setFixedSize(mPreviewImageSize);
		mVLayoutRender->addWidget(mPreviewImage);

		// Render button
		mRenderButton = new QPushButton("Prévisualiser", mWindow);
		QObject::connect(mRenderButton, SIGNAL(clicked()), this, SLOT(updatePreview()));
		mVLayoutMenu->addWidget(mRenderButton);

		this->updatePreview();
	}


	// Save button
	mSaveButton = new QPushButton("Sauvegarder", mWindow);
	QObject::connect(mSaveButton, SIGNAL(clicked()), this, SLOT(startRender()));
	mVLayoutMenu->addWidget(mSaveButton);
}


std::unique_ptr<QImage> Creation::getColorMap(float fHorizontalRotation, float fVerticalRotation, float fZoom, QVector2D fTranslation){
	const Camera* _sceneCamera = Scene::getScene()->getCamera();
	
	// Create a new camera
	Camera _camera(_sceneCamera->getPosition(), _sceneCamera->getRotation(), 60.f);
	_camera.translateCameraWithMouse(fTranslation.x(), fTranslation.y());
	_camera.moveCamera(fHorizontalRotation, fVerticalRotation, fZoom);

	// Render
	QPoint _size = getImageSize();
	std::unique_ptr<QImage> _image = _camera.getColorMap(_size.x(), _size.y(), mBackgroundColor);
	
	// Image corrections
	CreationTools::gammaCorrection(*_image, mGamma);

	// Anti aliasing
	for (unsigned int i = 0; i < mAntiAliasingIteration; i++){
		_image = CreationTools::antiAliasing(*_image);
	}

	
	return _image;
}


std::unique_ptr<QImage> Creation::getDepthMap(float fHorizontalRotation, float fVerticalRotation, float fZoom, QVector3D fTranslation){
	const Camera* _sceneCamera = Scene::getScene()->getCamera();

	// Create a new camera
	Camera _camera(_sceneCamera->getPosition(), _sceneCamera->getRotation(), 60.f);
	_camera.translateCamera(fTranslation);
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
			QImage _image = _render->scaled(mPreviewImageSize.width(), mPreviewImageSize.height(), Qt::AspectRatioMode::IgnoreAspectRatio);
			QPixmap _pixmap = QPixmap::fromImage(_image);

			mPreviewImage->setPixmap(_pixmap);
		}
	}
}


void Creation::insertNewWidget(QWidget* fWidget){
	mVLayoutMenu->insertWidget(mPositionNewWidget, fWidget);
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
}


void Creation::changeAntialiasing(int fIteration){
	mAntiAliasingIteration = fIteration;
}


void Creation::changeBackgroundColor(){
    QColor _color = QColorDialog::getColor(Qt::white, mWindow, "Choisir une couleur", QColorDialog::DontUseNativeDialog);

	mBackgroundColor = QVector3D(_color.red() / 255.f, _color.green() / 255.f, _color.blue() / 255.f);
}
