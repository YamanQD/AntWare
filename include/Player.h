#pragma once
#include <Bullet.h>
#include <GameObject.h>
#include <HUD.h>
#include <SFML/Audio.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <Window.h>
#include <random>
namespace aw
{
  /** \brief The Main Character (the one the user is controlling) also known as
   * the Player.*/
  class Player : public GameObject
  {

    float speed = 10.0f, runningSpeed = 20.0f;
    float mouseSenstivity = 10.0f;
    /** \brief Used for rotation since they are easier to work with in this
     * use-case.*/
    glm::vec3 eularAngles = {0, 0, 0};
    /** \brief Used for animating by rotation, for the whole character
     * body.*/
    glm::vec3 childrenEular = {0, 0, 0};
    /** \brief Used for animating by translation, for the whole character
     * body.*/
    glm::vec3 childrenTranslation = {0, 0, 0};
    glm::vec2 mouseDelta;
    std::shared_ptr<Mesh> bulletMesh;
    sf::SoundBuffer gunShotSoundBuffer, footstepsSoundBuffer, reloadSoundBuffer,
        hurtSoundBuffer;
    sf::Sound gunShotSound, footstepsSound, reloadSound, hurtSound;
    int transparentTexture, flashTexture;
    bool isRecoiling = false;
    /** \brief Controls how the player rotates/translates when firing a shot.*/
    float recoilImpact = 40.0f;
    /** \brief The recoil animation length, in seconds.*/
    float recoilTimeOut = 1.0f / 5.0f;
    float recoilTime;

    bool isReloading = false;
    float reloadTime;
    /** \brief The reload animation length, in seconds.*/
    float reloadTimeOut = 1.5f; // mod me to change animation length
    float reloadPlaybackSpeed = 50.0f;
    /** \brief Progress the recoil animation \a deltaTime length.
     *
     * Ends the animation and sets ::isRecoiling to false if ::recoilTime
     * exceeds ::recoilTimeOut.
     *
     * \param deltaTime The amount of time (in seconds) to progress the animation.
     */
    void recoilAnim(float deltaTime);
    /** \brief Progress the reload animation \a deltaTime length.
     *
     * Ends the animation and sets ::isReloading to false if ::reloadTime
     * exceeds ::reloadTimeOut.
     *
     * \param deltaTime The amount of time (in seconds) to progress the animation.
     */
    void reloadAnim(float deltaTime);

    glm::vec2 mapMinLimit;
    glm::vec2 mapMaxLimit;
    bool hasFallen = false;
    float fallingAcceleration = 1000.0f;
    float fallingTime = 0.0f;
    float dieAfter = 5.0f;

  public:
    /** \brief Active Bullet instances fired at the Scene.*/
    std::vector<Bullet> bullets;
    float timeSinceDamage = 0.0f;
    float hp = 10.0f;
    unsigned totalAmmo = 36, inHandAmmo = 12, maxAmmo = 12;

    /** \param mesh The Player Mesh.
     * \param material The Player Material.
     * \param bulletMesh The Bullet Mesh.
     * \param mapMinLimit The map's rectangle XZ minimum point.
     * \param maxMinLimit The map's rectangle XZ maximum point.
     * \param parent The Player's parent.
     */
    Player(std::shared_ptr<Mesh> mesh, Material material,
           std::shared_ptr<Mesh> bulletMesh, glm::vec2 mapMinLimit,
           glm::vec2 mapMaxLimit, GameObject *parent = nullptr);
    /** \brief Sets up the player resources and physics state.
     *
     * Locks the Player linear movement on the Y (up) axis.
     * Locks the Player angular movement on the Z (forward) axis.
     */
    void start() override;
    /** \brief Handle user input and Player and ::bullets state management.
     *
     * Handles the player movement input and mouse motion, destroys timedout
     * Bullets, Kills the player if he ::fallingTime exceeds ::dieAfter.
     */
    void update() override;
    /** \brief In addition to GameObject::fixedUpdate, it handles camera movement
     * correctly runs Bullet::fixedUpdate on ::bullets, updates fallingTime if
     * ::hasFallen and runs animations if their bool values are true.
     *
     * \param deltaTime Passed to GameObject::fixedUpdate and Bullet::fixedUpdate.
     */
    void fixedUpdate(float deltaTime) override;
    /** \brief Draws the Player and ::bullets.*/
    void draw() override;
    /** \brief Fires a Bullet and adds it to ::bullets.*/
    void dispatchBullet();
    /** \brief Starts reloading */
    void reload();
    /** \brief Destorys a Bullet from ::bullets.
     *
     * \param index The index of the Bullet to destory.
     */
    void destroyBullet(int index);
    /** \brief Deals \a amount damage to the Player.
     *
     * \param amount The amount of damage to deal.
     * \return true if hp is equal or lower than zero.
     * \return false if hp is greater than zero.
     */
    bool damage(float amount);
    /** \return true if hp is equal or lower than zero.
     * \return false if hp is greater than zero.
     */
    bool isDead();
    /** \brief Stops Player from making any sound.*/
    void killSound();
  };
} // namespace aw