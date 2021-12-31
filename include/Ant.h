#pragma once
#include <GameObject.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>
namespace aw
{
    class Ant : public GameObject
    {
    protected:
        unsigned hp = 5;
        sf::Clock timeSinceDamage, timeSinceLastAlphaDecrease;
        Material originalMaterial;
        bool isHurting = false;
        bool isAlive = true;
        sf::SoundBuffer hurtSoundBuffer;
        sf::Sound hurtSound;
        virtual void die();

    public:
        Ant(std::shared_ptr<Mesh> mesh, Material material, GameObject *parent);
        void start() override;
        void update() override;
        void damage(unsigned amount);
        unsigned getHp();
        bool timeToDestroy();
    };
}