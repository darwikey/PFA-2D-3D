#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include "obj_loader.h"
#include "ply_loader.h"
#include "Point.h"

class Model
{
public:

    struct StructBoundingBox{
        StructBoundingBox():x_min(0),x_max(0), y_min(0), y_max(0), z_min(0), z_max(0){}
        GLfloat x_min, x_max, y_min, y_max, z_min, z_max;
    };

    std::vector<Coordinate3d> vertices;
    std::vector<Coordinate2d> uvs;
    std::vector<Coordinate3d> normals;
    std::vector<uint> indices;
    StructBoundingBox BoundingBox;
	Model() {}
    Model(string filePath);
    GLuint vboId[2];
    GLuint elementbuffer;
    std::vector<Coordinate3d> color;


private:
	string m_fileName;

};

#endif // MODEL_H
