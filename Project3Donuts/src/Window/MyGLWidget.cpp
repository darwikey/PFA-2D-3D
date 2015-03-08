#include "MyGLWidget.hpp"
#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include "Scene.hpp"
#include "Camera.hpp"
#include "TransformWidget.hpp"
#include "Object.hpp"
#include "Creator.hpp"


MyGLWidget::MyGLWidget(int framesPerSecond, QWidget *fParent, char * fName):
    QGLWidget(fParent){
    setWindowTitle(QString::fromUtf8(fName));
    setFocusPolicy(Qt::ClickFocus);
    if(framesPerSecond == 0)
        mTimer = NULL;
    else
    {
        int seconde = 1000; // 1 seconde = 1000 ms
        int timerInterval = seconde / framesPerSecond;
        mTimer = new QTimer(this);
        connect(mTimer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        mTimer->start( timerInterval );
    }
}

MyGLWidget::~MyGLWidget(){

}

void MyGLWidget::timeOutSlot()
{

}
//mouse Press Event
void MyGLWidget::mousePressEvent(QMouseEvent *fEvent)
{
    mPrevMousePosition = fEvent->pos();
	QVector2D _mouse((float)fEvent->x() / width(), 1.f - (float)fEvent->y() / height());

	if (fEvent->buttons() & Qt::LeftButton) {
		Scene::getScene()->getTransformWidget()->select(_mouse);
	}
	else if (fEvent->buttons() & Qt::RightButton) {
		Scene::getScene()->selectObjects(_mouse);
	}

     update();
}


void  MyGLWidget::mouseReleaseEvent(QMouseEvent *fEvent) {
	Scene::getScene()->getTransformWidget()->unselect();

    update();
}

//mouse Move Event
void MyGLWidget::mouseMoveEvent(QMouseEvent *fEvent){

    float _dx = (float)(fEvent->x() - mPrevMousePosition.x()) / 10;//viewport_size.width();
    float _dy = (float)(fEvent->y() - mPrevMousePosition.y()) / 7;//viewport_size.height();


    if( fEvent->buttons() & Qt::LeftButton ) {
		if (Scene::getScene()->getTransformWidget()->isSelected()) {
			QVector2D _mouse((float)fEvent->x() / width(), 1.f - (float)fEvent->y() / height());
			Scene::getScene()->getTransformWidget()->activate(_mouse);
		}
		else {
			Scene::getScene()->getCamera()->moveCameraWithMouse(_dy, _dx, 0.f);
		}
    }

    mPrevMousePosition = fEvent->pos();
    update();
}

//wheel Event
void MyGLWidget::wheelEvent( QWheelEvent * fEvent )
{
    float _dz = (float)fEvent->delta();
	Scene::getScene()->getCamera()->moveCameraWithMouse(0.f, 0.f, _dz);

    update();
}


//key Press Event
void MyGLWidget::keyPressEvent( QKeyEvent *fEvent )
{
    switch( fEvent->key() )
    {
        case Qt::Key_Escape:
            exit(0);
            break;

		case Qt::Key_T:
			Scene::getScene()->getTransformWidget()->changeState(TransformWidget::State::TRANSLATION);
			break;

        case Qt::Key_R:
			Scene::getScene()->getTransformWidget()->changeState(TransformWidget::State::ROTATION);
            break;

        case Qt::Key_S:
			Scene::getScene()->getTransformWidget()->changeState(TransformWidget::State::SCALE);
            break;

		case Qt::Key_Plus:
			Scene::getScene()->getCamera()->moveCameraWithMouse(0.f, 0.f, 0.1f);
			break;

		case Qt::Key_Minus:
			Scene::getScene()->getCamera()->moveCameraWithMouse(0.f, 0.f, -0.1f);
			break;

		case Qt::Key_Delete:
			Scene::getScene()->deleteSelectedObject();
			break;

		case Qt::Key_Z:
			Scene::getScene()->revertPreviousAction();
			break;

		case Qt::Key_N:
			Creator::getCreator()->launchAnaglyph(0);
			break;

		case Qt::Key_U:
			Creator::getCreator()->launchAutostereogram(0);
			break;

		case Qt::Key_P:
			Creator::getCreator()->launchPhotograph(0);
			break;

		case Qt::Key_F:
			Creator::getCreator()->launchFlipbook(0);
			break;

		case Qt::Key_C:
		{
			QColor _colorRGB = QColorDialog::getColor(QColor(128, 128, 128), nullptr, "Select Color", QColorDialog::DontUseNativeDialog);
			QVector3D _color(_colorRGB.red(), _colorRGB.green(), _colorRGB.blue());
			Object* _selectedObject = Scene::getScene()->getObject(Scene::getScene()->getNameSelectedObject());
			if (_selectedObject){
				_selectedObject->setGlobalColor(_color / 255.f);
			}
			break;
		}

        default:
            QGLWidget::keyPressEvent( fEvent );
    }
    update();
}
