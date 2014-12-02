#include "Model.hpp"
#include "PlyLoader.hpp"
#include "ObjLoader.hpp"

Model::Model(string filePath) : vboStatus(0),
m_fileName(filePath) {

    ObjLoader _loader (filePath);
	_loader.load(this);

    //generating colors for better rendering
    GLfloat _color = 0.f;
    for(unsigned int i=0; i<vertices.size();i++) {
        Vec3 colors(_color, _color, _color);
        color.push_back(colors);
        _color = (GLfloat) i/indices.size();
    }

}


void Model::computeBoundingBox() {
	for (Vec3 _v : vertices)
	{
		BoundingBox.x_min = (_v.x < BoundingBox.x_min) ? _v.x : BoundingBox.x_min;
		BoundingBox.x_max = (BoundingBox.x_max < _v.x) ? _v.x : BoundingBox.x_max;
		BoundingBox.y_min = (_v.y < BoundingBox.y_min) ? _v.y : BoundingBox.y_min;
		BoundingBox.y_max = (BoundingBox.y_max < _v.y) ? _v.y : BoundingBox.y_max;
		BoundingBox.z_min = (_v.z < BoundingBox.z_min) ? _v.z : BoundingBox.z_min;
		BoundingBox.z_max = (BoundingBox.z_max < _v.z) ? _v.z : BoundingBox.z_max;
	}
}