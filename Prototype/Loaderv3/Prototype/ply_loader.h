#ifndef PLY_LOADER_H
#define PLY_LOADER_H

#include "Point.hpp"
#include "Model.hpp"

class Model;

bool loadPLY(std::string fPath, Model* fModel);


#endif // PLY_LOADER_H
