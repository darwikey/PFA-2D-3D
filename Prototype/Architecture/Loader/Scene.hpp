#ifndef SCENE_HPP
#define SCENE_HPP

#include <cstdio>
#include "Object.hpp"

namespace Loader{
  // ! \class Scene
  // ! \brief The three dimension scene where objects will be placed
  class Scene{
  public:
    //! \brief Scene constructor for a new scene
    Scene();

    //! \brief Scene constructor for a loaded scene that had been started before
    Scene(<Objects>);

    //! \brief Function to add a new object in a scene
    //! \param Object to place
    void addObject(Object);

  private:
    <Objects> objects;	
  }

}
