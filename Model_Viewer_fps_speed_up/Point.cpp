#include"Point.h"

Coordinate2d::Coordinate2d(GLfloat x_value, GLfloat y_value)
{
    x=x_value;
    y=y_value;
}


Coordinate3d::Coordinate3d(GLfloat x_value, GLfloat y_value, GLfloat z_value):Coordinate2d(x_value,y_value)
{
    z=z_value;
}

Coordinate3d::~Coordinate3d()
{

}


