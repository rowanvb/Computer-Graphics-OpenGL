#ifndef PLANE_H
#define PLANE_H
#include "object.h"

class Plane : public Object
{
public:
    Plane(GLuint VAO, GLuint VBO, GLuint texture);
    void init();
};

#endif // PLANE_H
