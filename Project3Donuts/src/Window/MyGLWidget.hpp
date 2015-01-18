#ifndef MYGLWIDGET_HPP
#define MYGLWIDGET_HPP


#include <QMouseEvent>
#include <QtOpenGL>
#include <QWheelEvent>
#include <QSize>
#include <QPoint>

#include <QOpenGLFunctions>
#include <QGLWidget>

class MyGLWidget : public QGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyGLWidget(int framesPerSecond = 0, QWidget *fParent = 0, char * fName = 0);
    ~MyGLWidget();

    virtual void initializeGL() = 0;
    virtual void resizeGL(int fWidth, int fHeight) = 0;
    virtual void paintGL() = 0;
    

    virtual void keyPressEvent( QKeyEvent *fEvent );

    /** Handles mouse press events on the QGLWidget. */
    void mousePressEvent( QMouseEvent *fEvent );

	/** Handles mouse release events on the QGLWidget. */
	void mouseReleaseEvent(QMouseEvent *fEvent);

    /** Handles mouse move events on the QGLWidget. */
    void mouseMoveEvent( QMouseEvent *fEvent );

    /** Zoomin in and out of the cube */
    void wheelEvent ( QWheelEvent * fEvent );


public slots:
    virtual void timeOutSlot();

private:

    QTimer *mTimer;
	// mouse position at the lastest mouse click 
	QPoint mPrevMousePosition;
    QSize viewport_size;
};


#endif // MYGLWIDGET_HPP
