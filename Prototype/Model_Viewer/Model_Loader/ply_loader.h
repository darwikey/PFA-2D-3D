#ifndef PLY_LOADER_H
#define PLY_LOADER_H

#include "Point.h"

bool loadPLY(
    const char * path,
    std::vector<Coordinate3d> & out_vertices
);


#endif // PLY_LOADER_H
