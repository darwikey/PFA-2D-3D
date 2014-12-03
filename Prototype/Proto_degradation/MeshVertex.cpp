#include "Mesh.h"
#include "model.h"


Mesh::Vertex::Vertex(Vec3 fPosition) : position(fPosition),
cost(FLT_MAX),
collapse(nullptr)
{
}



Mesh::Triangle::Triangle(Vertex* vertex1, Vertex* vertex2, Vertex* vertex3, Vec3 faceNormal) : normal(faceNormal), cost(0.f)
{
	vertices[0] = vertex1;
	vertices[1] = vertex2;
	vertices[2] = vertex3;
}


bool Mesh::Triangle::hasVertex(Vertex* v)
{
	return vertices[0] == v || vertices[1] == v || vertices[2] == v;
}

void Mesh::Triangle::replaceVertex(Vertex* fOldVertex, Vertex* fNewVertex)
{
	for (int i = 0; i < 3; i++)
	{
		if (vertices[i] == fOldVertex)
		{
			vertices[i] = fNewVertex;
			return;
		}
	}
}


Mesh::Mesh(Model* fModel){
	fModel->vertices.reserve(fModel->vertices.size());

	// for each vertex
	for(Vec3& v: fModel->vertices){
		mVertices.push_back(new Vertex(v));
	}

	// for each triangle
	for(auto& tri: fModel->triangles){

		Triangle* _tri = new Triangle(nullptr, nullptr, nullptr, Vec3(0,0,0));

		// for each vertex of the triangle
		for (int i = 0; i < 3; i++) {
			uint index = tri.vertices[i]-1;
			if (index < mVertices.size()) {
				_tri->vertices[i] = mVertices[index];
			}
		}

		if (_tri->vertices[0] == nullptr || _tri->vertices[1] == nullptr || _tri->vertices[2] == nullptr){
			delete _tri;
			continue;
		}

		//Compute the normal of the face
		Vec3 _edge1 = _tri->vertices[1]->position - _tri->vertices[0]->position;
		Vec3 _edge2 = _tri->vertices[2]->position - _tri->vertices[0]->position;
		_tri->normal = _edge1.crossProduct(_edge2);
		_tri->normal.normalise();

		mTriangles.push_back(_tri);


		// add information on each vertex
		for (size_t i = 0; i < 3; i++){
			_tri->vertices[i]->face.push_back(_tri);
			
			// add for each vertex his vertex neighbor
			for (size_t j = 0; j < 3; j++){
				if (i != j){
					_tri->vertices[i]->neighbor.insert(_tri->vertices[j]);
				}
			}
		}
	}

	for(auto _v: mVertices){
		computeEdgeCostAtVertex(_v);
	}
}


Mesh::~Mesh()
{
	//TODO delete vertices & triangles
}




void Mesh::polygonReduction(size_t fPolygonDesired){
	/*while(mVertices.size() > fPolygonDesired) {
		//find the vertex with the lowest cost
		Vertex* mn = *std::min_element(mVertices.begin(), mVertices.end(), &Mesh::compareCost);
		collapse(mn,mn->collapse);

	}*/
	const size_t _iterationNumber = 15;// mTriangles.size() - fPolygonDesired;
	for (size_t i = 0; i < _iterationNumber; i++)
	{
		for (auto _tri : mTriangles) {
			if (_tri != nullptr) {
				collapseTriangle(_tri);
				break;
			}
		}
	}
	mVertices.size();
}


Model* Mesh::convertToModel(){
	Model* _model = new Model();
	
	for(auto _v: mVertices){
		_model->vertices.push_back(_v->position);
	}
	
	for(auto _tri: mTriangles){
		if (_tri == nullptr) {
			continue;
		}

		Model::StructTriangle _modelTri;
		bool _fail = false;

		for (size_t i = 0; i < 3; i++) {
			auto it = std::find(mVertices.begin(), mVertices.end(), _tri->vertices[i]);
			if (it != mVertices.end()){
				_modelTri.vertices[i] = 1 + std::distance(mVertices.begin(), it);
			}
			else {
				_fail = true;
			}
		}

		if (!_fail) {
			_model->triangles.push_back(_modelTri);
		}
	}

	return _model;
}


