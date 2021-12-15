#include <Transform.h>
using namespace aw;
using namespace glm;
Transform::Transform(vec3 position, quat rotation, vec3 scale) : position(position),
                                                                 rotation(rotation),
                                                                 scaling(scale) {}
Transform::Transform(vec3 position, vec3 rotation, vec3 scale) : position(position),
                                                                 rotation(radians(rotation)),
                                                                 scaling(scale) {}
vec3 Transform::getPosition()
{
    return position;
}
quat Transform::getRotation()
{
    return rotation;
}
vec3 Transform::getScale()
{
    return scaling;
}
vec3 Transform::getRotationAxis()
{
    if (rotation.w == 0.0f)
        return vec3(1, 0, 0);
    float sqrtOneMinWSquered = sqrt(1 - pow(rotation.w, 2));
    return vec3(
        rotation.x / sqrtOneMinWSquered,
        rotation.y / sqrtOneMinWSquered,
        rotation.z / sqrtOneMinWSquered);
}
float Transform::getRotationAngle()
{
    return degrees(2 * acos(rotation.w));
}
void Transform::setPosition(vec3 position)
{
    this->position = position;
}
void Transform::setRotation(quat rotation)
{
    this->rotation = rotation;
}
void Transform::setRotation(vec3 rotation)
{
    rotation = radians(rotation);
    this->rotation = quat(rotation);
}
void Transform::setRotation(vec3 axis, float angle)
{
    angle = radians(angle);
    this->rotation = glm::rotate(quat{1, 0, 0, 0}, angle, axis);
}
void Transform::setScale(vec3 scale)
{
    this->scaling = scale;
}
void Transform::translate(vec3 translation)
{
    position += translation;
}
void Transform::rotate(quat rotation)
{
    this->rotation *= rotation;
}
void Transform::rotate(vec3 rotation)
{
    rotation = radians(rotation);
    this->rotation *= quat(rotation);
}
void Transform::rotate(vec3 axis, float angle)
{
    angle = radians(angle);
    this->rotation *= glm::rotate(quat{1, 0, 0, 0}, angle, axis);
}
void Transform::rotateGlobal(quat rotation)
{
    this->rotation = rotation * this->rotation;
}
void Transform::rotateGlobal(vec3 rotation)
{
    rotation = radians(rotation);
    this->rotation = quat(rotation) * this->rotation;
}
void Transform::rotateGlobal(vec3 axis, float angle)
{
    angle = radians(angle);
    quat rotation = glm::rotate(quat{1, 0, 0, 0}, angle, axis);
    this->rotation = rotation * this->rotation;
}
void Transform::scale(vec3 scale)
{
    scaling += scale;
}