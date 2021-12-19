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
    private:
        int linearLock = 0;
        int angularLock = 0;

    public:
        glm::vec3 velocity;
        glm::vec3 angularVelocity;
        glm::vec3 acceleration;
        glm::vec3 angularAcceleration;
        float mass = 1.0f;
        void lockLinear(AXIS axis);
        void lockAngular(AXIS axis);
        void unlockLinear(AXIS axis);
        void unlockAngular(AXIS axis);
        bool isLinearLocked(AXIS axis);
        bool isAngularLocked(AXIS axis);
        int getLinearLock();
        int getAngularLock();
    };
}