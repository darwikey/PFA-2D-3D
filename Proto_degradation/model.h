#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include "obj_loader.h"
#include "Point.h"

class Model
{
public:
	struct StructTriangle{
		StructTriangle();
		uint vertices[3];
		uint uvs[3];
		uint normals[3];
	};

    std::vector<Vec3> vertices;
    std::vector<Coordinate2d> uvs;
    std::vector<Vec3> normals;
	std::vector<StructTriangle> triangles; 

	Model() {}
    Model(string filePath);


private:
	string m_fileName;

};

#endif // MODEL_H
