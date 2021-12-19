#pragma once
#include <glm/glm.hpp>
namespace aw
{
    class AABB
    {
    private:
        float up, down, right, left, forward, backward;

    public:
        bool isColliding(const AABB &other);
        bool isColliding(glm::vec3 point);
        friend class GameObject;
    };
}