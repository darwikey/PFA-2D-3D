#ifndef POINT_H
#define POINT_H

using namespace std;

#include <QtGui/QOpenGLShaderProgram>


class Vec2 {
        
    public:
		GLfloat x, y;

        Vec2(){}
        Vec2(GLfloat x_value, GLfloat y_value);
        ~Vec2() {}
};

class Vec3 : public Vec2{
    public:
        GLfloat z;
        Vec3(){}
        Vec3(GLfloat x_value, GLfloat y_value, GLfloat z_value);
        ~Vec3();
};

#endif // POINT_H
