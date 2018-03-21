#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <QOpenGLShaderProgram>

class ShaderProgram : public QOpenGLShaderProgram
{
    GLint uniformModel;
    GLint uniformView;
    GLint uniformProjection;
    GLint uniformNormal;
    GLint uniformLightPosition;
    GLint uniformMaterial;
    GLint uniformLightColor;
    GLint uniformSampler;

public:
    ShaderProgram();

    GLint getUniformModel() const;
    void setUniformModel(const GLint &value);

    GLint getUniformProjection() const;
    void setUniformProjection(const GLint &value);

    GLint getUniformNormal() const;
    void setUniformNormal(const GLint &value);

    GLint getUniformView() const;
    void setUniformView(const GLint &value);

    GLint getUniformLightPosition() const;
    void setUniformLightPosition(const GLint &value);

    GLint getUniformMaterial() const;
    void setUniformMaterial(const GLint &value);

    GLint getUniformLightColor() const;
    void setUniformLightColor(const GLint &value);

    GLint getUniformSampler() const;
    void setUniformSampler(const GLint &value);
};

#endif // SHADERPROGRAM_H
