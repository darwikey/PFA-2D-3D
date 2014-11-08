#ifndef OBJ_LOADER_H
#define OBJ_LOADER_H

#include "Point.h"

bool loadOBJ(
    const char * path,
    std::vector<Coordinate3d> & out_vertices,
    std::vector<Coordinate2d> & out_uvs,
    std::vector<Coordinate3d> & out_normals
);


#endif // OBJ_LOADER_H
