#ifndef MYGLWIDGET_HPP
#define MYGLWIDGET_HPP


#include <QMouseEvent>
#include <QtOpenGL>
#include <QWheelEvent>
#include <QSize>
#include <QPoint>

#include <QGLWidget>

class MyGLWidget : public QWindow, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWindow *parent = 0);
    ~MyGLWidget();

    virtual void render(QPainter *painter);
    virtual void render();
    virtual void initialize();
    void setAnimating(bool animating);

    virtual void keyPressEvent( QKeyEvent *pEvent );

    /** Handles mouse press events on the QGLWidget. */
    void mousePressEvent( QMouseEvent *pEvent );

    /** Handles mouse move events on the QGLWidget. */
    void mouseMoveEvent( QMouseEvent *pEvent );

    /** Zoomin in and out of the cube */
    void wheelEvent ( QWheelEvent * pEvent );

    GLfloat fRotationX;
    GLfloat fRotationY;
    GLfloat fRotationZ;

    GLfloat fMoveUpDown;
    GLfloat fMoveLeftRight;
    GLfloat fMoveInOut;

    QSize viewport_size;					//< current size of the viewport.
    QPoint lastPos;

public slots:
    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event);
    void exposeEvent(QExposeEvent *event);

private:

    /** Change settings for rendering. */
    void setRotation( GLfloat _x, GLfloat _y, GLfloat _z );

    bool m_update_pending;
    bool m_animating;
    QOpenGLContext *m_context;
    QOpenGLPaintDevice *m_device;
};


#endif // MYGLWIDGET_HPP
