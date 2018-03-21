#ifndef CUBE_H
#define CUBE_H

#include "object.h"


class Cube : public Object
{
public:
    Cube(GLuint VAO, GLuint VBO);
    void init();
};

#endif // CUBE_H
