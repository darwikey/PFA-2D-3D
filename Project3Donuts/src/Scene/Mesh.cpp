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

	// add a random coefficient to the cost, to avoid artefact
	float _random = ((float)rand() / (float)RAND_MAX);
	cost *= 1.f + 0.2f * (_random - 0.5f);
}


Mesh::Mesh(Object* fModel){
	std::vector<Mesh::Vertex*> _vertexByIndex;
	_vertexByIndex.reserve(fModel->mVertices.size());

	// for each vertex
	for(QVector3D& v: fModel->mVertices){
		Mesh::Vertex* _meshVertex = new Mesh::Vertex(v);
		mVertices.insert(_meshVertex);
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
				_tri->vertices[0] = _vertexByIndex[_indice0];
				_tri->vertices[1] = _vertexByIndex[_indice1];
				_tri->vertices[2] = _vertexByIndex[_indice2];

				mTriangleByVertex.insert(std::make_pair(_vertexByIndex[_indice0], _tri));
				mTriangleByVertex.insert(std::make_pair(_vertexByIndex[_indice1], _tri));
				mTriangleByVertex.insert(std::make_pair(_vertexByIndex[_indice2], _tri));

				_tri->computeCost();
				
				mTriangles.insert(_tri);
			}
		}
	}
}


Mesh::~Mesh()
{
	for (auto it : mVertices){
		delete it;
	}

	for (auto it : mTriangles){
		delete it;
	}
}




void Mesh::polygonReduction(size_t fPolygonDesired){
	std::cout << "Begin polygon reduction" << std::endl;
	std::cout << "number of triangles : " << mTriangles.size() << std::endl;
	auto _start = std::chrono::system_clock::now();

	mTriangleIterator = mTriangles.begin();

	while( mTriangles.size() > fPolygonDesired) {
		//find the vertex with the lowest cost
		
		int _random = (rand() % 20) + 1;
		for (int i = 0; i < _random; i++){
			++mTriangleIterator;

			if (mTriangleIterator == mTriangles.end()){
				mTriangleIterator = mTriangles.begin();
			}
		}

		Mesh::Triangle* _tri = *mTriangleIterator;//[rand()%mTriangles.size()];//*std::min_element(mTriangles.begin(), mTriangles.end(), &Triangle::compareCost);
		collapseTriangle(_tri);

		//if (mTriangles.size()%100==0)
			//std::cout<<mTriangles.size()<<"  "<< mTriangleByVertex.size() <<std::endl;
	}

	auto _end = std::chrono::system_clock::now();
	std::cout << "duration : " << std::chrono::duration<double>(_end-_start).count() << " s" << std::endl;
	std::cout << "End polygon reduction"<< std::endl;
	std::cout << "number of triangles : " << mTriangles.size() << std::endl;
}


Object* Mesh::convertToModel(){
	Object* _model = new Object();
	
	std::map<Vertex*, uint> _indexByVertex;

	uint i = 0;
	for(auto _v: mVertices){
		_model->pushVertice(_v->position);
		_indexByVertex.insert(std::make_pair(_v, i));
		i++;
	}
	
	for(auto _tri: mTriangles){
		uint _modelTri[3];
		bool _fail = false;

		for (size_t i = 0; i < 3; i++) {
			auto it = mVertices.find(_tri->vertices[i]);

			// if we find the vertex
			if (it != mVertices.end()){
				_modelTri[i] = _indexByVertex.find(_tri->vertices[i])->second;
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


void Mesh::collapseTriangle(Mesh::Triangle* fTriangle){
	QVector3D _center(0.f, 0.f, 0.f);
	
	for (int i = 0; i < 3; i++)	{
		_center = _center + fTriangle->vertices[i]->position;
	}
	_center = _center / 3.f;

	Mesh::Vertex* _vertex1 = fTriangle->vertices[1];
	Mesh::Vertex* _vertex2 = fTriangle->vertices[2];

	collapseAtVertex(fTriangle, _vertex1);
	collapseAtVertex(fTriangle, _vertex2);
	

	// the triangle to collapse
	// and the triangles with only two vertex are deleted
	deleteTriangle(fTriangle);

	fTriangle->vertices[0]->position = _center;

	auto _it = mVertices.find(_vertex1);
	if (_it != mVertices.end()){
		mVertices.erase(_it);
	}
	
	_it = mVertices.find(_vertex2);
	if (_it != mVertices.end()){
		mVertices.erase(_it);
	}

	mTriangleByVertex.erase(_vertex1);
	mTriangleByVertex.erase(_vertex2);

	delete _vertex1;
	delete _vertex2;
	delete fTriangle;
}


void Mesh::collapseAtVertex(Mesh::Triangle* fTriangle, Mesh::Vertex* fVertex){
	auto _listTri = mTriangleByVertex.equal_range(fVertex);
	for (auto _tri = _listTri.first; _tri != _listTri.second; ++_tri){

		// if the triangle still exist
		if (mTriangles.find(_tri->second) != mTriangles.end()){

			for (int i = 0; i < 3; i++)
			{
				if (_tri->second->vertices[i] == fVertex) {
					_tri->second->vertices[i] = fTriangle->vertices[0];
					_tri->second->computeCost();

					if (_tri->second->isDegenerate()){
						deleteTriangle(_tri->second);
						break;
					}
					else{
						auto _list2 = mTriangleByVertex.equal_range(fTriangle->vertices[0]);
						bool _isAlready = false;
						for (auto _tri2 = _list2.first; _tri2 != _list2.second; ++_tri2){
							if (_tri2->second == _tri->second){
								_isAlready = true;
							}
						}
						if (!_isAlready){
							mTriangleByVertex.insert(std::make_pair(fTriangle->vertices[0], _tri->second));
						}
					}
				}
			}
		}
	}
}


bool Mesh::Triangle::compareCost(Triangle* u, Triangle* v){
	return u->cost < v->cost;
}


void Mesh::deleteTriangle(Mesh::Triangle* fTriangle){
	auto _triToErase = mTriangles.find(fTriangle);

	if (_triToErase != mTriangles.end()) {

		if (_triToErase == mTriangleIterator){
			++mTriangleIterator;
			if (mTriangleIterator == mTriangles.end()){
				mTriangleIterator = mTriangles.begin();
			}
		}

		mTriangles.erase(_triToErase);
	}
}