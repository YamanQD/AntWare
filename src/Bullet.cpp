#include <Bullet.h>
using namespace aw;
using namespace std;
using namespace glm;
Bullet::Bullet(shared_ptr<Mesh> mesh, GameObject *parent, vec3 projectVec) : GameObject(mesh, parent, false)
{
    rigidbody.velocity = normalize(projectVec) * speed;
}
void Bullet::start()
{
}
void Bullet::update()
{
}