float Mesh::computeEdgeCollapseCost(Vertex* u, Vertex* v){
	// if we collapse edge uv by moving u to v then how 
	// much different will the model change, i.e. the “error”.
	float edgelength = v->position.distance(u->position);
	float curvature = 0;
	// find the “sides” triangles that are on the edge uv
	std::vector<Triangle *> sides;
	for (size_t i = 0; i < u->face.size(); i++)	{
		if (u->face[i]->hasVertex(v))
		{
			sides.push_back(u->face[i]);
		}
	}
	// use the triangle facing most away from the sides 
	// to determine our curvature term
	for (size_t i = 0; i < u->face.size(); i++)	{
		float mincurv = 1;
		for (int j = 0; j < sides.size(); j++){
			// use dot product of face normals
			float dotprod = u->face[i]->normal.dotProduct(sides[j]->normal);
			mincurv = min(mincurv, (1 - dotprod) / 2.0f);
		}
		curvature = max(curvature, mincurv);
	}
	return edgelength * curvature;
}

void Mesh::computeEdgeCostAtVertex(Vertex *v)
{
	if (v->neighbor.size() == 0){
		v->collapse = nullptr;
		v->cost = -0.01f;
		return;
	}

	v->cost = FLT_MAX;
	v->collapse = nullptr;
	// search all neighboring edges for “least cost” edge
	for (auto _neighbor: v->neighbor){
		
		float c = computeEdgeCollapseCost(v, _neighbor);
		if (c < v->cost){
			v->collapse = _neighbor;
			v->cost = c;
		}
	}

	if (v->collapse == nullptr)
		v->neighbor.size();
}


void Mesh::collapse(Vertex *u, Vertex *v)
{
	// Collapse the edge uv by moving vertex u onto v
	if (!v){
		// u is a vertex all by itself so just delete it
		//mVertices.erase(std::find(mVertices.begin(), mVertices.end(), u));
		delete_vertex( u);
		return;
	}

	std::vector<Vertex *> tmp;
	tmp.reserve(u->neighbor.size());

	// make tmp a list of all the neighbors of u
	for (auto it: u->neighbor){
		tmp.push_back(it);
	}

	// delete triangles on edge uv:
	for (int i = u->face.size() - 1; i >= 0; i--){
		if (u->face[i]->hasVertex(v)){
			delete_triangle(u->face[i]);
		}
	}

	// update remaining triangles to have v instead of u
	for (auto itV : mVertices)
	{
		for (auto itF : itV->face)
		{
			itF->replaceVertex(u, v);
		}
	}

	delete_vertex(u);

	// recompute the edge collapse costs in neighborhood
	for (auto it : tmp){
		computeEdgeCostAtVertex(it);
	}
}

void Mesh::collapseTriangle(Triangle* fTriangle){
	Vec3 _center(0.f, 0.f, 0.f);
	
	for (int i = 0; i < 3; i++)	{
		_center = _center + fTriangle->vertices[i]->position;
	}
	_center = _center * 0.333f;

	Vertex* _vertex1 = fTriangle->vertices[1];
	Vertex* _vertex2 = fTriangle->vertices[2];

	for (auto& _tri : mTriangles)
	{
		if (_tri == nullptr) {
			continue;
		}
		for (int i = 0; i < 3; i++)
		{
			if (_tri->vertices[i] == _vertex1) {
				_tri->vertices[i] = fTriangle->vertices[0];
			}

			if (_tri->vertices[i] == _vertex2) {
				_tri->vertices[i] = fTriangle->vertices[0];
			}
		}

		if (_tri->vertices[0] == _tri->vertices[1] || _tri->vertices[1] == _tri->vertices[2] || _tri->vertices[0] == _tri->vertices[2]) {
			_tri = nullptr;
			continue;
		}
	}

	fTriangle->vertices[0]->position = _center;

	delete_vertex(_vertex1);
	delete_vertex(_vertex2);

	delete_triangle(fTriangle);
}

void Mesh::delete_vertex(Vertex* v){
	/*for (auto it: v->neighbor){
		it->neighbor.erase(v);
	}*/

	auto e = std::find(mVertices.begin(), mVertices.end(), v);
	if (e != mVertices.end()) {
		mVertices.erase(e);
	}
	//delete v;

}


void Mesh::delete_triangle(Triangle* fTriangle)
{
	for (auto it : mVertices)
	{
		auto e = std::find(it->face.begin(), it->face.end(), fTriangle);
		if (e != it->face.end())
		{
			it->face.erase(e);
		}
	}

	auto e = std::find(mTriangles.begin(), mTriangles.end(), fTriangle);
	if (e != mTriangles.end()) {
		*e = nullptr;
		//mTriangles.erase(e);
	}

	delete fTriangle;

}


bool Mesh::compareCost(Vertex* u, Vertex* v){
	return u->cost < v->cost;
}

