#ifndef POINT_H
#define POINT_H

using namespace std;

#include <QtGui/QOpenGLShaderProgram>


class Coordinate2d {
        
    public:
		GLfloat x, y;

        Coordinate2d(){}
        Coordinate2d(GLfloat x_value, GLfloat y_value);
		~Coordinate2d() {}
};

class Coordinate3d : public Coordinate2d{
    public:
        GLfloat z;
        Coordinate3d(){}
        Coordinate3d(GLfloat x_value, GLfloat y_value, GLfloat z_value);
        ~Coordinate3d();
};

#endif // POINT_H
