#ifndef CHARGEUR_HPP
#define CHARGEUR_HPP

#include"Model.hpp"
#include"Scene.hpp"
#include "singleton.h"

class Chargeur: public Singleton<Chargeur>
{
public:
    Chargeur();
    void newModel(const std::string& fName);
    Model* getModel(const std::string& fName);
};

#endif // CHARGEUR_HPP
