#ifndef SCENE_HPP
#define SCENE_HPP

#include "global.hpp"
#include <QOpenGLBuffer>
#include <QtXml/QDomNode>

class Object;
class Loader;
class MainWindow;
class SceneRenderer;
class Camera;
class TransformWidget;


//! \class Scene
//! \brief The three dimension scene where objects will be placed
class Scene{
public:
	//! \brief get the current scene
	static Scene* getScene();


	//! \brief Function to add a new object in a scene
	//! \param Object to place
	void addObject(const std::string& fName, Object* fObject);

	//! \brief return a object
	//! \param name of the object
	//! \return return nullptr if the object can't be find
	Object* getObject(const std::string& fName);

	//! \brief show the scene, this function must be called once
	void show();

	//! \brief render the scene, this function must be called each frame
	//! \param fRenderOnlyObject, don't render widgets and lamps
	//! \param the camera used to render, if null the function use the scene camera
	void render(bool fRenderOnlyObject = false, Camera* fCamera = nullptr);

	//! \brief select all the object touched by the mouse
	//! \param fMousePosition, position of the mouse in the screen
	void selectObjects(QVector2D fMousePosition);

    //! \brief select all the object given in parmameters
    //! \param List of the objects
    void selectObjectsByName(QStringList fObjectList);

	//! \brief return the name of the selected object
	std::string getNameSelectedObject();

	//! \brief delete the selected object
	void deleteSelectedObject();

	//! \brief register an new action
	void registerAction(std::function<void()> fAction);

    //! \brief revert the previous action
    void revertPreviousAction();

	//! \brief get scene renderer instance
	SceneRenderer* getSceneRenderer();

	//! \brief get loader instance
	Loader* getLoader();
	
	//! \brief get camera instance
	Camera* getCamera();

    //! \brief get the list of the objects in the scene
    QStringListModel* getListObjects();

	//! \brief get the transform widget
	TransformWidget* getTransformWidget();

	//! \brief get the radius of the bounding sphere including all objects in the scene
	float getBoundingSphereRadius();

    //! \brief to know if the actual scene is empty or not
    bool isEmptyScene();

	
	//! \brief When asked by the user, save the scene
	//! \param The name of the file where the user wants to save his scene (xml file)
	void saveScene(const std::string& fPath);

    //! \brief Create a scene from a save document
    //! \param The path to the save file
    void createScene(const QString &fPath);


private:
	//! \brief Scene constructor for a new scene
	Scene();
	~Scene();
	QVector3D nodeTreatment(QDomNode *fcurrent);
	
	bool cameraTreatment(QDomNode *fcurrent);

	bool objectTreatment(QDomNode *fcurrent);

    void updateListObjects();
	
	
	// Instances
	static Scene* mSceneInstance;
	Loader* mLoader = nullptr;
	MainWindow* mWindow = nullptr;
	SceneRenderer* mSceneRenderer = nullptr;
	Camera* mCamera = nullptr;

	TransformWidget* mTransformWidget = nullptr;
    QStringList mObjectList;
    QStringListModel *mModelList = nullptr;

	std::atomic<std::map<std::string, Object*>*> mObjects;
    std::pair<std::string, Object*> mSelectedObject = std::make_pair(std::string(), nullptr);
	std::map<std::string, Object*> mDeletedObjects;

    std::vector<std::function<void()>> mActionTable;
};

#endif
