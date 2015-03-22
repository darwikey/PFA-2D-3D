#include "Mesh.hpp"
#include "Object.hpp"
#include <iostream>
#include <chrono>

Mesh::Vertex::Vertex(QVector3D fPosition) : position(fPosition) {
}



Mesh::Triangle::Triangle(Vertex* vertex1, Vertex* vertex2, Vertex* vertex3, QVector3D faceNormal) : normal(faceNormal), cost(0.f) {
	vertices[0] = vertex1;
	vertices[1] = vertex2;
	vertices[2] = vertex3;
}


bool Mesh::Triangle::isDegenerate() {
	return vertices[0] == vertices[1] 
		|| vertices[1] == vertices[2] 
		|| vertices[0] == vertices[2];
}


void Mesh::Triangle::computeCost() {
	/*QVector3D _edge1 = vertices[1]->position - vertices[0]->position;
	QVector3D _edge2 = vertices[2]->position - vertices[0]->position;
	
	// the cost is equal to the area of the triangle
	cost = QVector3D::crossProduct(_edge1, _edge2).lengthSquared();*/

	cost = vertices[0]->position.distanceToPoint(vertices[1]->position) + vertices[0]->position.distanceToPoint(vertices[2]->position) + vertices[1]->position.distanceToPoint(vertices[2]->position);

	// add a random coefficient to the cost, to avoird artefact
	float _random = ((float)rand() / (float)RAND_MAX);
	cost *= 1.f + 0.2f * (_random - 0.5f);
}


Mesh::Mesh(Object* fModel){
	std::vector<Mesh::Vertex*> _vertexByIndex;
	_vertexByIndex.reserve(fModel->mVertices.size());

	// for each vertex
	for(QVector3D& v: fModel->mVertices){
		Mesh::Vertex* _meshVertex = new Mesh::Vertex(v);
		mVertices.push_back(_meshVertex);
		_vertexByIndex.push_back(_meshVertex);
	}

	// for each triangle
	for (size_t i = 0; i < fModel->mIndices.size(); i += 3){
		if (i + 2 < fModel->mIndices.size()){
			uint _indice0 = fModel->mIndices[i];
			uint _indice1 = fModel->mIndices[i + 1];
			uint _indice2 = fModel->mIndices[i + 2];

			if (_indice0 < mVertices.size() && _indice1 < mVertices.size() && _indice2 < mVertices.size()){

				Mesh::Triangle* _tri = new Mesh::Triangle(nullptr, nullptr, nullptr, QVector3D(0, 0, 0));

				// for each vertex of the triangle
				_tri->vertices[0] = mVertices[_indice0];
				_tri->vertices[1] = mVertices[_indice1];
				_tri->vertices[2] = mVertices[_indice2];

				_tri->computeCost();
				

				//Compute the normal of the face
				/*QVector3D _edge1 = _tri->vertices[1]->position - _tri->vertices[0]->position;
				QVector3D _edge2 = _tri->vertices[2]->position - _tri->vertices[0]->position;
				_tri->normal = _edge1.crossProduct(_edge2);
				_tri->normal.normalise();*/

				mTriangles.push_back(_tri);
			}
		}
	}
}


Mesh::~Mesh()
{
	//TODO delete vertices & triangles
}




void Mesh::polygonReduction(size_t fPolygonDesired){
	std::cout << "Begin polygon reduction" << std::endl;
	std::cout << "number of triangles : " << mTriangles.size() << std::endl;
	auto _start = std::chrono::system_clock::now();

	while( mTriangles.size() > fPolygonDesired) {
		//find the vertex with the lowest cost
		Mesh::Triangle* _tri = mTriangles[rand()%mTriangles.size()];//*std::min_element(mTriangles.begin(), mTriangles.end(), &Triangle::compareCost);
		collapseTriangle(_tri);

		if (mTriangles.size()%100==0)
			std::cout<<mTriangles.size()<<std::endl;
	}

	auto _end = std::chrono::system_clock::now();
	std::cout << "duration : " << std::chrono::duration<double>(_end-_start).count() << " s" << std::endl;
	std::cout << "End polygon reduction"<< std::endl;
	std::cout << "number of triangles : " << mTriangles.size() << std::endl;
}


Object* Mesh::convertToModel(){
	Object* _model = new Object();
	
	for(auto _v: mVertices){
		_model->pushVertice(_v->position);
	}
	
	for(auto _tri: mTriangles){
		uint _modelTri[3];
		bool _fail = false;

		for (size_t i = 0; i < 3; i++) {
			auto it = std::find(mVertices.begin(), mVertices.end(), _tri->vertices[i]);

			// if we find the vertex
			if (it != mVertices.end()){
				_modelTri[i] = std::distance(mVertices.begin(), it);
			}
			else {
				_fail = true;
			}
		}

		// if everything is OK, add the triangle to the object
		if (!_fail) {
			for (size_t i = 0; i < 3; i++) {
				_model->pushIndice(_modelTri[i]);
			}
		}
	}

	_model->computeBoundingBox();

	return _model;
}


Mesh::Vertex* Mesh::findVertexByIndex(size_t fIndex) {
	if (fIndex < mVertices.size()) {
		size_t _index = 0;
		for (auto v : mVertices) {
			if (_index == fIndex) {
				return v;
			}
			_index++;
		}
	}

	return nullptr;
}


void Mesh::collapseTriangle(Mesh::Triangle* fTriangle){
	QVector3D _center(0.f, 0.f, 0.f);
	
	for (int i = 0; i < 3; i++)	{
		_center = _center + fTriangle->vertices[i]->position;
	}
	_center = _center / 3.f;

	Mesh::Vertex* _vertex1 = fTriangle->vertices[1];
	Mesh::Vertex* _vertex2 = fTriangle->vertices[2];

	for (auto _tri = mTriangles.begin(); _tri != mTriangles.end(); ){
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
	}

	fTriangle->vertices[0]->position = _center;

	for (auto _vertex = mVertices.begin(); _vertex != mVertices.end(); ) {
		if (*_vertex == _vertex1 || *_vertex == _vertex2) {
			_vertex = mVertices.erase(_vertex);
		}
		else {
			++_vertex;
		}
	}

	delete _vertex1;
	delete _vertex2;
	delete fTriangle;
}


bool Mesh::Triangle::compareCost(Triangle* u, Triangle* v){
	return u->cost < v->cost;
}

