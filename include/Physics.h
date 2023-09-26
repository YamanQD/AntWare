#pragma once
#include <GameObject.h>
#include <Scene.h>
#define PHYSICS aw::Physics::instance()
namespace aw
{
    /** \brief Game physics manager.*/
    class Physics
    {
    private:
        Physics();

    public:
        static Physics &instance();
        /** \brief Calls \a scene::gameObjects::fixedUpdate(\a deltaTime) and
         * \a scene::camera::fixedUpdate(\a deltaTime).
         *
         * \param scene A pointer to the scene which getting its Camera and GameObject
         * instances physics applied.
         * \param deltaTime The time (in seconds) between the last time physics were applied and the present
         * (commonly known as the timestep).
         */
        void apply(Scene *scene, float deltaTime);
        /** \brief Intended for collisions resolution, not implemented yet.*/
        void resolveCollision(GameObject *one, GameObject *two); // For testing purposes
    };
}