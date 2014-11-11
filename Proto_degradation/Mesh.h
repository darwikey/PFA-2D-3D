#pragma once

#include "Point.h"

class Model;

class Mesh
{
public:
	Mesh(Model* fModel);
	~Mesh();

	void polygonReduction(size_t fPolygonDesired);
	Model* convertToModel();

private:
	float computeEdgeCollapseCost(Vertex* u, Vertex* v);
	void computeEdgeCostAtVertex(Vertex *v);
	void collapse(Vertex *u, Vertex *v);
	void delete_vertex(Vertex* v);
	
	static bool compareCost(Vertex* u, Vertex* v);
	

	vector<Vertex*> mVertices;
	vector<Triangle*> mTriangles;
};

