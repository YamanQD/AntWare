#include <Ant.h>
using namespace aw;
using namespace std;
Ant::Ant(shared_ptr<Mesh> mesh, GameObject *parent) : GameObject(mesh, parent, false, 3)
{
    for (unsigned i = 0; i < 8; ++i)
    {
        if (i < 4)
        {
            aabb.bounds[i].x -= 1.0f;
        }
        else
        {
            aabb.bounds[i].x += 1.0f;
        }
    }
}
void Ant::start() {}
void Ant::update() {}