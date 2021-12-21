#pragma once
#include <glm/glm.hpp>
namespace aw
{
    enum AXIS
    {
        x = 1,
        y = 2,
        z = 4
    };
    class Rigidbody
    {
    public:
        glm::vec3 velocity = {0, 0, 0};
        glm::vec3 angularVelocity = {0, 0, 0};
        glm::vec3 acceleration = {0, 0, 0};
        glm::vec3 angularAcceleration = {0, 0, 0};
        float mass = 1.0f;
        int linearLock = 0;
        int angularLock = 0;

        void lockLinear(AXIS axis);
        void lockAngular(AXIS axis);
        void unlockLinear(AXIS axis);
        void unlockAngular(AXIS axis);
        bool isLinearLocked(AXIS axis);
        bool isAngularLocked(AXIS axis);
        };
}