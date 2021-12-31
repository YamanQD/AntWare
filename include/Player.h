#pragma once
#include <random>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Audio.hpp>
#include <Window.h>
#include <GameObject.h>
#include <Bullet.h>
#include <HUD.h>
namespace aw
{
    class Player : public GameObject
    {

        float speed = 10.0f, runningSpeed = 20.0f;
        float mouseSenstivity = 15.0f;
        glm::vec3 eularAngles = {0, 0, 0};
        glm::vec3 childrenEular = {0, 0, 0}, childrenTranslation = {0, 0, 0};
        glm::vec2 mouseDelta;
        std::shared_ptr<Mesh> bulletMesh;
        sf::SoundBuffer gunShotSoundBuffer, footstepsSoundBuffer, reloadSoundBuffer, hurtSoundBuffer;
        sf::Sound gunShotSound, footstepsSound, reloadSound, hurtSound;
        int transparentTexture, flashTexture;
        bool isRecoiling = false;
        float recoilImpact = 40.0f;
        float recoilTimeOut = 1.0f / 5.0f;
        float recoilTime;

        bool isReloading = false;
        float reloadTime;
        float reloadTimeOut = 1.5f; // mod me to change animation length
        float reloadPlaybackSpeed = 50.0f;
        void recoilAnim(float deltaTime);
        void reloadAnim(float deltaTime);

    public:
        std::vector<Bullet> bullets;
        float timeSinceDamage = 0.0f;
        float hp = 10.0f;
        unsigned totalAmmo = 30, inHandAmmo = 12, maxAmmo = 10;

        Player(std::shared_ptr<Mesh> mesh, Material material, GameObject *parent = nullptr);
        void start() override;
        void update() override;
        void fixedUpdate(float deltaTime) override;
        void draw() override;
        void dispatchBullet();
        void reload();
        void destroyBullet(int index);
        bool damage(float amount);
        void killSound();
    };
}