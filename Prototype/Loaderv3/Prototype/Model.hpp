#ifndef MODEL_HPP
#define MODEL_HPP


#include <QString>
#include "Point.hpp"

class Model
{
public:

    struct StructBoundingBox{
        StructBoundingBox():x_min(0),x_max(0), y_min(0), y_max(0), z_min(0), z_max(0){}
        GLfloat x_min, x_max, y_min, y_max, z_min, z_max;
    };

    Model() ;
    Model(string filePath);

	void computeBoundingBox();
    void computeColors();

    std::vector<Vec3> vertices;
    std::vector<Vec2> uvs;
    std::vector<Vec3> normals;
    std::vector<uint> indices;

    std::vector<Vec3> color;

    StructBoundingBox BoundingBox;

    int vboStatus;
    GLuint vertexbuffer;
    GLuint colorbuffer;
    GLuint elementbuffer;

private:
    string m_fileName;
};

#endif // MODEL_HPP
