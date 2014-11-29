#include "Model.hpp"

Model::Model(string filePath):vboStatus(0){
    loadPLY(filePath.c_str(), this);
    m_fileName = filePath;
    //generating colors for better rendering

    GLfloat _color = 0.f;
    for(unsigned int i=0; i<vertices.size();i++)
    {
        Vec3 colors(_color, _color, _color);
        color.push_back(colors);
        _color = (GLfloat) i/indices.size();
    }

}
