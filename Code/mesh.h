#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"
#include "model.h"

class Mesh : public Object
{
public:
    Mesh(QString filename, const GLuint &VAO, const GLuint &VBO, const GLuint &texture);
    void init(QString filename);
};

#endif // MESH_H
