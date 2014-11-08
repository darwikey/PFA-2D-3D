#include "model.h"

Model::Model(string filePath)
{
        loadOBJ(filePath.c_str(), vertices, uvs, normals);
        m_fileName = filePath;
}
