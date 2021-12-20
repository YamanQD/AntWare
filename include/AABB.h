#pragma once
#include <glm/glm.hpp>
namespace aw
{
    class AABB
    {
    private:
        float up, down, right, left, forward, backward;
        glm::vec3 bounds[8];

    public:
        bool isColliding(const AABB &other);
        bool isColliding(glm::vec3 point);
        glm::vec3 getCenter();
        friend class GameObject;
    };
}