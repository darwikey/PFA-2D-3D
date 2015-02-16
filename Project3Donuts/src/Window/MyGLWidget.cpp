#include "MyGLWidget.hpp"
#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include "Scene.hpp"
#include "Camera.hpp"
#include "TransformWidget.hpp"
#include "Object.hpp"


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

    GLfloat _dx = (GLfloat)(fEvent->x() - mPrevMousePosition.x()) / 10;//viewport_size.width();
    float _dy = (float)(fEvent->y() - mPrevMousePosition.y()) / 7;//viewport_size.height();


    if( fEvent->buttons() & Qt::LeftButton ) {
		if (Scene::getScene()->getTransformWidget()->isSelected()) {
			QVector2D _mouse((float)fEvent->x() / width(), 1.f - (float)fEvent->y() / height());
			Scene::getScene()->getTransformWidget()->activate(_mouse);
		}
		else {
			Scene::getScene()->getCamera()->moveCamera(_dy, _dx, 0.f);
		}
    }

    mPrevMousePosition = fEvent->pos();
    update();
}

//wheel Event
void MyGLWidget::wheelEvent( QWheelEvent * fEvent )
{
    float _dz = (float)fEvent->delta();
	Scene::getScene()->getCamera()->moveCamera(0.f, 0.f, _dz);

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

		case Qt::Key_A:
			std::cout << "rendu..." << std::endl;
			Scene::getScene()->getCamera()->getColorMap().save("colormap.png");
			Scene::getScene()->getCamera()->getDepthMap().save("depthmap.png");
			/*Object::switchShader((Object::Shader)a);//Object::Shader::DEBUG_NORMAL);
			a++;
			if (a > Object::Shader::DEPTHMAP)
				a = 0;*/
			break;

        default:
            QGLWidget::keyPressEvent( fEvent );
    }
    update();
}
