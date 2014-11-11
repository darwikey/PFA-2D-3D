#include "Mesh.h"
#include "model.h"


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
		for (int i = 0; i < 3; i++)
		{
			uint index = tri.vertices[i]-1;
			if (index < mVertices.size())
			{
				_tri->vertices[i] = mVertices[index];
			}
		}

		if (_tri->vertices[0] == nullptr || _tri->vertices[1] == nullptr || _tri->vertices[2] == nullptr){
			delete _tri;
			continue;
		}

		//Compute the normal of the face
		//TODO

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
	while(mVertices.size() > fPolygonDesired) {
		//find the vertex with the lowest cost
		Vertex* mn = *std::min_element(mVertices.begin(), mVertices.end(), &Mesh::compareCost);
		collapse(mn,mn->collapse);
	}
}


Model* Mesh::convertToModel(){
	Model* _model = new Model();
	
	for(auto _v: mVertices){
		_model->vertices.push_back(_v->position);
	}
	
	for(auto _tri: mTriangles){
		Model::StructTriangle _modelTri;

		for (size_t i = 0; i < 3; i++)
		{
			auto it = std::find(mVertices.begin(), mVertices.end(), _tri->vertices[i]);
			if (it != mVertices.end()){
				_modelTri.vertices[i] = 1 + std::distance(mVertices.begin(), it);
			}
		}

		_model->triangles.push_back(_modelTri);
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
			// use dot product of face normals.
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
}


void Mesh::collapse(Vertex *u, Vertex *v)
{
	// Collapse the edge uv by moving vertex u onto v
	if (!v){
		// u is a vertex all by itself so just delete it
		mVertices.erase(std::find(mVertices.begin(), mVertices.end(), u));
		delete u;
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
			delete(u->face[i]);
		}
	}

	// update remaining triangles to have v instead of u
	for (int i = u->face.size() - 1; i >= 0; i--){
		u->face[i]->replaceVertex(u, v);
	}

	delete_vertex(u);

	// recompute the edge collapse costs in neighborhood
	for (size_t i = 0; i < tmp.size(); i++){
		computeEdgeCostAtVertex(tmp[i]);
	}
}


void Mesh::delete_vertex(Vertex* v){
	for (auto it: v->neighbor){
		it->neighbor.erase(v);
	}

	mVertices.erase(std::find(mVertices.begin(), mVertices.end(), v));
	delete v;

}


bool Mesh::compareCost(Vertex* u, Vertex* v){
	return u->cost < v->cost;
}

