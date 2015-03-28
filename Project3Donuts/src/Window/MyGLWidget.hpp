#ifndef MYGLWIDGET_HPP
#define MYGLWIDGET_HPP

#include "global.hpp"

#include <QOpenGLFunctions>
#include "MainWindow.hpp" // we need myglwidget to know that mainwindow is a qt class (to be able to send a signal)

//! \class MyGLWidget
//! \brief Model Viewer basic window.
class MyGLWidget : public QGLWidget, public QOpenGLFunctions
{
    Q_OBJECT
public:
    //! \brief Constructor, initialize the window.
    explicit MyGLWidget(int framesPerSecond = 0, QWidget *fParent = 0, char * fName = 0);
    ~MyGLWidget();

    //! \brief Initialized the opengl functions.
	virtual void initializeGL() override  = 0;

    //! \brief Resize method for the window.
    virtual void resizeGL(int fWidth, int fHeight) override = 0;

    //! \brief Render function
	virtual void paintGL() override = 0;
    
	//! \brief Handles key press events on the QGLWidget.
    void keyPressEvent( QKeyEvent *fEvent ) override;

    //! \brief Handles mouse press events on the QGLWidget.
    void mousePressEvent(QMouseEvent *fEvent) override;

    //! \brief Handles mouse release events on the QGLWidget.
	void mouseReleaseEvent(QMouseEvent *fEvent) override;

    //! \brief Handles mouse move events on the QGLWidget.
    void mouseMoveEvent(QMouseEvent *fEvent) override;

    //! \brief Zoomin in and out of the cube
    void wheelEvent(QWheelEvent * fEvent) override;

    //! \brief set the window that will receive the notifications of updates on the scene
    void setParentWindow(MainWindow * fWindow);

signals:
    //! \brief Used to notify the parent window that there are new changes.
    void newAction();
    //! \brief Used to notify the parent window that we are trying to close the program.
    void winClose();

public slots:
    //! \brief Timeout method.
    virtual void timeOutSlot();

private:
    MainWindow *mParent;
    QTimer *mTimer;
	// mouse position at the lastest mouse click 
    QPoint mPrevMousePosition;
};


#endif // MYGLWIDGET_HPP
