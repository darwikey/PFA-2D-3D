#include "Mesh.h"
#include "model.h"
#include <iostream>
#include <chrono>


Mesh::Vertex::Vertex(Vec3 fPosition) : position(fPosition) {
}



Mesh::Triangle::Triangle(Vertex* vertex1, Vertex* vertex2, Vertex* vertex3, Vec3 faceNormal) : normal(faceNormal), cost(0.f) {
	vertices[0] = vertex1;
	vertices[1] = vertex2;
	vertices[2] = vertex3;
}

bool Mesh::Triangle::hasVertex(Mesh::Vertex* v)
{
	return vertices[0] == v || vertices[1] == v || vertices[2] == v;
}

void Mesh::Triangle::replaceVertex(Mesh::Vertex* fOldVertex, Mesh::Vertex* fNewVertex)
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

bool Mesh::Triangle::isDegenerate() {
	return vertices[0] == vertices[1] 
		|| vertices[1] == vertices[2] 
		|| vertices[0] == vertices[2];
}


void Mesh::Triangle::computeCost() {
	Vec3 _edge1 = vertices[1]->position - vertices[0]->position;
	Vec3 _edge2 = vertices[2]->position - vertices[0]->position;
	
	// the cost is equal to the area of the triangle
	cost = _edge1.crossProduct(_edge2).length();
}


Mesh::Mesh(Model* fModel){
	mVertices.reserve(fModel->vertices.size());

	// for each vertex
	for(Vec3& v: fModel->vertices){
		Mesh::Vertex* _meshVertex = new Mesh::Vertex(v);
		mVertices.push_back(_meshVertex);
	}

	// for each triangle
	for(auto& _modelTri: fModel->triangles){

		Mesh::Triangle* _tri = new Mesh::Triangle(nullptr, nullptr, nullptr, Vec3(0, 0, 0));

		// for each vertex of the triangle
		for (int i = 0; i < 3; i++) {
			uint _index = _modelTri.vertices[i] - 1;
			if (_index < mVertices.size()) {
				_tri->vertices[i] = mVertices[_index];
			}
		}

		if (_tri->vertices[0] == nullptr || _tri->vertices[1] == nullptr || _tri->vertices[2] == nullptr){
			delete _tri;
			continue;
		}

		_tri->computeCost();

		//Compute the normal of the face
		/*Vec3 _edge1 = _tri->vertices[1]->position - _tri->vertices[0]->position;
		Vec3 _edge2 = _tri->vertices[2]->position - _tri->vertices[0]->position;
		_tri->normal = _edge1.crossProduct(_edge2);
		_tri->normal.normalise();*/

		//mTriangles.push_back(_tri);
		mTrianglesByCost.insert(std::pair<float, Mesh::Triangle*>(_tri->cost, _tri));

		// for each vertex of the triangle, link all the adjacent triangles
		for (int i = 0; i < 3; i++) {
			// we don't want duplicate triangle in our list 
			auto _find = std::find(_tri->vertices[i]->linkedTriangles.begin(), _tri->vertices[i]->linkedTriangles.end(), _tri);
			if (_find == _tri->vertices[i]->linkedTriangles.end()) {
				_tri->vertices[i]->linkedTriangles.push_back(_tri);
			}
		}
	}

}


Mesh::~Mesh()
{
	//TODO delete vertices & triangles
}




void Mesh::polygonReduction(size_t fPolygonDesired){
	std::cout<<"Begin polygon reduction"<<endl;
	auto _start = std::chrono::system_clock::now();
	int i = 0;

	while( mTrianglesByCost.size() > fPolygonDesired) {
		//find the vertex with the lowest cost
		//Mesh::Triangle* _tri = *std::min_element(mTriangles.begin(), mTriangles.end(), &Triangle::compareCost);
		Mesh::Triangle* _tri = mTrianglesByCost.begin()->second;

		collapseTriangle(_tri);

		//if (i % 1000==0)
			std::cout<<mTrianglesByCost.size()<<endl;
		i++;
	}

	auto _end = std::chrono::system_clock::now();
	std::cout<<"duration : " << std::chrono::duration<double>(_end-_start).count() << " s" << endl;
	std::cout<<"End polygon reduction"<<endl;
}


