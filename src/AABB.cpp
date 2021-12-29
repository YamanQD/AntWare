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

    if ((up <= other.up && up >= other.down) ||
        (down <= other.up && down >= other.down))
    {
        intersectY = true;
    }
    if ((right <= other.right && right >= other.left) ||
        (left <= other.right && left >= other.left))
    {
        intersectX = true;
    }
    if ((forward <= other.forward && forward >= other.backward) ||
        (backward <= other.forward && backward >= other.backward))
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
void AABB::minmize(float factor)
{
    for (unsigned i = 0; i < 8; ++i)
    {
        if (i < 4)
        {
            bounds[i].x -= factor;
        }
        else
        {
            bounds[i].x += factor;
        }
        if (i < 2 || i == 4 || i == 5)
        {
            bounds[i].y -= factor;
        }
        else
        {
            bounds[i].y += factor;
        }
        if (i % 2 == 0)
        {
            bounds[i].z -= factor;
        }
        else
        {
            bounds[i].z += factor;
        }
    }
}
void AABB::maximize(float factor)
{
    minmize(-factor);
}