#include <iostream>
#include <vector>
#include <QtGui/QOpenGLShaderProgram>

#include "plyLoader.h"

// Very, VERY simple PLY loader.
// Not all PLY files are supported.
// Only load simple ascii 1.0, float vertex with triangles faces PLY files.

bool loadPLY(std::string fPath, Model* fModel) {


  std::cout << "Loading PLY file "<< fPath << "..." << std::endl;;

  //std::vector<unsigned long> vertexIndices;
  //std::vector<Coordinate3d> temp_vertices;
  GLfloat f1,f2,f3;

  FILE * file = NULL;

  if((file = fopen(fPath.c_str(), "r")) == NULL) {
    fprintf(stderr, "Impossible to open the file ! Are you in the right dir ?\n");
    exit(EXIT_FAILURE);
    return false;
  }

  std::cout << "fopen done " << std::endl;;

  Model::StructBoundingBox BoundingBox;

  //parsing the header file
  long vertex_number = 0;
  long face_number = 0;

  while(1) {

    char lineHeader[128];
    char lineType[128];

    // read the first word of the line
    int res = fscanf(file, "%s", lineHeader);

    if (res == EOF) {
      printf("EOF detected, nothing done\n");
      break; // EOF = End Of File. Quit the loop.
    }

    // else : parse lineHeader
    if(strcmp(lineHeader, "end_header") == 0) {
      fgetc(file);
      printf("End of header detected\n");
      break;
    }

    else if(strcmp(lineHeader, "element") == 0) {

      fscanf(file, "%s", lineType);

      if(strcmp(lineType, "vertex") == 0) {
	fscanf(file, "%ld\n", &vertex_number);
	printf("%ld vertex found\n", vertex_number);
      }

      else if(strcmp(lineType, "face") == 0) {
	fscanf(file, "%ld\n", &face_number);
	printf("%ld face found\n", face_number);
      }
    }
  }

  std::cout << "Header ok " << std::endl;;

  //then we parse vertex

  for(int i=0;i<vertex_number;i++) {

    fscanf(file, "%f %f %f\n", &f1, &f2, &f3);

    Coordinate3d vertex(f1,f2,f3);

    fModel->vertices.push_back(vertex);
    BoundingBox.x_min = (f1<BoundingBox.x_min)?f1:BoundingBox.x_min;
    BoundingBox.x_max = (BoundingBox.x_max<f1)?f1:BoundingBox.x_max;
    BoundingBox.y_min = (f2<BoundingBox.y_min)?f2:BoundingBox.y_min;
    BoundingBox.y_max = (BoundingBox.y_max<f2)?f2:BoundingBox.y_max;
    BoundingBox.z_min = (f3<BoundingBox.z_min)?f3:BoundingBox.z_min;
    BoundingBox.z_max = (BoundingBox.z_max<f3)?f3:BoundingBox.z_max;
  }
  std::cout << "Vertex ok " << std::endl;;
  //Then we parse the faces

  int type_of_face = 1;

  for(int i=0;i<face_number;i++)
    {
      unsigned int vertexIndex[3];
      fscanf(file, "%d %d %d %d\n", &type_of_face, &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);

      if (type_of_face != 3){
	printf("File can't be read by our simple parser :-( Try exporting with other options\n");
	return false;
      }
      fModel->indices.push_back(vertexIndex[0]);
      fModel->indices.push_back(vertexIndex[1]);
      fModel->indices.push_back(vertexIndex[2]);
    }
  std::cout << "Face ok " << std::endl;;
  //Then we gather our vertex according to the faces informations.
  /*    for( unsigned long i=0; i<vertexIndices.size(); i++ ){

  // Get the indices of its attributes
  unsigned long vertexIndex = vertexIndices[i];

  // Get the attributes thanks to the index
  Coordinate3d vertex = temp_vertices[ vertexIndex];

  // Put the attributes in buffers
  out_vertices.push_back(vertex);

  }*/
  fModel->BoundingBox=BoundingBox;
  std::cout << "Now leaving " << std::endl;;
  return true;
}
