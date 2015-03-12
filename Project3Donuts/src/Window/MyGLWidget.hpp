#ifndef MYGLWIDGET_HPP
#define MYGLWIDGET_HPP

#include "global.hpp"

#include <QOpenGLFunctions>


class MyGLWidget : public QGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit MyGLWidget(int framesPerSecond = 0, QWidget *fParent = 0, char * fName = 0);
    ~MyGLWidget();

	virtual void initializeGL() override  = 0;
    virtual void resizeGL(int fWidth, int fHeight) override = 0;
	virtual void paintGL() override = 0;
    
	//! \brief Handles key press events on the QGLWidget.
    void keyPressEvent( QKeyEvent *fEvent ) override;

    //! \brief Handles mouse press events on the QGLWidget.
    void mousePressEvent(QMouseEvent *fEvent) override;

	// \brief Handles mouse release events on the QGLWidget.
	void mouseReleaseEvent(QMouseEvent *fEvent) override;

    // \brief Handles mouse move events on the QGLWidget.
    void mouseMoveEvent(QMouseEvent *fEvent) override;

    // \brief Zoomin in and out of the cube
    void wheelEvent(QWheelEvent * fEvent) override;


public slots:
    virtual void timeOutSlot();
    void revertPreviousAction();

private:

    QTimer *mTimer;
    QAction * mUndo;
	// mouse position at the lastest mouse click 
    QPoint mPrevMousePosition;
};


#endif // MYGLWIDGET_HPP
