#include "TransformWidget.hpp"
#include "ObjLoader.hpp"
#include "SceneRenderer.hpp"
#include "Object.hpp"


TransformWidget::TransformWidget(){
}

TransformWidget::~TransformWidget(){
}


void TransformWidget::render(SceneRenderer* fRenderer, const std::vector<Object*>& fSelectedObjects){
	if (mState != TransformWidget::State::HIDE
		&& mObjectX != nullptr
		&& !fSelectedObjects.empty()) {

		mObjectX->moveObject(fSelectedObjects[0]->getPosition());
		mObjectY->moveObject(fSelectedObjects[0]->getPosition());
		mObjectZ->moveObject(fSelectedObjects[0]->getPosition());

		mObjectX->changeObjectOrientation(QVector3D(0.f, 0.f, -1.57f));
		//mObjectY->changeObjectOrientation(fSelectedObjects[0]->getRotation());
		mObjectZ->changeObjectOrientation(QVector3D(1.57f, 0.f, 0.f));

		fRenderer->render(mObjectX, true);
		fRenderer->render(mObjectY, true);
		fRenderer->render(mObjectZ, true);
	}
}


void TransformWidget::changeState(TransformWidget::State fState) {
	// Load the widget model
	if (mObjectX == nullptr) {
		mObjectX = new Object();
		mObjectY = new Object();
		mObjectZ = new Object();

		std::string _objPath = "resources/models/widget.obj";
		ObjLoader _loaderX(_objPath);
		ObjLoader _loaderY(_objPath);
		ObjLoader _loaderZ(_objPath);

		if (!_loaderX.load(mObjectX)
			|| !_loaderY.load(mObjectY)
			|| !_loaderZ.load(mObjectZ)){
			QMessageBox::critical(0, "Error", "Error opening " + QString(_objPath.c_str()));
		}

		mObjectX->computeColors(QVector3D(1.f, 0.f, 0.f));
		mObjectY->computeColors(QVector3D(0.f, 1.f, 0.f));
		mObjectZ->computeColors(QVector3D(0.f, 0.f, 1.f));
	}

	mState = fState;
}