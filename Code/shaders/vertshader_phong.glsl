#version 330 core

// Define constants
#define M_PI 3.141593

// Specify the input locations of attributes
layout (location = 0) in vec3 vertCoordinates_in;
layout (location = 1) in vec3 vertNormal_in;
layout (location = 2) in vec2 texCoords_in;

// Specify the Uniforms of the vertex shader
uniform mat4 modelTransform;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform mat3 normalMatrix;
uniform vec3 lightPosition;

out vec3 vertNormal;
out vec3 vertPosition;
out vec3 relativeLightPosition;
out vec2 texCoords;

void main()
{
    mat4 mvc = viewMatrix * modelTransform;
    gl_Position = projectionMatrix * mvc * vec4(vertCoordinates_in, 1.0);

    //Compute light ray
   relativeLightPosition = vec3(viewMatrix * vec4(lightPosition, 1));
   vertPosition = vec3(mvc * vec4(vertCoordinates_in, 1));
   vertNormal   = mat3(viewMatrix) * normalMatrix * vertNormal_in;
   texCoords    = texCoords_in;
}
