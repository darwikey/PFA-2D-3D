#pragma once

#include "global.hpp"
#include <set>
class Object;

class Mesh
{

	class Vertex
	{

	public:
		QVector3D position; 
		//std::vector<Vertex*> neigbhor;

		Vertex(QVector3D fPosition);
		~Vertex(){}

	};


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
	Mesh(Object* fModel);
	~Mesh();

	void polygonReduction(size_t fPolygonDesired);
	Object* convertToModel();

private:
	void collapseTriangle(Triangle* fTriangle);
	void collapseAtVertex(Triangle* fTriangle, Vertex* fVertex);

	void deleteTriangle(Triangle* fTriangle);

	std::set<Vertex*> mVertices;
	std::set<Triangle*> mTriangles;
	std::set<Triangle*>::iterator mTriangleIterator;
	std::multimap<Vertex*, Triangle*> mTriangleByVertex;

};

