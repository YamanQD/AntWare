#include <Physics.h>
using namespace aw;
Physics::Physics() {}
Physics &Physics::instance()
{
    static Physics physics;
    return physics;
}
void Physics::resolveCollision(GameObject *one, GameObject *two)
{
    // TODO
}
void Physics::apply(Scene *scene, float deltaTime)
{
    for (unsigned i = 0; i < scene->gameObjects.size(); ++i)
    {
        scene->gameObjects[i]->fixedUpdate(deltaTime);
    }
}