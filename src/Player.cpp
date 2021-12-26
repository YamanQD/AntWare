#include <Player.h>
using namespace aw;
using namespace std;
using namespace sf;
using namespace glm;
Player::Player(shared_ptr<Mesh> mesh, GameObject *parent) : GameObject(mesh, parent, false, 2)
{
}
void Player::start()
{
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
    if (length(rigidbody.velocity) > 0)
        rigidbody.velocity = normalize(rigidbody.velocity);
    rigidbody.velocity *= speed;

    auto mousePos = Mouse::getPosition(WINDOW.internal);
    mouseDelta = {mousePos.x - WINDOW.internal.getSize().x / 2.0f, mousePos.y - WINDOW.internal.getSize().y / 2.0f};
    mouseDelta *= -mouseSenstivity;
    Mouse::setPosition(Vector2i{WINDOW.internal.getSize().x / 2.0f, WINDOW.internal.getSize().y / 2.0f}, WINDOW.internal);
}
void Player::fixedUpdate(float deltaTime)
{
    GameObject::fixedUpdate(deltaTime);
    eularAngles.x += mouseDelta.y * deltaTime;
    eularAngles.y += mouseDelta.x * deltaTime;
    eularAngles.x = glm::clamp<float>(eularAngles.x, -60.0f, 80.0f);
    transform.setRotation(eularAngles);
}