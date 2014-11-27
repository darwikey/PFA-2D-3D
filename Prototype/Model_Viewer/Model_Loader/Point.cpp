#include <stdio.h>


#include"Point.h"

Coordinate2d::Coordinate2d(GLfloat x_value, GLfloat y_value)
{
    x=x_value;
    y=y_value;
}

Coordinate2d::~Coordinate2d()
{

}

GLfloat Coordinate2d::getX()
{
    return x;

}
GLfloat Coordinate2d::getY()
{
    return y;

}


Coordinate3d::Coordinate3d(GLfloat x_value, GLfloat y_value, GLfloat z_value):Coordinate2d(x_value,y_value)
{
    z=z_value;
}

Coordinate3d::~Coordinate3d()
{

}

GLfloat Coordinate3d::getZ()
{

    return z;

}

Face::Face(Coordinate3d v, Coordinate2d vt, Coordinate3d vn)
{
    Vertex = v;
    VertexTexture=vt;
    VertexNormal=vn;
}

Face::~Face()
{

}

Coordinate3d Face::getVertex()
{
    return Vertex;
}

Coordinate2d Face::getVertexTexture()
{
    return VertexTexture;
}

Coordinate3d Face::getVertexNormal()
{
    return VertexNormal;
}
