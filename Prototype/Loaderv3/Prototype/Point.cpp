#include"Point.hpp"

Vec2::Vec2(GLfloat x_value, GLfloat y_value)
{
    x=x_value;
    y=y_value;
}


Vec3::Vec3(GLfloat x_value, GLfloat y_value, GLfloat z_value):Vec2(x_value,y_value)
{
    z=z_value;
}

Vec3::~Vec3()
{

}


