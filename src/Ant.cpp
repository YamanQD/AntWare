#include <Ant.h>
using namespace aw;
using namespace std;
Ant::Ant(shared_ptr<Mesh> mesh, Material material, GameObject *parent) : GameObject(mesh, material, parent, false, 3)
{
    hurtSoundBuffer.loadFromFile("Assets/Audio/antHurt.ogg");
    hurtSound.setBuffer(hurtSoundBuffer);
    originalMaterial = material;
    for (unsigned i = 0; i < 8; ++i)
    {
        if (i < 4)
        {
            aabb.bounds[i].x -= 2.5f;
        }
        else
        {
            aabb.bounds[i].x += 2.5f;
        }
        if (i < 2 || i == 4 || i == 5)
        {
            aabb.bounds[i].y -= 0.1f;
        }
        else
        {
            aabb.bounds[i].y += 0.6f;
        }
        if (i % 2 == 0)
        {
            aabb.bounds[i].z -= 0.5f;
        }
        else
        {
            aabb.bounds[i].z += 1.3f;
        }
    }
}
void Ant::start() {}
void Ant::update()
{
    if (isAlive && isHurting && timeSinceDamage.getElapsedTime().asSeconds() >= 0.3f)
    {
        isHurting = false;
        material = originalMaterial;
    }
    if (!isAlive && timeSinceLastAlphaDecrease.getElapsedTime().asSeconds() >= 0.1f)
    {
        if (material.getAlpha() > 0.0f)
        {
            material.setAlpha(material.getAlpha() - 0.05f);
        }
        timeSinceLastAlphaDecrease.restart();
    }
}
void Ant::damage(unsigned amount)
{
    if (!isAlive)
        return;

    isHurting = true;
    hurtSound.play();
    timeSinceDamage.restart();
    material.setDiffuse({1, 0, 0, 1});

    if (hp <= amount)
    {
        hp = 0;
        die();
    }
    else
    {
        hp -= amount;
    }
}
unsigned Ant::getHp()
{
    return hp;
}
void Ant::die()
{
    isAlive = false;
    isHurting = false;
    material = originalMaterial;
    transform.rotate({1, 0, 0}, 180.0f);
}
bool Ant::timeToDestroy()
{
    return !isAlive && material.getAlpha() <= 0.0f;
}