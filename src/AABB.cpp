#include <AABB.h>
using namespace aw;
using namespace glm;
bool AABB::isColliding(const AABB &other)
{
    bool intersectX = false, intersectY = false, intersectZ = false;
    if ((other.up <= up && other.up >= down) ||
        (other.down <= up && other.down >= down))
    {
        intersectY = true;
    }
    if ((other.right <= right && other.right >= left) ||
        (other.left <= right && other.left >= left))
    {
        intersectX = true;
    }
    if ((other.forward <= forward && other.forward >= backward) ||
        (other.backward <= forward && other.backward >= backward))
    {
        intersectZ = true;
    }
    return intersectZ && intersectY && intersectX;
}
bool AABB::isColliding(vec3 point)
{
    bool intersectX = false, intersectY = false, intersectZ = false;
    if (point.y <= up && point.y >= down)
    {
        intersectY = true;
    }
    if (point.x <= right && point.x >= left)
    {
        intersectX = true;
    }
    if (point.z <= forward && point.z >= backward)
    {
        intersectZ = true;
    }
    return intersectZ && intersectY && intersectX;
}
vec3 AABB::getCenter()
{
    vec3 corner = {left, down, backward};
    vec3 oppisite = {right, up, forward};
    return (corner + oppisite) * 0.5f;
}