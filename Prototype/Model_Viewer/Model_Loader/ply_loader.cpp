#include "ply_loader.h"

#include <vector>
#include <QtGui/QOpenGLShaderProgram>

// Very, VERY simple PLY loader.
// Not all PLY files are supported.
// Only load simple ascii 1.0, float vertex with triangles faces PLY files.

bool loadPLY(
    const char * path,
    std::vector<Coordinate3d> & out_vertices
){


    printf("Loading PLY file %s...\n", path);

    std::vector<unsigned long> vertexIndices;
    std::vector<Coordinate3d> temp_vertices;
    GLfloat f1,f2,f3;

    FILE * file = fopen(path, "r");
    if( file == NULL ){
        fprintf(stderr, "Impossible to open the file ! Are you in the right path ?\n");
        exit(EXIT_FAILURE);
        return false;
    }


    //parsing the header file
    long vertex_number=0;
    long face_number=0;

    while( 1 ){

        char lineHeader[128];
        char lineType[128];
        // read the first word of the line
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF){
            printf("EOF detected, nothing done\n");
            break; // EOF = End Of File. Quit the loop.
        }
        // else : parse lineHeader
        if(strcmp( lineHeader, "end_header" ) == 0 )
        {
            printf("End of header detected\n");
            break;
        }
        else if(strcmp( lineHeader, "element" ) == 0 )
        {
            fscanf(file, "%s", lineType);
                if(strcmp( lineType, "vertex" ) == 0 )
                {
                    fscanf(file, "%ld\n", &vertex_number);
                    printf("%ld vertex found\n", vertex_number);
                }
                else if(strcmp( lineType, "face" ) == 0 )
                {
                    fscanf(file, "%ld\n", &face_number);
                    printf("%ld face found\n", face_number);
                }
        }

    }

    //then we parse vertex
    for(int i=0;i<vertex_number;i++)
    {
        fscanf(file, "%f %f %f\n", &f1, &f2, &f3);
        Coordinate3d vertex(f1,f2,f3);
        temp_vertices.push_back(vertex);
    }
    //Then we parse the faces

    int type_of_face;
    unsigned long vertexIndex[3];
    for(int i=0;i<face_number;i++)
    {

        fscanf(file, "%d %ld %ld %ld\n", &type_of_face, &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
        if (type_of_face != 3){
            printf("File can't be read by our simple parser :-( Try exporting with other options\n");
            return false;
        }
        vertexIndices.push_back(vertexIndex[0]);
        vertexIndices.push_back(vertexIndex[1]);
        vertexIndices.push_back(vertexIndex[2]);
    }
    //Then we gather our vertex according to the faces informations.
    for( unsigned long i=0; i<vertexIndices.size(); i++ ){

        // Get the indices of its attributes
        unsigned long vertexIndex = vertexIndices[i];

        // Get the attributes thanks to the index
        Coordinate3d vertex = temp_vertices[ vertexIndex];

        // Put the attributes in buffers
        out_vertices.push_back(vertex);

    }
    return true;
}
