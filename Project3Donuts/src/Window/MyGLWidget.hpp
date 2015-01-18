#ifndef MYGLWIDGET_HPP
#define MYGLWIDGET_HPP


#include <QMouseEvent>
#include <QtOpenGL>
#include <QWheelEvent>
#include <QSize>
#include <QPoint>

#include <QGLWidget>

class MyGLWidget : public QWindow, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWindow *parent = 0);
    ~MyGLWidget();

    virtual void render(QPainter *painter);
    virtual void render();
    virtual void initialize();
    

    virtual void keyPressEvent( QKeyEvent *fEvent );

    /** Handles mouse press events on the QGLWidget. */
    void mousePressEvent( QMouseEvent *fEvent );

	/** Handles mouse release events on the QGLWidget. */
	void mouseReleaseEvent(QMouseEvent *fEvent);

    /** Handles mouse move events on the QGLWidget. */
    void mouseMoveEvent( QMouseEvent *fEvent );

    /** Zoomin in and out of the cube */
    void wheelEvent ( QWheelEvent * fEvent );


    void renderLater();
    void renderNow();

protected:
    bool event(QEvent *event);
    void exposeEvent(QExposeEvent *event);

private:

    bool mUpdatePending = false;
    bool m_animating = false;
    QOpenGLContext *mContext = nullptr;
    QOpenGLPaintDevice *mDevice = nullptr;
	
	// mouse position at the lastest mouse click 
	QPoint mPrevMousePosition;
};


#endif // MYGLWIDGET_HPP
