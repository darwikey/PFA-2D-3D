#include <vector>
#include <iostream>
#include "Model.hpp"
#include "obj_loader.h"
#include <QtGui/QOpenGLShaderProgram>
#include <locale>

// Very, VERY simple OBJ loader.
// Here is a short list of features a real function would provide :
// - Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
// - Animations & bones (includes bones weights)
// - Multiple UVs
// - All attributes should be optional, not "forced"
// - More stable. Change a line in the OBJ file and it crashes.
// - More secure. Change another line and you can inject code.
// - Loading from memory, stream, etc

bool loadOBJ(std::string fPath, Model* fModel){
    std::locale::global(std::locale("POSIX"));
    std::cout << "Loading OBJ file "<< fPath << "..." << std::endl;;

    GLfloat f1,f2,f3;

    FILE * file = fopen(fPath.c_str(), "r");
    if( file == NULL ){
        fprintf(stderr, "Impossible to open the file ! Are you in the right path ?\n");
        exit(EXIT_FAILURE);
        return false;
    }
    Model::StructBoundingBox BoundingBox;
    while( 1 ){

        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if ( strcmp( lineHeader, "v" ) == 0 ){

            fscanf(file, "%f %f %f\n", &f1, &f2, &f3 );
            Vec3 vertex(f1,f2,f3);
            fModel->vertices.push_back(vertex);
            BoundingBox.x_min = (f1<BoundingBox.x_min)?f1:BoundingBox.x_min;
            BoundingBox.x_max = (BoundingBox.x_max<f1)?f1:BoundingBox.x_max;
            BoundingBox.y_min = (f2<BoundingBox.y_min)?f2:BoundingBox.y_min;
            BoundingBox.y_max = (BoundingBox.y_max<f2)?f2:BoundingBox.y_max;
            BoundingBox.z_min = (f3<BoundingBox.z_min)?f3:BoundingBox.z_min;
            BoundingBox.z_max = (BoundingBox.z_max<f3)?f3:BoundingBox.z_max;

        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            fscanf(file, "%f %f\n", &f1, &f2 );
            //f2 = -f2; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            Vec2 vertexTexture(f1,f2);
            fModel->uvs.push_back(vertexTexture);

        }else if ( strcmp( lineHeader, "vn" ) == 0 ){

            fscanf(file, "%f %f %f\n", &f1, &f2, &f3 );
            Vec3 vertexNormal(f1,f2,f3);
            fModel->normals.push_back(vertexNormal);

        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9){
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
            }

            fModel->indices.push_back(vertexIndex[0]-1);
            fModel->indices.push_back(vertexIndex[1]-1);
            fModel->indices.push_back(vertexIndex[2]-1);

        }else{

        }

    }
    fModel->BoundingBox=BoundingBox;


    return true;
}
