#include "pyramid.h"

/**
 * @brief Pyramid::init
 *
 * Intializes the pyramid object by determining its vertices
 */
void Pyramid::init(){
    Vertex top = {0,1,0,1,0,0};
    Vertex leftBottomFar = {-1,-1,-1,1,1,0};
    Vertex leftBottomNear = {-1,-1,1,0,1,0};
    Vertex rightBottomFar = {1,-1,-1,0,1,1};
    Vertex rightBottomNear = {1,-1,1,0,0,1};

    _bufferObject.push_back(top);
    _bufferObject.push_back(rightBottomFar);
    _bufferObject.push_back(leftBottomFar);

    _bufferObject.push_back(top);
    _bufferObject.push_back(leftBottomFar);
    _bufferObject.push_back(leftBottomNear);

    _bufferObject.push_back(rightBottomNear);
    _bufferObject.push_back(leftBottomNear);
    _bufferObject.push_back(rightBottomFar);

    _bufferObject.push_back(leftBottomNear);
    _bufferObject.push_back(leftBottomFar);
    _bufferObject.push_back(rightBottomFar);

    _bufferObject.push_back(rightBottomNear);
    _bufferObject.push_back(rightBottomFar);
    _bufferObject.push_back(top);

    _bufferObject.push_back(top);
    _bufferObject.push_back(leftBottomNear);
    _bufferObject.push_back(rightBottomNear);
}

Pyramid::Pyramid (GLuint VAO, GLuint VBO) : Object(VAO, VBO)
{
    init();
}
