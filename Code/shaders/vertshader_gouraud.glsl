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
uniform vec4 material;

// Specify the output of the vertex stage
out float vSpecular;
out float vAmbient;
out float vDiffuse;
out vec2 vTexCoords;

void main()
{
    // Ambient component.
    vAmbient = material.x;
    mat4 mvc = viewMatrix * modelTransform;

    // Calculate light direction, vertex position and normal.
    vec3 vertexPosition        = vec3(mvc * vec4(vertCoordinates_in, 1));
    vec3 vertexNormal          = normalize(mat3(viewMatrix) * normalMatrix * vertNormal_in);
    vec3 relativeLightPosition = vec3(viewMatrix * vec4(lightPosition, 1));
    vec3 lightDirection        = normalize(relativeLightPosition - vertexPosition);

    // Diffuse component.
    float diffuseIntensity = max(dot(vertexNormal, lightDirection), 0);
    vDiffuse = material.y * diffuseIntensity;

    // Specular component.
    vec3 cameraPos = vec3(viewMatrix[0][3], viewMatrix[1][3], viewMatrix[2][3]);
    vec3 viewDirection =  normalize(cameraPos - vertexPosition);
    vec3 reflectDirection   = reflect(-lightDirection, vertexNormal);
    float specularIntensity = max(dot(viewDirection, reflectDirection), 0);
    vSpecular = material.z * pow(specularIntensity, material.w);

    vTexCoords = texCoords_in;
    gl_Position = projectionMatrix * mvc * vec4(vertCoordinates_in, 1);
}
