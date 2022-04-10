#pragma once
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <GameObject.h>
namespace aw
{
    class Bullet : public GameObject
    {
    private:
        sf::Clock timer;
        float lifeSpan = 5.0f;
        float speed = 40.0f;

    public:
        Bullet(std::shared_ptr<Mesh> mesh, Material material, GameObject *parent, glm::vec3 projectVec);
        void start() override;
        void update() override;
        bool timeOut();
    };
}