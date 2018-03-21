#version 330 core

// Define constants
#define M_PI 3.141593

in float vAmbient;
in float vDiffuse;
in float vSpecular;
in vec2 vTexCoords;

out vec4 fColor;

uniform vec3 lightColor;
uniform sampler2D samplerUniform;

void main()
{
    // Texture
    vec3 textureColor = texture(samplerUniform, vTexCoords).xyz;

    fColor = vec4(vAmbient * textureColor + (vSpecular + vDiffuse) * lightColor * textureColor, 1.0f);
}
