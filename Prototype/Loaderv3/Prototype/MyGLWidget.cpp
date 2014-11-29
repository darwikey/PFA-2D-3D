#include "MyGLWidget.hpp"


#include <QtCore/QCoreApplication>

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLPaintDevice>
#include <QtGui/QPainter>

MyGLWidget::MyGLWidget(QWindow *parent)
    : QWindow(parent)
    , m_update_pending(false)
    , m_animating(false)
    , m_context(0)
    , m_device(0)
{
    setSurfaceType(QWindow::OpenGLSurface);
}

MyGLWidget::~MyGLWidget()
{
    delete m_device;
}
void MyGLWidget::render(QPainter *painter)
{
    Q_UNUSED(painter);
}

void MyGLWidget::initialize()
{
}

void MyGLWidget::render()
{
    if (!m_device)
        m_device = new QOpenGLPaintDevice;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    m_device->setSize(size());

    QPainter painter(m_device);
    render(&painter);
}

void MyGLWidget::renderLater()
{
    if (!m_update_pending) {
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

bool MyGLWidget::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        m_update_pending = false;
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void MyGLWidget::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);

    if (isExposed())
        renderNow();
}

void MyGLWidget::renderNow()
{
    if (!isExposed())
        return;

    bool needsInitialize = false;

    if (!m_context) {
        m_context = new QOpenGLContext(this);
        m_context->setFormat(requestedFormat());
        m_context->create();

        needsInitialize = true;
    }

    m_context->makeCurrent(this);

    if (needsInitialize) {
        initializeOpenGLFunctions();
        initialize();
    }

    render();

    m_context->swapBuffers(this);

    if (m_animating)
        renderLater();
}

void MyGLWidget::setAnimating(bool animating)
{
    m_animating = animating;

    if (animating)
        renderLater();
}

//==============================================================================	set Rotation
void MyGLWidget::setRotation( GLfloat _x, GLfloat _y, GLfloat _z )
{
    fRotationX += _x;
    fRotationY += _y;
    fRotationZ += _z;

    renderLater();
}

//==============================================================================	mouse Press Event
void MyGLWidget::mousePressEvent(QMouseEvent *pEvent)
{
    lastPos = pEvent->pos();

    renderLater();
}



//==============================================================================	mouse Move Event  // non fonctionnel ??!
void MyGLWidget::mouseMoveEvent(QMouseEvent *pEvent)
{
    GLfloat dx = (GLfloat)(pEvent->x() - lastPos.x()) / viewport_size.width();
    GLfloat dy = (GLfloat)(pEvent->y() - lastPos.y()) / viewport_size.height();


    if( pEvent->buttons() & Qt::LeftButton )
    {
        setRotation(-dy, -dx, 0.0);
    }
    else if( pEvent->buttons() & Qt::RightButton )
    {
        setRotation(-dy, 0.0, dx);
    }
    else
    {} // do nothing //

    lastPos = pEvent->pos();
    renderLater();
}


//==============================================================================	wheel Event
void MyGLWidget::wheelEvent( QWheelEvent * pEvent )
{
    fMoveInOut += (GLfloat)pEvent->delta() / 80.0;
    renderLater();
}



//==============================================================================	key Press Event
void MyGLWidget::keyPressEvent( QKeyEvent *pEvent )
{
    switch( pEvent->key() )
    {
        case Qt::Key_Escape:
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
            break;
        default:
            QWindow::keyPressEvent( pEvent );
    }
    renderLater();
}
