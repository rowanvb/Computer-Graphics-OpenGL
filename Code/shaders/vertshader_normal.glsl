#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelTransform;
uniform mat4 projectionMatrix;
uniform mat3 normalMatrix;

// Specify the output of the vertex stage
out vec3 vertNormal;

void main()
{
    gl_Position = projectionMatrix * modelTransform * vec4(vertCoordinates_in, 1.0);
    vertNormal = normalMatrix * vertNormal_in;
}
