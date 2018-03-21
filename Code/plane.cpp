#include "plane.h"

void Plane::init(){
    Vertex v1 = {-1, 0, -1,
                 0, 1, 0,
                 0, 0};
    Vertex v2 = {-1, 0, 1,
                 0, 1, 0,
                 0, 1};
    Vertex v3 = {1, 0, 1,
                 0, 1, 0,
                 1, 1};
    Vertex v4 = {1, 0, -1,
                 0, 1, 0,
                 1, 0};

    _bufferObject.push_back(v1);
    _bufferObject.push_back(v2);
    _bufferObject.push_back(v3);

    _bufferObject.push_back(v1);
    _bufferObject.push_back(v3);
    _bufferObject.push_back(v4);

}

Plane::Plane(GLuint VAO, GLuint VBO, GLuint texture) : Object(VAO, VBO, texture)
{
    init();
}
