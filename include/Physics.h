#pragma once
#include <GameObject.h>
#include<Scene.h>
#define PHYSICS aw::Physics::instance()
namespace aw
{
    class Physics
    {
    private:
        Physics();

    public:
        static Physics &instance();
        void apply(Scene *scene, float deltaTime);
        void resolveCollision(GameObject *one, GameObject *two); // For testing purposes
    };
}