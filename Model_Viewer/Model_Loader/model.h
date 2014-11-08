#ifndef MODEL_H
#define MODEL_H

#include <QString>
#include "obj_loader.h"
#include "Point.h"

class Model
{
public:
    std::vector<Coordinate3d> vertices;
    std::vector<Coordinate2d> uvs;
    std::vector<Coordinate3d> normals;
    string m_fileName;
    Model() {}
    Model(string filePath);

    string fileName() const { return m_fileName; }
};

#endif // MODEL_H
