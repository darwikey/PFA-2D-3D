#include"Point.h"


Coordinate2d::Coordinate2d(GLfloat x_value, GLfloat y_value)
{
    x=x_value;
    y=y_value;
}



Vec3::Vec3(GLfloat x_value, GLfloat y_value, GLfloat z_value) : x(x_value), y(y_value), z(z_value)
{
}

GLfloat Vec3::distance(const Vec3& fPoint) const {
	return sqrt((fPoint.x - x) * (fPoint.x - x) + (fPoint.y - y) * (fPoint.y - y) + (fPoint.z - z) * (fPoint.z - z));
}

GLfloat Vec3::dotProduct(const Vec3& fPoint) const {
	return x * fPoint.x + y * fPoint.y + z * fPoint.z;
}


Vertex::Vertex(Vec3 fPosition) : position(fPosition),
cost(FLT_MAX),
collapse(nullptr){
}



Triangle::Triangle(Vertex* vertex1, Vertex* vertex2, Vertex* vertex3, Vec3 faceNormal) : normal(faceNormal) {
	vertices[0] = vertex1;
	vertices[1] = vertex2;
	vertices[2] = vertex3;
}


bool Triangle::hasVertex(Vertex* v){
	return vertices[0] == v || vertices[1] == v || vertices[2] == v;
}

void Triangle::replaceVertex(Vertex* fOldVertex, Vertex* fNewVertex){
	for (int i = 0; i < 3; i++)	{
		if (vertices[i] == fOldVertex){
			vertices[i] = fNewVertex;
			return;
		}
	}
}
