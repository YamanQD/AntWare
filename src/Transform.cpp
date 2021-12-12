#include <Transform.h>
using namespace aw;
using namespace glm;
Transform::Transform(vec3 position, quat rotation, vec3 scale) : position(position),
                                                                 rotation(rotation),
                                                                 scale(scale)
{
}
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
    return scale;
}
void Transform::setPosition(vec3 position)
{
    this->position = position;
}
void Transform::setRotation(quat rotation)
{
    this->rotation = rotation;
}
void Transform::setScale(vec3 scale)
{
    this->scale = scale;
}