#pragma once
#include <GameObject.h>
#define PHYSICS aw::Physics::instance()
namespace aw
{
    class Physics
    {
    private:
        Physics();

    public:
        static Physics &instance();
        void resolveCollision(GameObject *one, GameObject *two); // For testing purposes
    };
}