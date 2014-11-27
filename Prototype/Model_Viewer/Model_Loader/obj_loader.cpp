#include <vector>

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

bool loadOBJ(
    const char * path,
    std::vector<Coordinate3d> & out_vertices,
    std::vector<Coordinate2d> & out_uvs,
    std::vector<Coordinate3d> & out_normals
){
    printf("Loading OBJ file %s...\n", path);

    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<Coordinate3d> temp_vertices;
    std::vector<Coordinate2d> temp_uvs;
    std::vector<Coordinate3d> temp_normals;
    GLfloat f1,f2,f3;

    FILE * file = fopen(path, "r");
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
            Coordinate3d vertex(f1,f2,f3);
            temp_vertices.push_back(vertex);
        }else if ( strcmp( lineHeader, "vt" ) == 0 ){
            fscanf(file, "%f %f\n", &f1, &f2 );
            f2 = -f2; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            Coordinate2d vertexTexture(f1,f2);
            temp_uvs.push_back(vertexTexture);
        }else if ( strcmp( lineHeader, "vn" ) == 0 ){

            fscanf(file, "%f %f %f\n", &f1, &f2, &f3 );
            Coordinate3d vertexNormal(f1,f2,f3);
            temp_normals.push_back(vertexNormal);
        }else if ( strcmp( lineHeader, "f" ) == 0 ){
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
            if (matches != 9){
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }else{

        }

    }

    // For each vertex of each triangle
    for( unsigned int i=0; i<vertexIndices.size(); i++ ){

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        Coordinate3d vertex = temp_vertices[ vertexIndex-1 ];
        Coordinate2d vertexTexture = temp_uvs[ uvIndex-1 ];
        Coordinate3d vertexNormal = temp_normals[ normalIndex-1 ];

        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        out_uvs     .push_back(vertexTexture);
        out_normals .push_back(vertexNormal);

    }

    return true;
}

