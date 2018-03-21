#version 330 core

// Define constants
#define M_PI 3.141593

//in vec3 vertNormal;
//in vec3 lightDir;
//in vec3 lightColorOut;
//in vec2 vTexCoords;

in vec3 vertNormal;
in vec3 vertPosition;
in vec3 relativeLightPosition;
in vec2 texCoords;

out vec4 fColor;

uniform sampler2D samplerUniform;
uniform vec3 lightColor;
uniform vec4 material;
uniform mat4 viewMatrix;

void main()
{
    vec3 textureColor = texture(samplerUniform, texCoords).xyz;

    // Ambient
    vec3 color = textureColor * material.x;

    // Calculate light direction vectors in the phong model.
    vec3 lightDirection   = normalize(relativeLightPosition - vertPosition);
    vec3 normal           = normalize(vertNormal);

    // Diffuse colour.
    float diffuseIntensity = max(dot(normal, lightDirection), 0);
    color += textureColor * material.y * diffuseIntensity;

    // Specular colour.
    vec3 cameraPos = vec3(viewMatrix[0][3], viewMatrix[1][3], viewMatrix[2][3]);
    vec3 viewDirection =  normalize(cameraPos - vertPosition);
    vec3 reflectDirection  = reflect(-lightDirection, normal);
    float specularIntensity = max(dot(reflectDirection, viewDirection), 0);
    color += textureColor * lightColor * material.z * pow(specularIntensity, material.w);

    fColor = vec4(color, 1);
}
