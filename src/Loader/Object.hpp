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
	void moveObject(float fHorizontalValue, float fVerticalValue, float fDepthValue);

	//! \brief Scaling of the object, following the given rate
	//! \param Rate for the scaling, considering the actual size of the object as rate 1
	void changeObjectSize(float fRate);

	//! \brief Moving the object from his initial orientation to a new orientation
	//! \param Two angles in radian are given on the horizontal plan and the vertical plan to move the object from his initial axe
	void changeObjectOrientation(float fHorizontalAngle, float fVerticalAngle);

	//! \brief initialize the vertex buffer object
	void initVbo(SceneRenderer* fRenderer);

    //! \brief draw the object
    void initAttributes(SceneRenderer* fRenderer);

	//! \brief draw the object
	void draw(SceneRenderer* fRenderer);

	//! \brief fit the bounding box to the vertices
	void computeBoundingBox();

	//! \brief find the vertice color
	void computeColors();

	//! \brief return the object bounding box 
	BoundingBox getBoundingBox();

	//! \brief tell if the vertex buffer object is initialized
	bool isVboInitialized();

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
	BoundingBox mBoundingBox;
	
	std::vector<QVector3D> mVertices;
    std::vector<QVector2D> mTextureCoordinates;
    std::vector<QVector3D> mNormals;
    std::vector<uint> mIndices;
    std::vector<QVector3D> mColor;

	bool mIsVboInitialized = false;
    QOpenGLVertexArrayObject mVao;
    QOpenGLBuffer  mVertexbuffer;
    QOpenGLBuffer  mColorbuffer;
    QOpenGLBuffer  mElementbuffer;
};


#endif
