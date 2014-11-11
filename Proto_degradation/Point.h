#ifndef POINT_H
#define POINT_H

using namespace std;

#include <QtGui/QOpenGLShaderProgram>
#include <set>

class Coordinate2d {
        
    public:
		GLfloat x, y;

        Coordinate2d(){}
        Coordinate2d(GLfloat x_value, GLfloat y_value);
		~Coordinate2d() {}
};


class Vec3 {

    public:
		GLfloat x, y, z;

		Vec3(){}
        Vec3(GLfloat x_value, GLfloat y_value, GLfloat z_value);
		~Vec3(){}

		GLfloat distance(const Vec3& fPoint) const;
		GLfloat dotProduct(const Vec3& fPoint) const;
};


class Triangle;

class Vertex {

public:
	Vec3 position; // location of this point
	std::set<Vertex *> neighbor; // adjacent vertices
	std::vector<Triangle *> face; // adjacent triangles
	float cost; // cached cost of collapsing edge
	Vertex* collapse; // candidate vertex for collapse

	Vertex(Vec3 fPosition);
	~Vertex() {}

};


class Triangle {

public:

	Triangle(Vertex* vertex1, Vertex* vertex2, Vertex* vertex3, Vec3 faceNormal);
	~Triangle() {}

	bool hasVertex(Vertex* v);
	void replaceVertex(Vertex* fOldVertex, Vertex* fNewVertex);

	Vertex* vertices[3];
	Vec3 normal;
};





#endif // POINT_H
