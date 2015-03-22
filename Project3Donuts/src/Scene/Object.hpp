#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "global.hpp"
#include "BoundingBox.hpp"
#include <QOpenGLBuffer>



class SceneRenderer;

//! \class Object
//! \brief definition of objects that will be placed in the scene
class Object {
	friend class Mesh;
public:

	enum Shader{
		STANDARD_SHADING, DEBUG_NORMAL, COLORMAP, DEPTHMAP
	};

	//! \brief Construction of the object before filling it with points
	Object();

	//! \brief Construction of the object when it is loaded with a file
	Object(const std::string &fPath);

	//! \brief To move an object depending on three values on  x, y and z coordonates
	//! \param fUpdateCamera, update the camera position
	void moveObject(QVector3D fPosition, bool fUpdateCamera = false);

	//! \brief Scaling of the object
	//! \param Rate for the scaling, considering the actual size of the object as rate 1
	//! \param fUpdateCamera, update the camera position
	void changeObjectScale(float fScale, bool fUpdateCamera = false);

	//! \brief Scaling of the object
	//! \param scale along each axis, considering the actual size of the object as rate 1
	//! \param fUpdateCamera, update the camera position
	void changeObjectScale(QVector3D fScale, bool fUpdateCamera = false);

	//! \brief Moving the object from his initial orientation to a new orientation
	//! \param 3 euler angles in radian are given to move the object from his initial axe
	//! \param fUpdateCamera, update the camera position
	void changeObjectOrientation(QVector3D fRotation, bool fUpdateCamera = false);


	//! \brief initialize the vertex buffer object
	void initVbo(SceneRenderer* fRenderer);

    //! \brief init attribute
	void bindAttributes(SceneRenderer* fRenderer);

	//! \brief release atribute
	void releaseAttributes(SceneRenderer* fRenderer);

	//! \brief init shader
	void initShader(SceneRenderer* fRenderer);

	
	//! \brief draw the object
	void draw(SceneRenderer* fRenderer);

	//! \brief fit the bounding box to the vertices
	void computeBoundingBox();

	//! \brief find vertex colors
	void computeColors(QVector3D fColor = QVector3D(1, 1, 1));

	//! \brief normalize the stored data
	void normalizeData();

	//! \brief select the object
	//! \param select or not the object
	void selectObject(bool fIsSelected);

	//! \brief is selected by the user
	bool isObjectSelected();

	//! \brief return the object bounding box 
	BoundingBox getBoundingBox();

	//! \brief get position in the scene
	QVector3D getPosition();

	//! \brief get rotation in the scene
	//! \note in radian
	QVector3D getRotation();

	//! \brief get scale of the object
	QVector3D getScale();


	//! \brief tell if the vertex buffer object is initialized
	bool isVboInitialized();

	//! \brief switch the active shader
	static void switchShader(Object::Shader fShader);

	//! \brief get the shader of the object
	QOpenGLShaderProgram* getShader();

	//! \brief compute model matrix
	//! \param if fWithoutScaling is false, apply the scaling of the object on the matrix
	QMatrix4x4 getModelMatrix(bool fWithoutScaling = false);

	//! \brief add one vertex in the model
	void pushVertice(QVector3D fValue);

	//! \brief add one normal in the model
	void pushNormal(QVector3D fValue);

	//! \brief add one indice in the model
	void pushIndice(uint fValue);

	//! \brief add one vertex color in the model
	//! \note coordinates of fValue must be between 0 and 1
	void pushColor(QVector3D fValue);

	//! \brief add one texture coordinate in the model
	void pushTextureCoordinate(QVector2D fValue);

	//! \brief set the global colr of the object
	void setGlobalColor(QVector3D fColor);

	//! \brief set the global colr of the object
	QVector3D getGlobalColor();

	//! \brief return the path of the file 
    const std::string& getPath() const;


private:
	void loadShader(SceneRenderer* fRenderer, Object::Shader fShader, QString fVertexShaderPath, QString fFragmentShaderPath);

	//! \brief find vertex normals
	void computeNormals();


	bool mIsSelected = false;
	BoundingBox mBoundingBox;
	QVector3D mPosition;
	QVector3D mRotation; //in radian
	QVector3D mScale;
	
	std::vector<QVector3D> mVertices;
    std::vector<QVector2D> mTextureCoordinates;
    std::vector<QVector3D> mNormals;
    std::vector<uint> mIndices;
    std::vector<QVector3D> mVertexColor;
	QVector3D mGlobalColor = QVector3D(0.5f, 0.5f, 0.5f);

	bool mIsVboInitialized = false;
    QOpenGLVertexArrayObject mVAO;
    QOpenGLBuffer mVertexbuffer;
    QOpenGLBuffer mColorbuffer;
    //QOpenGLBuffer mIndexbuffer;
	QOpenGLBuffer mNormalBuffer;

	std::vector<QOpenGLShaderProgram*> mShaders;
	static Shader mActiveShader;
	Shader mCurrentShader = Shader::STANDARD_SHADING;

    std::string mPath;
};


#endif
