#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <GameObject.h>
#include <Window.h>
namespace aw
{
    class Player : public GameObject
    {
        float speed = 10.0f;
        float mouseSenstivity = 15.0f;
        glm::vec3 eularAngles = {0, 0, 0};
        glm::vec2 mouseDelta;

    public:
        Player(std::shared_ptr<Mesh> mesh, GameObject *parent = nullptr);
        void start() override;
        void update() override;
        void fixedUpdate(float deltaTime) override;
    };
}