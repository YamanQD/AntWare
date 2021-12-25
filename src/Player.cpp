#include <Player.h>
using namespace aw;
using namespace std;
using namespace sf;
using namespace glm;
Player::Player(shared_ptr<Mesh> mesh, GameObject *parent) : GameObject(mesh, parent, false)
{
}
void Player::start()
{
    isStatic = false;
    rigidbody.lockLinear(AXIS::y);
    speed = 2.0f;
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
    vec2 mouseDelta = {mousePos.x, mousePos.y};
    if (length(mouseDelta) > 0)
        mouseDelta = normalize(mouseDelta);
    mouseDelta *= mouseSenstivity; // TODO hide cursoe
    rigidbody.angularVelocity = {mouseDelta.y, mouseDelta.x, 0};
    Mouse::setPosition(Vector2i{0, 0}, WINDOW.internal);
}