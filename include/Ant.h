#pragma once
#include <GameObject.h>
#include <SFML/System/Clock.hpp>
namespace aw
{
    class Ant : public GameObject
    {
        unsigned hp = 2;
        sf::Clock timeSinceDamage, timeSinceLastAlphaDecrease;
        Material originalMaterial;
        bool isHurting = false;
        bool isAlive = true;
        void die();

    public:
        Ant(std::shared_ptr<Mesh> mesh, Material material, GameObject *parent);
        void start() override;
        void update() override;
        void damage(unsigned amount);
        unsigned getHp();
        bool timeToDestroy();
    };
}