#pragma once

#include "Point.h"

class Model;

class Mesh
{
	class Triangle;

	class Vertex
	{

	public:
		Vec3 position; // location of this point
		std::set<Vertex *> neighbor; // adjacent vertices
		std::vector<Triangle *> face; // adjacent triangles
		float cost; // cached cost of collapsing edge
		Vertex* collapse; // candidate vertex for collapse

		Vertex(Vec3 fPosition);
		~Vertex(){}

	};


	class Triangle
	{

	public:

		Triangle(Vertex* vertex1, Vertex* vertex2, Vertex* vertex3, Vec3 faceNormal);
		~Triangle()	{}

		bool hasVertex(Vertex* v);
		void replaceVertex(Vertex* fOldVertex, Vertex* fNewVertex);

		Vertex* vertices[3];
		Vec3 normal;
	};


public:
	Mesh(Model* fModel);
	~Mesh();

	void polygonReduction(size_t fPolygonDesired);
	Model* convertToModel();

private:
	float computeEdgeCollapseCost(Vertex* u, Vertex* v);
	void computeEdgeCostAtVertex(Vertex *v);
	void collapse(Vertex *u, Vertex *v);
	void collapseTriangle(Triangle* fTriangle);
	void delete_vertex(Vertex* v);
	void delete_triangle(Triangle* fTriangle);

	static bool compareCost(Vertex* u, Vertex* v);
	

	vector<Vertex*> mVertices;
	vector<Triangle*> mTriangles;

};

