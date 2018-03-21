#include <cmath>
#include "object.h"

/**
 * @brief Object::Object
 *
 * Constructor for the Object class, links the VAO and VBO to the object.
 *
 * @param VAO VAO that can be used to store the VBO
 * @param VBO VBO that can be used to store the vertices
 */
Object::Object(const GLuint &VAO, const GLuint &VBO){
    _VAO = VAO;
    _VBO = VBO;
}

Object::Object(const GLuint &VAO, const GLuint &VBO, const GLuint &texture){
    _VAO = VAO;
    _VBO = VBO;
    _texture = texture;
}

/**
 * @brief Object::transform updates transformation based on currently set variables
 * @param update update the parameters
 */
void Object::transform(bool update)
{
    if (update)
        updateVariables();

    _transformationMatrix.setToIdentity();
    _translation += QVector3D(0, _velocity, 0);
    _transformationMatrix.translate(_translation);
    _transformationMatrix.scale(_scale);
    _transformationMatrix.rotate(QQuaternion::fromEulerAngles(_rotationVector + QVector3D(0, _rotation , 0)));
    _normalMatrix = _transformationMatrix.normalMatrix();
}

void Object::updateGravity() {
    // define the zero point. Object is unitized, so scale == size;
    float distanceToZero = _translation.y() - _scale - _userDefinedZero;

    if (fabs(_velocity) < _gravitation && distanceToZero < 0.00001){
        still = true; // no longer evaluating the gravity since the object is laying still.
        _velocity = 0;
        return;
    }
    if (distanceToZero + _velocity <= 0) { // Hit the zero point.
        if (_velocity < -_gravitation){
            _velocity -= distanceToZero / -_velocity * _gravitation;
            _velocity = -_velocity * _restitution; // 0 < restitution =< 1
        }
    }
    else
        _velocity -= _gravitation;
}

void Object::updateVariables()
{
    _rotation = fmod(_rotation + 1.f * _rotationSpeed, 360.f);
    if (!still)
        updateGravity();
}

void Object::reset(){
    _rotation = 0;
    _velocity = 0;
    still = false;
    _translation = _originalPosition;
}

QMatrix4x4 Object::getTransformationMatrix() const
{
    return _transformationMatrix;
}

void Object::setTransformationMatrix(const QMatrix4x4 &transformationMatrix)
{
    _transformationMatrix = transformationMatrix;
}

QMatrix3x3 Object::getNormalMatrix() const
{
    return _normalMatrix;
}

void Object::setNormalMatrix(const QMatrix3x3 &normalMatrix)
{
    _normalMatrix = normalMatrix;
}

QVector3D Object::getTranslation() const
{
    return _translation;
}

void Object::setTranslation(const QVector3D &translation)
{
    _translation = translation;
}

Material Object::getMaterial() const
{
    return _material;
}

void Object::setMaterial(const Material &material)
{
    _material = material;
}

std::vector<Vertex> Object::getBufferObject() const
{
    return _bufferObject;
}

GLuint Object::getVBO() const
{
    return _VBO;
}

GLuint Object::getVAO() const
{
    return _VAO;
}

float Object::getRotation() const
{
    return _rotation;
}

void Object::setRotation(float rotation)
{
    _rotation = rotation;
}


void Object::setRotationSpeed(float rotationSpeed)
{
    _rotationSpeed = rotationSpeed;
}

void Object::setGravitation(float gravitation)
{
    _gravitation = gravitation;
}

void Object::setOriginalPosition(const QVector3D &originalPosition)
{
    _originalPosition = originalPosition;
}

QString Object::getObjectID() const
{
    return _objectID;
}

void Object::setObjectID(const QString &objectID)
{
    _objectID = objectID;
}

QVector3D Object::getRotationVector() const
{
    return _rotationVector;
}

void Object::setRotationVector(const QVector3D &rotationVector)
{
    _rotationVector = rotationVector;
}

GLuint Object::getTexture() const
{
    return _texture;
}

void Object::setTexture(const GLuint &texture)
{
    _texture = texture;
}

QVector3D Object::getOriginalPosition() const
{
    return _originalPosition;
}

float Object::getGravitation() const
{
    return _gravitation;
}

float Object::getRotationSpeed() const
{
    return _rotationSpeed;
}

float Object::getScale() const
{
    return _scale;
}

void Object::setScale(float value)
{
    _scale = value;
}

float Object::getRestitution() const
{
    return _restitution;
}

void Object::setRestitution(float restitution)
{
    _restitution = restitution;
}

void Object::setUserDefinedZero(float userDefinedZero)
{
    _userDefinedZero = userDefinedZero;
}

Object::~Object(){
    _bufferObject.clear();
}
