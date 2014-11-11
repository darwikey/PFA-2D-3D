#include <vector>
#include <iostream>
#include "model.h"
#include "obj_loader.h"
#include <QtGui/QOpenGLShaderProgram>

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
    std::cout << "Loading OBJ file "<< fPath << "..." << std::endl;;

    //std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    //std::vector<Vec3> temp_vertices;
    //std::vector<Coordinate2d> temp_uvs;
    //std::vector<Vec3> temp_normals;
    GLfloat f1,f2,f3;

    FILE * file = fopen(fPath.c_str(), "r");
    if( file == NULL ){
        fprintf(stderr, "Impossible to open the file ! Are you in the right path ?\n");
        exit(EXIT_FAILURE);
        return false;
    }

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

        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            fscanf(file, "%f %f\n", &f1, &f2 );
            //f2 = -f2; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            Coordinate2d vertexTexture(f1,f2);
            fModel->uvs.push_back(vertexTexture);

        }else if ( strcmp( lineHeader, "vn" ) == 0 ){

            fscanf(file, "%f %f %f\n", &f1, &f2, &f3 );
            Vec3 vertexNormal(f1,f2,f3);
            fModel->normals.push_back(vertexNormal);

        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            //std::string vertex1, vertex2, vertex3;
			Model::StructTriangle tri;
            //unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &tri.vertices[0], &tri.uvs[0], &tri.normals[0], &tri.vertices[1], &tri.uvs[1], &tri.normals[1], &tri.vertices[2], &tri.uvs[2], &tri.normals[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
            }
			fModel->triangles.push_back(tri);
            //vertexIndices.push_back(vertexIndex[0]);
            //vertexIndices.push_back(vertexIndex[1]);
            //vertexIndices.push_back(vertexIndex[2]);
            //uvIndices    .push_back(uvIndex[0]);
            //uvIndices    .push_back(uvIndex[1]);
            //uvIndices    .push_back(uvIndex[2]);
            //normalIndices.push_back(normalIndex[0]);
            //normalIndices.push_back(normalIndex[1]);
            //normalIndices.push_back(normalIndex[2]);
        }else{

        }

    }

    // For each vertex of each triangle
    //for( unsigned int i=0; i<vertexIndices.size(); i++ ){

    //    // Get the indices of its attributes
    //    unsigned int vertexIndex = vertexIndices[i];
    //    unsigned int uvIndex = uvIndices[i];
    //    unsigned int normalIndex = normalIndices[i];

    //    // Get the attributes thanks to the index
    //    Vec3 vertex = temp_vertices[ vertexIndex-1 ];
    //    Coordinate2d vertexTexture = temp_uvs[ uvIndex-1 ];
    //    Vec3 vertexNormal = temp_normals[ normalIndex-1 ];

    //    // Put the attributes in buffers
    //    out_vertices.push_back(vertex);
    //    out_uvs     .push_back(vertexTexture);
    //    out_normals .push_back(vertexNormal);

    //}

    return true;
}
