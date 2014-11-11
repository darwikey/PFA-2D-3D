#include "model.h"


Model::StructTriangle::StructTriangle() {
	vertices[0] = vertices[1] = vertices[2] = 0;
	uvs[0] = uvs[1] = uvs[2] = 0;
	normals[0] = normals[1] = normals[2] = 0;
}

Model::Model(string filePath){
    loadOBJ(filePath.c_str(), this);
    m_fileName = filePath;
}
