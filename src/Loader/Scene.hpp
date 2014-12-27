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
	//! \brief get the current scene
	static Scene* getScene();


	//! \brief Function to add a new object in a scene
	//! \param Object to place
	void addObject(const std::string fName, Object* fObject);

	//! \brief return a object
	//! \param name of the object
	//! \return return nullptr if the object can't be find
	Object* getObject(const std::string& fName);

	//! \brief render the scene
	void show();

	//! \brief get loader instance
	Loader* getLoader();

private:
	//! \brief Scene constructor for a new scene
	Scene();

	static Scene* mSceneInstance;
	Loader* mLoader;
	MainWindow* mWindow;

	std::map<std::string, Object*> mObjects;	
};

#endif