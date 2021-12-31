#include <RagedAnt.h>
using namespace aw;
using namespace std;
using namespace glm;
RagedAnt::RagedAnt(std::vector<std::shared_ptr<Mesh>> walkcycleAnim,
                   shared_ptr<Mesh> mesh,
                   Material material,
                   GameObject *parent,
                   GameObject *target) : Ant(mesh,
                                             material,
                                             parent),
                                         target(target),
                                         walkcycleAnim(walkcycleAnim) {}
void RagedAnt::start()
{
    Ant::start();
    GLuint texture;
    meshPtr->getTexture(texture);
    for (unsigned i = 0; i < walkcycleAnim.size(); ++i)
    {
        walkcycleAnim[i]->setTexture(texture);
    }
    baseMesh = meshPtr;
}
void RagedAnt::update()
{
    Ant::update();
    if (isAlive &&
        distance(transform.getPosition(), target->transform.getPosition()) <= detectionRaduis)
    {
        vec3 targetPos = target->transform.getPosition();
        targetPos.y = transform.getPosition().y;
        mat3 lookAt = glm::lookAt(transform.getPosition(), targetPos, {0, 1, 0});
        quat rotation = quat(lookAt);
        if (!(rotation != rotation))
        {
            transform.setRotation(quat(lookAt));
            transform.setRotation(transform.getRotationAxis(), -transform.getRotationAngle());
        }
        if (aabb.isColliding(target->aabb))
            rigidbody.velocity = {0, 0, 0};
        else
            rigidbody.velocity = {0, 0, -speed};
    }
    else
    {
        rigidbody.velocity = {0, 0, 0};
    }
}
void RagedAnt::die()
{
    Ant::die();
    rigidbody.velocity = {0, 0, 0};
}
void RagedAnt::fixedUpdate(float deltaTime)
{
    Ant::fixedUpdate(deltaTime);
    if (length(rigidbody.velocity) > 0.0f)
    {
        animate(deltaTime);
    }
    else
    {
        meshPtr = baseMesh;
    }
}
void RagedAnt::animate(float deltaTime)
{
    animTime += deltaTime;
    if (animTime > walkcycleLength)
    {
        animTime = 0.0f;
    }
    float progress = animTime / walkcycleLength;
    progress *= walkcycleAnim.size();
    int index = round(progress);
    if (index >= walkcycleAnim.size())
    {
        index = 0;
    }
    meshPtr = walkcycleAnim[index];
}