#include <Ant.h>
using namespace aw;
using namespace std;
Ant::Ant(shared_ptr<Mesh> mesh, Material material, GameObject *parent) : GameObject(mesh, material, parent, false, 3)
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
void Ant::damage(unsigned amount)
{
    hp -= amount;
    if (hp < 0)
        hp = 0;
}
unsigned Ant::getHp()
{
    return hp;
}