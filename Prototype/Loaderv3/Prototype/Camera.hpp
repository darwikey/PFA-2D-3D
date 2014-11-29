#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <QtOpenGL>

class Camera
{
public:
    Camera();

    GLfloat fRotationX;
    GLfloat fRotationY;
    GLfloat fRotationZ;

    GLfloat fMoveUpDown;
    GLfloat fMoveLeftRight;
    GLfloat fMoveInOut;

};

#endif // CAMERA_HPP
