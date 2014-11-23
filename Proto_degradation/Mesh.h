#pragma once

#include "Point.h"
class Model;

class Mesh
{

	class Vertex
	{

	public:
		Vec3 position; 

		Vertex(Vec3 fPosition);
		~Vertex(){}

	};


	class Triangle
	{

	public:

		Triangle(Vertex* vertex1, Vertex* vertex2, Vertex* vertex3, Vec3 faceNormal);
		~Triangle()	{}

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
	Vertex* findVertexByIndex(size_t fIndex);
	void collapseTriangle(Triangle* fTriangle);
	

	std::vector<Vertex*> mVertices;
	std::vector<Triangle*> mTriangles;

};

