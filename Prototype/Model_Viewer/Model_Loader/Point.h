#ifndef POINT_H
#define POINT_H

using namespace std;

#include <QtGui/QOpenGLShaderProgram>

class Coordinate2d {
    private:
        GLfloat x,y;
    public:
        Coordinate2d(){}
        Coordinate2d(GLfloat x_value, GLfloat y_value);
        ~Coordinate2d();
        GLfloat getX();
        GLfloat getY();
};

class Coordinate3d : public Coordinate2d{
    private:
        GLfloat z;
    public:
        Coordinate3d(){}
        Coordinate3d(GLfloat x_value, GLfloat y_value, GLfloat z_value);
        ~Coordinate3d();
        GLfloat getZ();
};

class Face {
  private :
    Coordinate3d Vertex;
    Coordinate2d VertexTexture;
    Coordinate3d VertexNormal;
  public:
    Face(){}
    Face(Coordinate3d v, Coordinate2d vt, Coordinate3d vn);
    ~Face();
    Coordinate3d getVertex();
    Coordinate2d getVertexTexture();
    Coordinate3d getVertexNormal();
};



#endif // POINT_H
