#pragma once
#include <GameObject.h>
#include <SFML/System/Clock.hpp>
namespace aw
{
    class Ant : public GameObject
    {
        unsigned hp = 4;
        sf::Clock timeSinceDamage;
        Material originalMaterial;
        bool isHurting = false;

    public:
        Ant(std::shared_ptr<Mesh> mesh, Material material, GameObject *parent);
        void start() override;
        void update() override;
        void damage(unsigned amount);
        unsigned getHp();
    };
}