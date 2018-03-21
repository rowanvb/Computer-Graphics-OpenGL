#ifndef PYRAMID_H
#define PYRAMID_H
#include "object.h"

class Pyramid : public Object
{
public:
    Pyramid(GLuint VAO, GLuint VBO);
    void init();
};

#endif // PYRAMID_H
