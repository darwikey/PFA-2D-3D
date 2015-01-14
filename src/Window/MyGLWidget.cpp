#include "MyGLWidget.hpp"
#include <QtCore/QCoreApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>
#include "Scene.hpp"
#include "Camera.hpp"


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

void MyGLWidget::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}

//mouse Press Event
void MyGLWidget::mousePressEvent(QMouseEvent *fEvent)
{
    mPrevMousePosition = fEvent->pos();

    renderLater();
}



//mouse Move Event  // non fonctionnel ??!
void MyGLWidget::mouseMoveEvent(QMouseEvent *fEvent){

    GLfloat _dx = (GLfloat)(fEvent->x() - mPrevMousePosition.x()) / 10;//viewport_size.width();
    GLfloat _dy = (GLfloat)(fEvent->y() - mPrevMousePosition.y()) / 7;//viewport_size.height();


    if( fEvent->buttons() & Qt::LeftButton ) {
        Scene::getScene()->getCamera()->moveCamera(_dy, _dx, 0.f);
    }
    else if( fEvent->buttons() & Qt::RightButton ) {
        //TODOScene::getScene()->moveCamera(-_dy, 0.f, _dx);
    }

    mPrevMousePosition = fEvent->pos();
    renderLater();
}

//wheel Event
void MyGLWidget::wheelEvent( QWheelEvent * fEvent )
{
    //TODO (GLfloat)fEvent->delta() / 80.0;
    renderLater();
}


//key Press Event
void MyGLWidget::keyPressEvent( QKeyEvent *fEvent )
{
    switch( fEvent->key() )
    {
        /*case Qt::Key_Escape:
            exit(0);
            break;

        case Qt::Key_R:
            fRotationX = 0.0f;
            fRotationY = 0.0f;
            fRotationZ = 0.0f;
            fMoveUpDown = 0.0f;
            fMoveLeftRight = 0.0f;
            fMoveInOut = 0.0f;
            break;

        case Qt::Key_Up:
        case Qt::Key_Z:
            fMoveUpDown += 0.6;
            break;

        case Qt::Key_Down:
        case Qt::Key_S:
            fMoveUpDown -= 0.6;
            break;

        case Qt::Key_Left:
        case Qt::Key_Q:
            fMoveLeftRight -= 0.6;
            break;

        case Qt::Key_Right:
        case Qt::Key_D:
            fMoveLeftRight += 0.6;
            break;
        case Qt::Key_I:
            fRotationX += 10;
            break;
        case Qt::Key_K:
            fRotationX -= 10;
            break;
        case Qt::Key_J:
            fRotationY += 10;
            break;
        case Qt::Key_L:
            fRotationY -= 10;
            break;
        case Qt::Key_P:
            fRotationZ += 10;
            break;
        case Qt::Key_M:
            fRotationZ -= 10;
            break;*/
        default:
            QWindow::keyPressEvent( fEvent );
    }
    renderLater();
}
