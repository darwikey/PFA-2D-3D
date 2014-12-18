#include "SceneRenderer.hpp"
#include"Chargeur.hpp"
#include <iostream>
#include <qopenglfunctions_3_1.h>


static const char *vertexShaderSource =
        "#version 330 core\n"
        "layout(location = 0) in vec3 vertexPosition_modelspace;\n"
    "layout(location = 1) in vec3 vertexColor;\n"
        "out vec3 fragmentColor;\n"
    "uniform mat4 matrix;\n"
    "void main() {\n"
    "   gl_Position = matrix * vec4(vertexPosition_modelspace,1);\n"
        "fragmentColor = vertexColor;\n"
    "}\n";

static const char *fragmentShaderSource =
        "#version 330 core\n"
        "in vec3 fragmentColor;\n"
        "out vec3 color;\n"
    "void main() {\n"
        "color = fragmentColor;\n"
    "}\n";


SceneRenderer::SceneRenderer()
    : m_program(0)
    , m_frame(0)
{

}


GLuint SceneRenderer::loadShader(GLenum type, const char *source)
{
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, 0);
    glCompileShader(shader);
    return shader;
}

void SceneRenderer::initialize()
{
    m_program = new QOpenGLShaderProgram(this);
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
    //m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, "StandardShading.vertexshader");
    //m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, "StandardShading.fragmentshader");
    //m_program->bindAttributeLocation("vertexColor",1);
    //m_program->bindAttributeLocation("vertexPosition_modelspace",0);

    qDebug() << m_program->log();

    m_program->link();
    m_matrixUniform = m_program->uniformLocation("matrix");
    Model* _model = Chargeur::getInstance()->getModel("cube1");
    glGenBuffers(1, &_model->vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _model->vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, _model->vertices.size()*sizeof(Vec3), _model->vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &_model->colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _model->colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, _model->color.size() * sizeof(Vec3), _model->color.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &_model->elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _model->elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _model->indices.size() * sizeof(uint), _model->indices.data(), GL_STATIC_DRAW);

    _model->vboStatus = 1;

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);



	// The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
	GLuint FramebufferName = 0;
	glGenFramebuffers(1, &FramebufferName);
	glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

	// The texture we're going to render to
	GLuint renderedTexture;
	glGenTextures(1, &renderedTexture);

	// "Bind" the newly created texture : all future texture functions will modify this texture
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" )
	glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, 1024, 768, 0,GL_RGB, GL_UNSIGNED_BYTE, 0);

	// Poor filtering. Needed !
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


	// The depth buffer
	GLuint depthrenderbuffer;
	glGenRenderbuffers(1, &depthrenderbuffer);
	glBindRenderbuffer(GL_RENDERBUFFER, depthrenderbuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1024, 768);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthrenderbuffer);


	// Set "renderedTexture" as our colour attachement #0
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = {GL_COLOR_ATTACHMENT0};
	glDrawBuffers(1, DrawBuffers); // "1" is the size of DrawBuffers
}

void SceneRenderer::render()
{
    Model* _model = Chargeur::getInstance()->getModel("cube1");

    if(_model->vboStatus==0)
    {
        glGenBuffers(1, &_model->vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _model->vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, _model->vertices.size()*sizeof(Vec3), _model->vertices.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &_model->colorbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _model->colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, _model->color.size() * sizeof(Vec3), _model->color.data(), GL_STATIC_DRAW);

        glGenBuffers(1, &_model->elementbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _model->elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _model->indices.size() * sizeof(uint), _model->indices.data(), GL_STATIC_DRAW);
        _model->vboStatus = 1;
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if ( !m_program->bind())
      {
          qWarning() << "Could not bind shader program";
          return;
      }

    matrix = QMatrix4x4();

    GLdouble centerx = (_model->BoundingBox.x_max+_model->BoundingBox.x_min)/2;
    GLdouble centery = (_model->BoundingBox.y_max+_model->BoundingBox.y_min)/2;
    GLdouble centerz = (_model->BoundingBox.z_max+_model->BoundingBox.z_min)/2;
    GLdouble r = sqrt(((centerx - _model->BoundingBox.x_max)*(centerx - _model->BoundingBox.x_max))+((centery - _model->BoundingBox.y_max)*(centery - _model->BoundingBox.y_max))+((centerz - _model->BoundingBox.z_max)*(centerz - _model->BoundingBox.z_max)));

    GLfloat fDistance = r / 0.57735f; // where 0.57735f is tan(30 degrees)

    GLfloat zNear = fDistance - r;
    GLfloat zFar = fDistance + r;

    //printf("bounding box : x -- %f, %f, y -- %f, %f, z -- %f, %f\n",_model->BoundingBox.x_max,_model->BoundingBox.x_min,_model->BoundingBox.y_max,_model->BoundingBox.y_min,_model->BoundingBox.z_max,_model->BoundingBox.z_min);
    //printf("center : %lf, %lf, %lf\n", centerx, centery, centerz);
    //printf("r : %lf, dist : %f, zNear : %f, zFar : %f\n",r, fDistance, zNear, zFar);
    QVector3D eye = QVector3D(0., 0., fDistance);
    QVector3D center = QVector3D(0., 0., 0.);
    QVector3D up = QVector3D(0.0, 1.0, 0.0);


    matrix.frustum(-r, +r, -r, +r, zNear, zFar);
    matrix.lookAt(eye, center, up);
    matrix.translate(-centerx, -centery, -centerz);
    matrix.translate(fMoveLeftRight, fMoveUpDown, fMoveInOut);
    matrix.rotate(fRotationX, 1.0f, 0.0f, 0.0f);
    matrix.rotate(fRotationY, 0.0f, 1.0f, 0.0f);
    matrix.rotate(fRotationZ, 0.0f, 0.0f, 1.0f);



    m_program->setUniformValue(m_matrixUniform, matrix);

    glEnableVertexAttribArray(0);
    // Index buffer
     glBindBuffer(GL_ARRAY_BUFFER, _model->vertexbuffer);

     // Draw the triangles !


     glVertexAttribPointer(
         0,                  // attribute
         3,                  // size
         GL_FLOAT,           // type
         GL_FALSE,           // normalized?
         0,                  // stride
         (void*)0            // array buffer offset
     );

     // 2nd attribute buffer : colors
     glEnableVertexAttribArray(1);
     glBindBuffer(GL_ARRAY_BUFFER, _model->colorbuffer);
     glVertexAttribPointer(
         1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
         3,                                // size
         GL_FLOAT,                         // type
         GL_FALSE,                         // normalized?
         0,                                // stride
         (void*)0                          // array buffer offset
     );

//        glDrawArrays(GL_TRIANGLES, 0, _model->vertices.size() );
     //not working, no shader
     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _model->elementbuffer);
     // Draw the triangles !
     glDrawElements(
         GL_TRIANGLES,      // mode
         _model->indices.size(),    // count
         GL_UNSIGNED_INT,   // type
         (void*)0           // element array buffer offset
     );


    //glDrawArrays(GL_TRIANGLES, 0, _model->vertices.size()*3);


    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    m_program->release();

    ++m_frame;
}
