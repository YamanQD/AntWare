#include <RagedAnt.h>
using namespace aw;
using namespace std;
using namespace glm;
RagedAnt::RagedAnt(shared_ptr<Mesh> mesh,
                   Material material,
                   GameObject *parent,
                   GameObject *target) : Ant(mesh,
                                             material,
                                             parent),
                                         target(target) {}

void RagedAnt::update()
{
    Ant::update();
    if (isAlive)
    {
        vec3 targetPos = target->transform.getPosition();
        targetPos.y = transform.getPosition().y;
        mat3 lookAt = glm::lookAt(transform.getPosition(), targetPos, {0, 1, 0});
        transform.setRotation(quat(lookAt));
        transform.setRotation(transform.getRotationAxis(), -transform.getRotationAngle());
        if (aabb.isColliding(target->aabb))
            rigidbody.velocity = {0, 0, 0};
        else
            rigidbody.velocity = {0, 0, -speed};
    }
}
void RagedAnt::die()
{
    Ant::die();
    rigidbody.velocity = {0, 0, 0};
}