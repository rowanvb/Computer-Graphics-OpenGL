#ifndef OBJECT_H
#define OBJECT_H

#include <QOpenGLWidget>
#include <QVector3D>
#include <QMatrix4x4>
#include "vertex.h"
#include "material.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class Object : public QObject
{
    QString _objectID;

    QMatrix4x4 _transformationMatrix;
    QMatrix3x3 _normalMatrix;

    QVector3D _translation;
    QVector3D _originalPosition;

    Material _material; // diffuse coef, etc..

    float _rotation = 0.f;
    float _rotationSpeed = 1.f;
    QVector3D _rotationVector = {0, 0, 0};
    float _velocity = 0.0f;
    float _gravitation = 0.02f;
    float _scale = 1.0f;
    float _restitution = 0.85f;
    float _userDefinedZero = 0.0f;

    bool still = false;


public:
    Object(){}
    ~Object();
    Object(const Object &object);
    Object(const GLuint &VAO, const GLuint &VBO);
    Object(const GLuint &VAO, const GLuint &VBO, const GLuint &texture);

    virtual void init(){}
    void transform(bool update);
    void reset();

    size_t getNumVertices() const { return _bufferObject.size(); }

    QMatrix4x4 getTransformationMatrix() const;
    void setTransformationMatrix(const QMatrix4x4 &transformationMatrix);

    QMatrix3x3 getNormalMatrix() const;
    void setNormalMatrix(const QMatrix3x3 &normalMatrix);

    QVector3D getTranslation() const;
    void setTranslation(const QVector3D &translation);

    Material getMaterial() const;
    void setMaterial(const Material &material);

    std::vector<Vertex> getBufferObject() const;

    GLuint getVBO() const;

    GLuint getVAO() const;

    float getRotation() const;
    void setRotation(float rotation);

    float getRotationSpeed() const;
    void setRotationSpeed(float rotationSpeed);

    float getGravitation() const;
    void setGravitation(float gravitation);

    QVector3D getOriginalPosition() const;
    void setOriginalPosition(const QVector3D &originalPosition);

    QString getObjectID() const;
    void setObjectID(const QString &objectID);

    QVector3D getRotationVector() const;
    void setRotationVector(const QVector3D &rotationVector);

    GLuint getTexture() const;
    void setTexture(const GLuint &texture);

    float getScale() const;
    void setScale(float value);

    float getRestitution() const;
    void setRestitution(float restitution);

    void setUserDefinedZero(float userDefinedZero);

protected:
    GLuint _VBO;
    GLuint _VAO;
    GLuint _texture;
    std::vector<Vertex> _bufferObject;

private:
    void updateVariables();
    void updateGravity();
};

Q_DECLARE_METATYPE(Object)

#endif // OBJECT_H
