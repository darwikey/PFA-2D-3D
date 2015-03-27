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

    //! \brief delete all the object given in parmameters
    //! \param List of the objects
    void deleteObjectsByName(QStringList fObjectList);

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

    //! \brief get the listmodel of the objects in the scene
    QStringListModel* getListObjects();

	//! \brief get the transform widget
	TransformWidget* getTransformWidget();

	//! \brief get the radius of the bounding sphere including all objects in the scene
	float getBoundingSphereRadius();

	//! \brief clear scene
	void clearScene();

    //! \brief to know if the actual scene is empty or not
    bool isEmptyScene();

	
	//! \brief When asked by the user, save the scene
	//! \param The name of the file where the user wants to save his scene (xml file)
	void saveScene(const std::string& fPath);

    //! \brief Create a scene from a save document
    //! \param The path to the save file
    void createScene(const QString &fPath);

	//! \brief tell if the scene have a name
    bool hasName();
    
	//! \brief set the scene name
	void setName(std::string fName);
    
	//! \brief return the scene name
	std::string getName();

	//! \brief set the path where the scene is saved
    void setPath(std::string fPath);

	//! \brief return the path where the scene is saved
    std::string getPath();

	//! \brief find the list of all object which have a local path
    std::vector<std::string> getLocalObjects();

private:
	//! \brief private scene constructor for a new scene
	Scene();
	~Scene();

	//! \brief process the xml and extract the 3D coordinates
	QVector3D nodeTreatment(QDomNode *fcurrent);
	
	//! \brief process the xml and extract the camera informations
	bool cameraTreatment(QDomNode *fcurrent);

	//! \brief process the xml and extract the object informations
	bool objectTreatment(QDomNode *fcurrent);

	//! \brief update the list of object contained in the scene
    void updateListObjects();
	
	
	// Instances
	static Scene* mSceneInstance;
	Loader* mLoader = nullptr;
	MainWindow* mWindow = nullptr;
	SceneRenderer* mSceneRenderer = nullptr;
	Camera* mCamera = nullptr;
    TransformWidget *mLandmark = nullptr;

	TransformWidget* mTransformWidget = nullptr;
    QStringList mObjectList;
    QStringListModel *mModelList = nullptr;

	std::atomic<std::map<std::string, Object*>*> mObjects;
    std::pair<std::string, Object*> mSelectedObject = std::make_pair(std::string(), nullptr);
	std::map<std::string, Object*> mDeletedObjects;

    std::vector<std::function<void()>> mActionTable;

    std::string mName;
    std::string mPath;
};

#endif
