#include "cube.h"

/**
 * @brief Cube::init
 *
 * Intializes the cube object by determining its vertices
 *
 */
void Cube::init(){
    Vertex leftTopFar = {-1,1,-1,1,0,0};
    Vertex leftTopNear = {-1,1,1,0,1,0};
    Vertex leftBottomFar = {-1,-1,-1,0,0,1};
    Vertex leftUnderNear = {-1,-1,1,1,1,0};

    Vertex rightTopFar = {1,1,-1,0,1,0};
    Vertex rightTopNear = {1,1,1,1,0,1};
    Vertex rightBottomFar = {1,-1,-1,0,0,1};
    Vertex rightBottomNear = {1,-1,1,1,1,0};

    _bufferObject.push_back(rightBottomNear);
    _bufferObject.push_back(rightBottomFar);
    _bufferObject.push_back(rightTopNear);

    _bufferObject.push_back(rightBottomFar);
    _bufferObject.push_back(rightTopFar);
    _bufferObject.push_back(rightTopNear);

    _bufferObject.push_back(leftBottomFar);
    _bufferObject.push_back(leftTopFar);
    _bufferObject.push_back(rightBottomFar);

    _bufferObject.push_back(leftTopFar);
    _bufferObject.push_back(rightTopFar);
    _bufferObject.push_back(rightBottomFar);

    _bufferObject.push_back(leftBottomFar);
    _bufferObject.push_back(leftUnderNear);
    _bufferObject.push_back(leftTopNear);

    _bufferObject.push_back(leftTopNear);
    _bufferObject.push_back(leftTopFar);
    _bufferObject.push_back(leftBottomFar);

    _bufferObject.push_back(leftTopNear);
    _bufferObject.push_back(rightTopNear);
    _bufferObject.push_back(leftTopFar);

    _bufferObject.push_back(leftTopFar);
    _bufferObject.push_back(rightTopNear);
    _bufferObject.push_back(rightTopFar);

    _bufferObject.push_back(leftUnderNear);
    _bufferObject.push_back(leftBottomFar);
    _bufferObject.push_back(rightBottomNear);

    _bufferObject.push_back(leftBottomFar);
    _bufferObject.push_back(rightBottomFar);
    _bufferObject.push_back(rightBottomNear);

    _bufferObject.push_back(leftUnderNear);
    _bufferObject.push_back(rightBottomNear);
    _bufferObject.push_back(leftTopNear);

    _bufferObject.push_back(leftTopNear);
    _bufferObject.push_back(rightBottomNear);
    _bufferObject.push_back(rightTopNear);
}

Cube::Cube(GLuint VAO, GLuint VBO) : Object(VAO, VBO)
{
    init();
}
