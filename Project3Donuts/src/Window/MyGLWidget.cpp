#include "MyGLWidget.hpp"
#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include "Scene.hpp"
#include "Camera.hpp"
#include "TransformWidget.hpp"


MyGLWidget::MyGLWidget(QWindow *fParent) : 
	QWindow(fParent){
    setSurfaceType(QWindow::OpenGLSurface);
}

MyGLWidget::~MyGLWidget(){
    delete mDevice;
}

void MyGLWidget::render(QPainter *fPainter)
{
    Q_UNUSED(fPainter);
}

void MyGLWidget::initialize(){
}

void MyGLWidget::render(){
    if (!mDevice)
        mDevice = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    mDevice->setSize(size());

    QPainter painter(mDevice);
    render(&painter);
}

void MyGLWidget::renderLater(){
    if (!mUpdatePending) {
        mUpdatePending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

bool MyGLWidget::event(QEvent *fEvent){
    switch (fEvent->type()) {
    case QEvent::UpdateRequest:
        mUpdatePending = false;
        renderNow();
        return true;
    default:
        return QWindow::event(fEvent);
    }
}

void MyGLWidget::exposeEvent(QExposeEvent *fEvent)
{
    Q_UNUSED(fEvent);

    if (isExposed())
        renderNow();
}

void MyGLWidget::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!mContext) {
        mContext = new QOpenGLContext(this);
        mContext->setFormat(requestedFormat());
        mContext->create();

        needsInitialize = true;
    }

    mContext->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    mContext->swapBuffers(this);

    if (m_animating)
        renderLater();
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

    renderLater();
}


void  MyGLWidget::mouseReleaseEvent(QMouseEvent *fEvent) {
	Scene::getScene()->getTransformWidget()->unselect();

	renderLater();
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
    renderLater();
}

//wheel Event
void MyGLWidget::wheelEvent( QWheelEvent * fEvent )
{
    float _dz = (float)fEvent->delta();
	Scene::getScene()->getCamera()->moveCamera(0.f, 0.f, _dz);

    renderNow();
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
       
        default:
            QWindow::keyPressEvent( fEvent );
    }
    renderLater();
}
