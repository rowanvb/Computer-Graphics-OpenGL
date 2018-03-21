#include "sphere.h"


/**
 * @brief Sphere::init
 *
 * Intializes the sphere object by determining its vertices based on the .obj file.
 *
 */
void Sphere::init(){
    Model sphereModel = Model(":/models/sphere.obj");

    QVector<QVector3D> vertices = sphereModel.getVertices();

    float scale = 0.001f;

    for(QVector3D vertex : vertices){
        float r = ((float) rand() / (RAND_MAX));
        float g = ((float) rand() / (RAND_MAX));
        float b = ((float) rand() / (RAND_MAX));
        _bufferObject.push_back({vertex.x() * scale, vertex.y() * scale, vertex.z() * scale, r, g, b});
    }
}

Sphere::Sphere (GLuint VAO, GLuint VBO)  : Object(VAO, VBO)
{
    init();
}

