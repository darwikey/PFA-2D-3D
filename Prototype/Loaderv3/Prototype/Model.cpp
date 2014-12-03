#include "Model.hpp"
#include "PlyLoader.hpp"
#include "ObjLoader.hpp"
#include <QMessageBox>

Model::Model():vboStatus(0)
{


}

Model::Model(string filePath) : vboStatus(0),
m_fileName(filePath) {

    ObjLoader _loader (filePath);
    if(!_loader.load(this))
    {
        std::cerr << "Impossible to open the file ! Are you in the right path ?" << std::endl;
        QMessageBox::critical(0, "Error", "Error Opening File...");
    }
    else
    {
        computeColors();
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

void Model::computeColors() {
    if(vertices.size() > 0 && indices.size()>0){
        for(unsigned int i=0;i<vertices.size();i++)
        {
            GLfloat _f = (GLfloat) i/vertices.size();
            Vec3 _ColorMod =Vec3(_f,_f,_f);
            color.push_back(_ColorMod);
        }

    }
}
