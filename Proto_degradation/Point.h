#ifndef POINT_H
#define POINT_H

using namespace std;

#include <QtGui/QOpenGLShaderProgram>
#include <set>

class Coordinate2d {
        
    public:
		float x, y;

        Coordinate2d(){}
        Coordinate2d(float x_value, float y_value);
		~Coordinate2d() {}
};


class Vec3 {

    public:
		float x, y, z;

		Vec3(){}
        Vec3(float x_value, float y_value, float z_value);

		float length() const;
		void normalise();
		float distance(const Vec3& fPoint) const;
		float dotProduct(const Vec3& fPoint) const;
		Vec3 crossProduct(const Vec3& fPoint) const;

		Vec3 operator + (const Vec3& rkVector) const;
		Vec3 operator - (const Vec3& rkVector) const;
		Vec3 operator * (const float fScalar) const;
		Vec3 operator * (const Vec3& rhs) const;
		Vec3 operator / (const float fScalar) const;
		Vec3 operator - () const;

		
};



#endif // POINT_H
