#ifndef MESH_H
#define MESH_H

#include "object.h"
#include "model.h"

class Sphere : public Object
{
public:
    Sphere(GLuint VAO, GLuint VBO);
    void init();
};

#endif // SPHERE_H
