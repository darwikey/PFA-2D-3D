#include "SceneRenderer.hpp"
#include"Chargeur.hpp"
#include <iostream>

extern "C"{
    #include <unistd.h>
}

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
    glBufferData(GL_ARRAY_BUFFER, _model->vertices.size()*sizeof(Vec3), &(_model->vertices[0]), GL_STATIC_DRAW);

    glGenBuffers(1, &_model->colorbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _model->colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, _model->color.size() * sizeof(Vec3), &(_model->color[0]), GL_STATIC_DRAW);

    glGenBuffers(1, &_model->elementbuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _model->elementbuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _model->indices.size() * sizeof(uint), &(_model->indices[0]), GL_STATIC_DRAW);

    _model->vboStatus = 1;

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    const qreal retinaScale = devicePixelRatio();
    glViewport(0, 0, width() * retinaScale, height() * retinaScale);
}

void SceneRenderer::render()
{
    Model* _model = Chargeur::getInstance()->getModel("cube1");

    if(_model->vboStatus==0)
    {
        glGenBuffers(1, &_model->vertexbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _model->vertexbuffer);
        glBufferData(GL_ARRAY_BUFFER, _model->vertices.size()*sizeof(Vec3), &(_model->vertices[0]), GL_STATIC_DRAW);

        glGenBuffers(1, &_model->colorbuffer);
        glBindBuffer(GL_ARRAY_BUFFER, _model->colorbuffer);
        glBufferData(GL_ARRAY_BUFFER, _model->color.size() * sizeof(Vec3), &(_model->color[0]), GL_STATIC_DRAW);

        glGenBuffers(1, &_model->elementbuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _model->elementbuffer);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, _model->indices.size() * sizeof(uint), &(_model->indices[0]), GL_STATIC_DRAW);

        _model->vboStatus = 1;
    }
    glClear(GL_COLOR_BUFFER_BIT);

    if ( !m_program->bind())
      {
          qWarning() << "Could not bind shader program";
          return;
      }

    matrix = QMatrix4x4();

    GLdouble left = (_model->BoundingBox.x_max+_model->BoundingBox.x_min)/2 - (_model->BoundingBox.z_max-_model->BoundingBox.z_min);
    GLdouble right = (_model->BoundingBox.x_max+_model->BoundingBox.x_min)/2 + (_model->BoundingBox.z_max-_model->BoundingBox.z_min);
    GLdouble bottom = (_model->BoundingBox.y_max+_model->BoundingBox.y_min)/2 - (_model->BoundingBox.z_max-_model->BoundingBox.z_min);
    GLdouble top = (_model->BoundingBox.y_max+_model->BoundingBox.y_min)/2 + (_model->BoundingBox.z_max-_model->BoundingBox.z_min);
    GLfloat zNear = 0.01;
    GLfloat zFar = zNear + 100.0f;
    QVector3D eye = QVector3D(0., 0., 2*(_model->BoundingBox.z_max-_model->BoundingBox.z_min));
    QVector3D center = QVector3D((_model->BoundingBox.x_max+_model->BoundingBox.x_min)/2, (_model->BoundingBox.y_max+_model->BoundingBox.y_min)/2, (_model->BoundingBox.z_max+_model->BoundingBox.z_min)/2);
    QVector3D up = QVector3D(0.0, 1.0, 0.0);
    matrix.ortho(left, right, bottom, top, zNear, zFar);
    matrix.lookAt(eye, center, up);
    matrix.translate(fMoveLeftRight, fMoveUpDown, fMoveInOut);
    matrix.rotate(fRotationX, 1.0f, 0.0f, 0.0f);
    matrix.rotate(fRotationY, 0.0f, 1.0f, 0.0f);
    matrix.rotate(fRotationZ, 0.0f, 0.0f, 1.0f);

//    matrix.perspective(60.0f, 4.0f/3.0f, 0.1f, 100.0f);
//    matrix.translate(0, 0, -5);
//    matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);


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
