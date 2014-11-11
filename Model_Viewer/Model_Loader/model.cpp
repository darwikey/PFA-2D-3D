#include "model.h"

Model::Model(string filePath)
{
        //loadOBJ(filePath.c_str(), vertices, uvs, normals);
        loadPLY(filePath.c_str(), vertices);
        m_fileName = filePath;
}
