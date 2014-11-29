#ifndef SCENE_HPP
#define SCENE_HPP

#include "Model.hpp"
#include "Camera.hpp"
#include "singleton.h"

class Scene : public Singleton<Scene>
{

public:
    Scene();
    map<std::string, Model*> mModels;
    Camera mCamera;
};

#endif // SCENE_HPP
