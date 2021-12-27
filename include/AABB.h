#pragma once
#include <glm/glm.hpp>
namespace aw
{
    class AABB
    {
    private:
        float up, down, right, left, forward, backward;

    public:
        glm::vec3 bounds[8];
        bool isColliding(const AABB &other);
        bool isColliding(glm::vec3 point);
        glm::vec3 getCenter();
        void minmize(float factor);
        friend class GameObject;
    };
}