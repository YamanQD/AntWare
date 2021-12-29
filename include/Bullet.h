#pragma once
#include <SFML/System/Clock.hpp>
#include <GameObject.h>
namespace aw
{
    class Bullet : public GameObject
    {
    private:
        sf::Clock timer;
        float lifeSpan = 1.0f;
        float speed = 80.0f;

    public:
        Bullet(std::shared_ptr<Mesh> mesh, Material material, GameObject *parent, glm::vec3 projectVec);
        void start() override;
        void update() override;
        bool timeOut();
    };
}