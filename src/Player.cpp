#include <Player.h>
using namespace aw;
using namespace std;
using namespace sf;
using namespace glm;
Player::Player(shared_ptr<Mesh> mesh, Material material, GameObject *parent) : GameObject(mesh, material, parent, false, 2)
{
    if (!gunShotSoundBuffer.loadFromFile("Assets/Audio/gunshot.wav"))
        throw "Error loading gunshot.wav";
    if (!footstepsSoundBuffer.loadFromFile("Assets/Audio/playerFootsteps.ogg"))
        throw "Error loading playerFootsteps.wav";

    gunShotSound.setBuffer(gunShotSoundBuffer);
    footstepsSound.setBuffer(footstepsSoundBuffer);
    footstepsSound.setLoop(true);
}
static inline bool isMoving()
{
    return (Keyboard::isKeyPressed(Keyboard::A) ||
            Keyboard::isKeyPressed(Keyboard::S) ||
            Keyboard::isKeyPressed(Keyboard::D) ||
            Keyboard::isKeyPressed(Keyboard::W));
}
void Player::start()
{
    bulletMesh = make_shared<Mesh>(Mesh("./Assets/Models/Bullet.glb", {1, 1, 1}));
    isStatic = false;
    rigidbody.lockLinear(AXIS::y);
    rigidbody.lockAngular(AXIS::z);
}
void Player::update()
{
    rigidbody.velocity = {0, 0, 0};
    rigidbody.angularVelocity = {0, 0, 0};
    if (Keyboard::isKeyPressed(Keyboard::W))
    {
        rigidbody.velocity.z -= 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::S))
    {
        rigidbody.velocity.z += 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::D))
    {
        rigidbody.velocity.x += 1;
    }
    if (Keyboard::isKeyPressed(Keyboard::A))
    {
        rigidbody.velocity.x -= 1;
    }

    if (isMoving())
    {
        if (footstepsSound.getStatus() != sf::Sound::Playing)
            footstepsSound.play();
    }
    else
    {
        footstepsSound.pause();
    }

    if (length(rigidbody.velocity) > 0)
        rigidbody.velocity = normalize(rigidbody.velocity);
    rigidbody.velocity *= speed;

    auto mousePos = Mouse::getPosition(WINDOW.internal);
    mouseDelta = {mousePos.x - WINDOW.internal.getSize().x / 2.0f, mousePos.y - WINDOW.internal.getSize().y / 2.0f};
    mouseDelta *= -mouseSenstivity;
    Mouse::setPosition(Vector2i{WINDOW.internal.getSize().x / 2.0f, WINDOW.internal.getSize().y / 2.0f}, WINDOW.internal);
    auto bulletsSize = bullets.size();
    for (unsigned i = 0; i < bulletsSize; ++i)
    {
        if (bullets[i].timeOut())
        {
            destroyBullet(i);
            --i;
            --bulletsSize;
        }
    }
}
void Player::fixedUpdate(float deltaTime)
{
    GameObject::fixedUpdate(deltaTime);
    eularAngles.x += mouseDelta.y * deltaTime;
    eularAngles.y += mouseDelta.x * deltaTime;
    eularAngles.x = glm::clamp<float>(eularAngles.x, -60.0f, 80.0f);
    transform.setRotation(eularAngles);
    for (unsigned i = 0; i < bullets.size(); ++i)
    {
        bullets[i].fixedUpdate(deltaTime);
    }
}
void Player::dispatchBullet()
{
    gunShotSound.play();
    bullets.push_back(Bullet(bulletMesh, Material(), nullptr, vec3(0, 0, -1))); // TODO custom mat
    bullets[bullets.size() - 1].transform = transform;
    bullets[bullets.size() - 1].transform.translate({0.23931f, 0.449318f, -1.22097f});
    float yRecoil = -(((float)(rand() % 100)) / 100.0f);
    float xRecoil = ((float)(rand() % 300)) / 100.0f;
    eularAngles.x += xRecoil;
    eularAngles.y += yRecoil;
    transform.setRotation(eularAngles);
}
void Player::draw()
{
    GameObject::draw();
    for (unsigned i = 0; i < bullets.size(); ++i)
    {
        bullets[i].draw();
    }
}
void Player::destroyBullet(int index)
{
    bullets.erase(bullets.begin() + index);
}
bool Player::damage(float amount)
{
    hp -= amount;
    return hp <= 0.0f;
}