#include "model.h"


Model::Model(string filePath){
    loadPLY(filePath.c_str(), this);
    m_fileName = filePath;
    //generating colors for better rendering

    GLfloat _color = 0.f;
    for(int i=0; i<vertices.size();i++)
    {
        Coordinate3d colors(_color, _color, _color);
        color.push_back(colors);
        _color += 0.f/indices.size();
    }

}
