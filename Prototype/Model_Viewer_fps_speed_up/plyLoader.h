#ifndef PLY_LOADER_H
#define PLY_LOADER_H

#include "Point.h"
#include "Model.h"

class Model;

bool loadPLY(std::string fPath, Model* fModel);


#endif // PLY_LOADER_H
