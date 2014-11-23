#include"Point.h"


Coordinate2d::Coordinate2d(float x_value, float y_value)
{
    x=x_value;
    y=y_value;
}



Vec3::Vec3(float x_value, float y_value, float z_value) : x(x_value), y(y_value), z(z_value)
{
}

float Vec3::length() const
{
	return sqrt(x * x + y * y + z * z);
}

void Vec3::normalise() {
	float _length = length();
	if (_length > 0.f){
		x /= _length;
		y /= _length;
		z /= _length;
	}
}

float Vec3::distance(const Vec3& fPoint) const {
	return sqrt((fPoint.x - x) * (fPoint.x - x) + (fPoint.y - y) * (fPoint.y - y) + (fPoint.z - z) * (fPoint.z - z));
}

float Vec3::dotProduct(const Vec3& fPoint) const {
	return x * fPoint.x + y * fPoint.y + z * fPoint.z;
}

Vec3 Vec3::crossProduct(const Vec3& fPoint) const {
	return Vec3(y * fPoint.z - fPoint.y * z,
				z * fPoint.x - fPoint.z * x,
				x * fPoint.y - fPoint.x * y);
}

// arithmetic operations
Vec3 Vec3::operator + (const Vec3& rkVector) const
{
	return Vec3(x + rkVector.x, y + rkVector.y, z + rkVector.z);
}

Vec3 Vec3::operator - (const Vec3& rkVector) const
{
	return Vec3(x - rkVector.x, y - rkVector.y, z - rkVector.z);
}

Vec3 Vec3::operator * (const float fScalar) const
{
	return Vec3(x * fScalar, y * fScalar, z * fScalar);
}

Vec3 Vec3::operator * (const Vec3& rhs) const
{
	return Vec3(x * rhs.x, y * rhs.y, z * rhs.z);
}

Vec3 Vec3::operator / (const float fScalar) const
{
	float fInv = 1.0f / fScalar;

	return Vec3(x * fInv, y * fInv, z * fInv);
}

Vec3 Vec3::operator - () const
{
	return Vec3(-x, -y, -z);
}

