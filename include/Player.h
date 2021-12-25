#pragma once
#include<SFML/Window/Keyboard.hpp>
#include <GameObject.h>
namespace aw
{
    class Player : public GameObject
    {
        float speed = 1.0f;

    public:
        Player(std::shared_ptr<Mesh> mesh, GameObject *parent = nullptr);
        void start() override;
        void update() override;
    };
}