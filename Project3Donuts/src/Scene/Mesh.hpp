#pragma once

#include "global.hpp"
#include <set>
class Object;

//! \class Mesh
//! \brief Can load an Object and apply an algorithm to reduce the number of face
class Mesh
{
	//! \class Vertex
	//! \brief Local class of Mesh to store a vertex
	class Vertex
	{

	public:
		QVector3D position; 

		Vertex(QVector3D fPosition);
		~Vertex(){}
	};

	//! \class Triangle
	//! \brief Local class of Mesh to store a triangle
	class Triangle
	{

	public:

		Triangle(Vertex* vertex1, Vertex* vertex2, Vertex* vertex3, QVector3D faceNormal);
		~Triangle()	{}

		bool isDegenerate();
		void computeCost();

		Vertex* vertices[3];
		QVector3D normal;
		float cost; // cost of collapsing triangle

		static bool compareCost(Triangle* u, Triangle* v);
	};


public:
	//! \brief Constructor, load an Object
	Mesh(Object* fModel);
	~Mesh();

	//! \brief reduces the number of face to the desired value
	void polygonReduction(size_t fPolygonDesired);

	//! \brief creates an object and fills it with the mesh
	Object* convertToModel();

private:
	//! \brief collapse a triangle and destroy it
	void collapseTriangle(Triangle* fTriangle);

	//! \brief collapse and destroy the triangle that touch the vertex
	void collapseAtVertex(Triangle* fTriangle, Vertex* fVertex);

	//! \brief destroy the triangle
	void deleteTriangle(Triangle* fTriangle);

	std::set<Vertex*> mVertices;
	std::set<Triangle*> mTriangles;
	std::set<Triangle*>::iterator mTriangleIterator;
	std::multimap<Vertex*, Triangle*> mTriangleByVertex;

};

