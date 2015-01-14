#ifndef SCENE_HPP
#define SCENE_HPP

#include "global.hpp"
#include <QOpenGLBuffer>

class Object;
class Loader;
class MainWindow;
class SceneRenderer;
class Camera;

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

	//! \brief show the scene, this function must be called once
	void show();

	//! \brief render the scene, this function must be called each frame
	void render();

	//! \brief get scene renderer instance
	SceneRenderer* getSceneRenderer();

	//! \brief get loader instance
	Loader* getLoader();
	
	//! \brief get camera instance
	Camera* getCamera();

	
private:
	//! \brief Scene constructor for a new scene
	Scene();

	// Instances
	static Scene* mSceneInstance;
	Loader* mLoader;
	MainWindow* mWindow;
	SceneRenderer* mSceneRenderer;
	Camera* mCamera;

	std::map<std::string, Object*> mObjects;	
};

#endif
