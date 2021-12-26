#include <Bullet.h>
using namespace aw;
using namespace std;
using namespace glm;
Bullet::Bullet(shared_ptr<Mesh> mesh,Material material, GameObject *parent, vec3 projectVec) : GameObject(mesh,material, parent, false)
{
    rigidbody.velocity = normalize(projectVec) * speed;
}
void Bullet::start()
{
    timer.restart();
}
void Bullet::update()
{
}
bool Bullet::timeOut()
{
    if (timer.getElapsedTime().asSeconds() >= lifeSpan)
    {
        return true;
    }
    return false;
}