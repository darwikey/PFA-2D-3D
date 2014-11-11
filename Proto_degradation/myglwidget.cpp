#include "myGLWidget.h"
#include"loader.h"
myGLWidget::myGLWidget(int framesPerSecond, QWidget *parent, char *name)
    : QGLWidget(parent),    fRotationX(0.0f),
      fRotationY(0.0f),
      fRotationZ(0.0f),
      fMoveUpDown(0.0f),
      fMoveLeftRight(0.0f),
      fMoveInOut(-15.0f)
{
    setWindowTitle(QString::fromUtf8(name));
    if(framesPerSecond == 0)
        t_Timer = NULL;
    else
    {
        int seconde = 1000; // 1 seconde = 1000 ms
        int timerInterval = seconde / framesPerSecond;
        t_Timer = new QTimer(this);
        connect(t_Timer, SIGNAL(timeout()), this, SLOT(timeOutSlot()));
        t_Timer->start( timerInterval );
    }

}

void myGLWidget::timeOutSlot()
{
}

void myGLWidget::perspective(GLdouble fovy, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
    GLdouble xmin, xmax, ymin, ymax;

    ymax = zNear * tan( fovy * M_PI / 360.0 );
    ymin = -ymax;
    xmin = ymin * aspect;
    xmax = ymax * aspect;

    glFrustum( xmin, xmax, ymin, ymax, zNear, zFar );
}

//==============================================================================	set Rotation
void myGLWidget::setRotation( GLfloat _x, GLfloat _y, GLfloat _z )
{
    fRotationX += _x;
    fRotationY += _y;
    fRotationZ += _z;
}


//==============================================================================	mouse Press Event
void myGLWidget::mousePressEvent(QMouseEvent *pEvent)
{
    lastPos = pEvent->pos();
}



//==============================================================================	mouse Move Event  // non fonctionnel ??!
void myGLWidget::mouseMoveEvent(QMouseEvent *pEvent)
{
    GLfloat dx = (GLfloat)(pEvent->x() - lastPos.x()) / viewport_size.width();
    GLfloat dy = (GLfloat)(pEvent->y() - lastPos.y()) / viewport_size.height();

    qDebug() << dx;
    qDebug() << dy << "\n";

    if( pEvent->buttons() & Qt::LeftButton )
    {
        setRotation(180 * dy, 180 * dx, 0.0);
    }
    else if( pEvent->buttons() & Qt::RightButton )
    {
        setRotation(180 * dy, 0.0, 180 * dx);
    }
    else
    {} // do nothing //

    update();
    lastPos = pEvent->pos();
}


//==============================================================================	wheel Event
void myGLWidget::wheelEvent( QWheelEvent * pEvent )
{
    fMoveInOut += (GLfloat)pEvent->delta() / 80.0;
    update();
}



//==============================================================================	key Press Event
void myGLWidget::keyPressEvent( QKeyEvent *pEvent )
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
            fMoveInOut = -15.0f;
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
            QGLWidget::keyPressEvent( pEvent );
    }
    update();
}
