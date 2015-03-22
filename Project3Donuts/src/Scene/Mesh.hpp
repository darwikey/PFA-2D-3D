#pragma once

#include "global.hpp"
class Object;

class Mesh
{

	class Vertex
	{

	public:
		QVector3D position; 

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
	Vertex* findVertexByIndex(size_t fIndex);
	void collapseTriangle(Triangle* fTriangle);
	

	std::vector<Vertex*> mVertices;
	std::vector<Triangle*> mTriangles;

};

