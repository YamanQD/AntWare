#pragma once
#include <random>
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
        glm::vec3 childrenEular = {0, 0, 0}, childrenTranslation = {0, 0, 0};
        glm::vec2 mouseDelta;
        std::shared_ptr<Mesh> bulletMesh;
        sf::SoundBuffer gunShotSoundBuffer, footstepsSoundBuffer;
        sf::Sound gunShotSound, footstepsSound;
        int transparentTexture, flashTexture;
        bool isRecoiling = false;
        float recoilImpact = 25.0f;
        float recoilTimeOut = 1.0f / 5.0f;
        float recoilTime;

    public:
        std::vector<Bullet> bullets;
        float timeSinceDamage = 0.0f;
        float hp = 10.0f;
        unsigned ammo = 5;

        Player(std::shared_ptr<Mesh> mesh, Material material, GameObject *parent = nullptr);
        void start() override;
        void update() override;
        void fixedUpdate(float deltaTime) override;
        void draw() override;
        void dispatchBullet();
        void destroyBullet(int index);
        bool damage(float amount);
    };
}