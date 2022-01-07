#include <Player.h>
using namespace aw;
using namespace std;
using namespace sf;
using namespace glm;
Player::Player(shared_ptr<Mesh> mesh, Material material, vec2 mapMinLimit, vec2 mapMaxLimit,
               GameObject *parent) : GameObject(mesh, material, parent, false, 2),
                                     mapMinLimit(mapMinLimit),
                                     mapMaxLimit(mapMaxLimit)
{
    gunShotSoundBuffer.loadFromFile("Assets/Audio/gunshot.wav");
    reloadSoundBuffer.loadFromFile("Assets/Audio/reload.wav");
    hurtSoundBuffer.loadFromFile("Assets/Audio/playerHurt.wav");
    footstepsSoundBuffer.loadFromFile("Assets/Audio/playerFootsteps.ogg");

    gunShotSound.setBuffer(gunShotSoundBuffer);
    reloadSound.setBuffer(reloadSoundBuffer);
    hurtSound.setBuffer(hurtSoundBuffer);
    footstepsSound.setBuffer(footstepsSoundBuffer);
    footstepsSound.setLoop(true);

    aabb.maximize(0.2f);
}
void Player::start()
{
    bulletMesh = shared_ptr<Mesh>(new Mesh("./Assets/Models/Bullet.glb", "Assets/Textures/Bullet.png"));
    transparentTexture = Mesh::createTexture("./Assets/Textures/transparent.png");
    flashTexture = Mesh::createTexture("./Assets/Textures/flash.png");
    children[0]->getMesh()->setTexture(transparentTexture);
    isStatic = false;
    rigidbody.lockLinear(AXIS::y);
    rigidbody.lockAngular(AXIS::z);
}
void Player::update()
{
    rigidbody.velocity = {0, 0, 0};
    rigidbody.angularVelocity = {0, 0, 0};
    if (!hasFallen)
    {
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
    }
    if (rigidbody.velocity != glm::vec3(0, 0, 0))
    {
        footstepsSound.setPitch(Keyboard::isKeyPressed(Keyboard::LShift) ? 1.5f : 1.0f);
        if (footstepsSound.getStatus() != sf::Sound::Playing)
            footstepsSound.play();
    }
    else
    {
        footstepsSound.pause();
    }

    if (length(rigidbody.velocity) > 0)
        rigidbody.velocity = normalize(rigidbody.velocity);

    rigidbody.velocity *= Keyboard::isKeyPressed(Keyboard::LShift) ? runningSpeed : speed;

    auto mousePos = Mouse::getPosition(WINDOW.internal);
    mouseDelta = {mousePos.x - WINDOW.internal.getSize().x / 2.0f, mousePos.y - WINDOW.internal.getSize().y / 2.0f};
    mouseDelta *= -mouseSenstivity;
    Mouse::setPosition(Vector2i{static_cast<int>(WINDOW.internal.getSize().x / 2.0f), static_cast<int>(WINDOW.internal.getSize().y / 2.0f)}, WINDOW.internal);
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
    vec2 positionOnY = {transform.getPosition().x, transform.getPosition().z};
    if ((positionOnY.x < mapMinLimit.x || positionOnY.y < mapMinLimit.y ||
         positionOnY.x > mapMaxLimit.x || positionOnY.y > mapMaxLimit.y) &&
        !hasFallen)
    {
        hasFallen = true;
        rigidbody.lockLinear(AXIS::x);
        rigidbody.lockLinear(AXIS::z);
        rigidbody.unlockLinear(AXIS::y);
        rigidbody.acceleration = {0, -fallingAcceleration, 0};
    }
    if (fallingTime >= dieAfter)
    {
        damage(hp);
        killSound();
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
    if (isRecoiling)
    {
        recoilAnim(deltaTime);
    }
    if (isReloading)
    {
        reloadAnim(deltaTime);
    }
    if (hasFallen)
    {
        fallingTime += deltaTime;
    }
}
void Player::dispatchBullet()
{
    gunShotSound.play();
    bullets.push_back(Bullet(bulletMesh, Material(), nullptr, vec3(0, 0, -1))); // TODO custom mat
    bullets[bullets.size() - 1].transform = transform;
    bullets[bullets.size() - 1].transform.translate({0.249067f, 0.47149f, -1.25759f});
    isRecoiling = true;
    recoilTime = 0.0f;
    children[0]->getMesh()->setTexture(flashTexture);
}
void Player::reload()
{
    isReloading = true;
    reloadTime = 0.0f;
    if (totalAmmo > 0)
        reloadSound.play();

    if (totalAmmo > maxAmmo)
    {
        inHandAmmo = maxAmmo;
        totalAmmo -= maxAmmo;
    }
    else if (totalAmmo > 0)
    {
        inHandAmmo = totalAmmo;
        totalAmmo = 0;
    }
    HUD.setInHandAmmo(inHandAmmo);
    HUD.setTotalAmmo(totalAmmo);
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
    hurtSound.play();
    hp -= amount;
    return hp <= 0.0f;
}
void Player::recoilAnim(float deltaTime)
{
    if (recoilTimeOut <= recoilTime)
    {
        isRecoiling = false;
        childrenEular = {0, 0, 0};
        childrenTranslation = {0, 0, 0};
    }
    else
    {
        recoilTime += deltaTime;
        if (recoilTime < (recoilTimeOut / 2.0f))
        {
            childrenEular.x += recoilImpact * deltaTime;
            childrenTranslation.z += recoilImpact * deltaTime * 0.05f;
        }
        else
        {
            childrenEular.x -= recoilImpact * deltaTime;
            childrenTranslation.z -= recoilImpact * deltaTime * 0.05f;
            children[0]->getMesh()->setTexture(transparentTexture);
        }
    }
    for (unsigned i = 0; i < children.size(); ++i)
    {
        children[i]->transform.setRotation(childrenEular);
        children[i]->transform.setPosition(childrenTranslation);
    }
}
void Player::reloadAnim(float deltaTime)
{
    if (reloadTimeOut <= reloadTime)
    {
        isReloading = false;
        childrenEular = {0, 0, 0};
        childrenTranslation = {0, 0, 0};
    }
    else
    {
        reloadTime += deltaTime;
        if (reloadTime < (reloadTimeOut / 2.0f))
        {
            childrenEular.x -= reloadPlaybackSpeed * deltaTime;
            childrenTranslation.z += reloadPlaybackSpeed * deltaTime * 0.005f;
        }
        else
        {
            childrenEular.x += reloadPlaybackSpeed * deltaTime;
            childrenTranslation.z -= reloadPlaybackSpeed * deltaTime * 0.005f;
        }
    }
    for (unsigned i = 0; i < children.size(); ++i)
    {
        children[i]->transform.setRotation(childrenEular);
        children[i]->transform.setPosition(childrenTranslation);
    }
}
bool Player::isDead()
{
    return hp <= 0.0f;
}
void Player::killSound()
{
    footstepsSound.resetBuffer();
    reloadSound.resetBuffer();
    gunShotSound.resetBuffer();
}