#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "global.hpp"
#include "BoundingBox.hpp"
#include <QOpenGLBuffer>

class SceneRenderer;

//! \class Object
//! \brief definition of objects that will be placed in the scene
class Object {
public:
	//! \brief Construction of the object before filling it with points
	Object();

	//! \brief To move an object depending on three values on  x, y and z coordonates
	void moveObject(QVector3D fPosition);

	//! \brief Scaling of the object, following the given rate
	//! \param Rate for the scaling, considering the actual size of the object as rate 1
	void changeObjectScale(float fScale);

	//! \brief Moving the object from his initial orientation to a new orientation
	//! \param Two angles in radian are given on the horizontal plan and the vertical plan to move the object from his initial axe
	void changeObjectOrientation(float fHorizontalAngle, float fVerticalAngle);

	//! \brief initialize the vertex buffer object
	void initVbo(SceneRenderer* fRenderer);

    //! \brief init attribute
    void initAttributes(SceneRenderer* fRenderer);

	//! \brief init shader
	void initShader(SceneRenderer* fRenderer);

	//! \brief draw the object
	void draw(SceneRenderer* fRenderer);

	//! \brief fit the bounding box to the vertices
	void computeBoundingBox();

	//! \brief find the vertice color
	void computeColors();

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
	QVector3D getRotation();

	//! \brief get scale of the object
	float getScale();

	//! \brief tell if the vertex buffer object is initialized
	bool isVboInitialized();

	//! \brief get the shader of the object
	QOpenGLShaderProgram* getShader();

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


private:
	bool mIsSelected = false;
	BoundingBox mBoundingBox;
	QVector3D mPosition;
	QVector3D mRotation;
	float mScale = 1.f;
	
	std::vector<QVector3D> mVertices;
    std::vector<QVector2D> mTextureCoordinates;
    std::vector<QVector3D> mNormals;
    std::vector<uint> mIndices;
    std::vector<QVector3D> mColor;

	bool mIsVboInitialized = false;
    QOpenGLVertexArrayObject mVAO;
    QOpenGLBuffer  mVertexbuffer;
    QOpenGLBuffer  mColorbuffer;
    QOpenGLBuffer  mElementbuffer;

	QOpenGLShaderProgram* mShader = nullptr;
};


#endif
