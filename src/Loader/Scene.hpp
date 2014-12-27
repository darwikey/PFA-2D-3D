#ifndef SCENE_HPP
#define SCENE_HPP

#include "global.hpp"


class Object;
class Loader;
class MainWindow;

//! \class Scene
//! \brief The three dimension scene where objects will be placed
class Scene{
public:
	//! \brief Scene constructor for a new scene
	Scene();

	//! \brief Function to add a new object in a scene
	//! \param Object to place
	void addObject(Object* fObject);

	//! \brief render the scene
	void show();

private:
	Loader* mLoader;
	MainWindow* mWindow;

	std::vector<Object*> mObjects;	
};

#endif