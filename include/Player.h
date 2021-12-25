#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <GameObject.h>
#include <Window.h>
namespace aw
{
    class Player : public GameObject
    {
        float speed = 1.0f;
        float mouseSenstivity = 300.0f;

    public:
        Player(std::shared_ptr<Mesh> mesh, GameObject *parent = nullptr);
        void start() override;
        void update() override;
    };
}