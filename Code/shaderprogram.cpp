#include "shaderprogram.h"

GLint ShaderProgram::getUniformModel() const
{
    return uniformModel;
}

void ShaderProgram::setUniformModel(const GLint &value)
{
    uniformModel = value;
}

GLint ShaderProgram::getUniformProjection() const
{
    return uniformProjection;
}

void ShaderProgram::setUniformProjection(const GLint &value)
{
    uniformProjection = value;
}

GLint ShaderProgram::getUniformNormal() const
{
    return uniformNormal;
}

void ShaderProgram::setUniformNormal(const GLint &value)
{
    uniformNormal = value;
}

GLint ShaderProgram::getUniformView() const
{
    return uniformView;
}

void ShaderProgram::setUniformView(const GLint &value)
{
    uniformView = value;
}

GLint ShaderProgram::getUniformLightPosition() const
{
    return uniformLightPosition;
}

void ShaderProgram::setUniformLightPosition(const GLint &value)
{
    uniformLightPosition = value;
}

GLint ShaderProgram::getUniformMaterial() const
{
    return uniformMaterial;
}

void ShaderProgram::setUniformMaterial(const GLint &value)
{
    uniformMaterial = value;
}

GLint ShaderProgram::getUniformLightColor() const
{
    return uniformLightColor;
}

void ShaderProgram::setUniformLightColor(const GLint &value)
{
    uniformLightColor = value;
}

GLint ShaderProgram::getUniformSampler() const
{
    return uniformSampler;
}

void ShaderProgram::setUniformSampler(const GLint &value)
{
    uniformSampler = value;
}

ShaderProgram::ShaderProgram()
{
}
