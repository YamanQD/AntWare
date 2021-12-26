#pragma once
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Audio.hpp>
#include <Window.h>
#include <GameObject.h>
#include <Bullet.h>
namespace aw
{
    class Player : public GameObject
    {
        float speed = 10.0f;
        float mouseSenstivity = 15.0f;
        glm::vec3 eularAngles = {0, 0, 0};
        glm::vec2 mouseDelta;
        std::shared_ptr<Mesh> bulletMesh;
        sf::SoundBuffer gunShotSoundBuffer, footstepsSoundBuffer;
        sf::Sound gunShotSound, footstepsSound;

    public:
        std::vector<Bullet> bullets;

        Player(std::shared_ptr<Mesh> mesh, GameObject *parent = nullptr);
        void start() override;
        void update() override;
        void fixedUpdate(float deltaTime) override;
        void draw() override;
        void dispatchBullet();
        void destroyBullet(int index);
    };
}