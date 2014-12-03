#pragma once

#include "Point.h"
class Model;

class Mesh
{
	struct Triangle;

	struct Vertex
	{

	public:
		Vec3 position; 

		Vertex(Vec3 fPosition);
		~Vertex(){}

		std::vector<Triangle*> linkedTriangles;

	};


	struct Triangle
	{

	public:

		Triangle(Vertex* vertex1, Vertex* vertex2, Vertex* vertex3, Vec3 faceNormal);
		~Triangle()	{}

		bool hasVertex(Vertex* v);
		void replaceVertex(Vertex* fOldVertex, Vertex* fNewVertex);
		bool isDegenerate();
		void computeCost();

		Vertex* vertices[3];
		Vec3 normal;
		float cost; // cost of collapsing triangle

		static bool compareCost(Triangle* u, Triangle* v);
	};


public:
	Mesh(Model* fModel);
	~Mesh();

	void polygonReduction(size_t fPolygonDesired);
	Model* convertToModel();

private:
	void collapseTriangle(Triangle* fTriangle);
	void deleteTriangle(Triangle* fTriangle);

	std::vector<Vertex*> mVertices;
	//std::vector<Triangle*> mTriangles;
	std::multimap<float, Triangle*> mTrianglesByCost;

};

