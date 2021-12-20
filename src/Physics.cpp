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