Model* Mesh::convertToModel(){
	Model* _model = new Model();
	
	for(auto _v: mVertices){
		_model->vertices.push_back(_v->position);
	}
	
	for(auto _tri: mTrianglesByCost){
		Model::StructTriangle _modelTri;
		bool _fail = false;

		for (size_t i = 0; i < 3; i++) {
			auto it = std::find(mVertices.begin(), mVertices.end(), _tri.second->vertices[i]);
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


void Mesh::collapseTriangle(Mesh::Triangle* fTriangle){
	Vec3 _center(0.f, 0.f, 0.f);
	
	// Recenter the first vertex of the triangle
	for (int i = 0; i < 3; i++)	{
		_center = _center + fTriangle->vertices[i]->position;
	}
	_center = _center * 0.333f;
	fTriangle->vertices[0]->position = _center;

	Mesh::Vertex* _vertex1 = fTriangle->vertices[1];
	Mesh::Vertex* _vertex2 = fTriangle->vertices[2];

	for (auto _tri = fTriangle->vertices[1]->linkedTriangles.begin(); _tri != fTriangle->vertices[1]->linkedTriangles.end(); ++_tri) {
		if (*_tri != fTriangle) {
			(*_tri)->replaceVertex(_vertex1, fTriangle->vertices[0]);
				
			if (0){//(*_tri)->isDegenerate()) {
				_tri = fTriangle->vertices[1]->linkedTriangles.erase(_tri);
				deleteTriangle(*_tri);
				//delete *_tri;
			}
			else {
				(*_tri)->computeCost();
			}
		}
		else {
			_tri = fTriangle->vertices[1]->linkedTriangles.erase(_tri);
		}
			
	}

	for (auto _tri = fTriangle->vertices[2]->linkedTriangles.begin(); _tri != fTriangle->vertices[2]->linkedTriangles.end(); ++_tri) {
		if (*_tri != fTriangle) {
			(*_tri)->replaceVertex(_vertex2, fTriangle->vertices[0]);
				
			if (0){//(*_tri)->isDegenerate()) {
				_tri = fTriangle->vertices[2]->linkedTriangles.erase(_tri);
				deleteTriangle(*_tri);
				//delete *_tri;
			}
			else {
				(*_tri)->computeCost();
			}
		}
		else {
			_tri = fTriangle->vertices[2]->linkedTriangles.erase(_tri);
		}
			
	}


	/*for (auto _tri = mTriangles.begin(); _tri != mTriangles.end(); ){
		for (int i = 0; i < 3; i++)
		{
			if ((*_tri)->vertices[i] == _vertex1) {
				(*_tri)->vertices[i] = fTriangle->vertices[0];
				(*_tri)->computeCost();
			}

			if ((*_tri)->vertices[i] == _vertex2) {
				(*_tri)->vertices[i] = fTriangle->vertices[0];
				(*_tri)->computeCost();
			}
		}

		// the triangle to collapse
		// and the triangles with only two vertex are deleted
		if (*_tri == fTriangle || (*_tri)->isDegenerate()){
			_tri = mTriangles.erase(_tri);
		}
		else {
			++_tri;
		}
	}*/


	for (auto _vertex = mVertices.begin(); _vertex != mVertices.end(); ) {
		if (*_vertex == _vertex1 || *_vertex == _vertex1) {
			_vertex = mVertices.erase(_vertex);
		}
		else {
			++_vertex;
		}
	}

	delete _vertex1;
	delete _vertex2;
	deleteTriangle(fTriangle);
	delete fTriangle;
}


void Mesh::deleteTriangle(Mesh::Triangle* fTriangle){
	auto _list = mTrianglesByCost.equal_range(fTriangle->cost);

	for (auto it = _list.first; it != _list.second; ++it) {
		if (it->second == fTriangle) {
			mTrianglesByCost.erase(it);
			return;
		}
	}
	return;
}

bool Mesh::Triangle::compareCost(Triangle* u, Triangle* v){
	return u->cost < v->cost;
}

