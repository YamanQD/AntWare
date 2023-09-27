#pragma once
#include <glm/glm.hpp>
namespace aw
{
    /** \brief Bit-encoding for axes, used to specify which axes are locked.*/
    enum AXIS
    {
        x = 1,
        y = 2,
        z = 4
    };
    /** \brief Physical representation of GameObject, describes physical
     * properties of the object, physics is processed in GameObject::fixedUpdate.
     */
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

        /** \brief Locks linear movement.
         *
         * \param axis The axes (one or more OR-ed) to lock linear movement on,
         * this value is OR-ed with ::linearLock.
         */
        void lockLinear(AXIS axis);
        /** \brief Locks angular movement.
         *
         * \param axis The axes (one or more OR-ed) to lock angular movement on,
         * this value is OR-ed with ::angularLock.
         */
        void lockAngular(AXIS axis);
        /** \brief Unlocks linear movement.
         *
         * \param axis The axes (one or more OR-ed) to unlock linear movement on,
         * this value is XOR-ed with ::linearLock.
         */
        void unlockLinear(AXIS axis);
        /** \brief Unlocks angular movement.
         *
         * \param axis The axes (one or more OR-ed) to unlock angular movement on,
         * this value is XOR-ed with ::angularLock.
         */
        void unlockAngular(AXIS axis);
        /** \param axis The linear axes (one or more OR-ed) of which to check if they are ALL locked.
         *
         * \return true if ALL axes specified are locked.
         * \return false if one of the axes specified is unlocked.
         */
        bool isLinearLocked(AXIS axis);
        /** \param axis The angular axes (one or more OR-ed) of which to check if they are ALL locked.
         *
         * \return true if ALL axes specified are locked.
         * \return false if one of the axes specified is unlocked.
         */
        bool isAngularLocked(AXIS axis);
    };
}