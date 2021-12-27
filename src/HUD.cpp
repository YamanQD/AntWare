#include <HUD.h>
using namespace aw;
using namespace sf;
Hud::Hud()
{
    char buffer[128];
    loadTexture("Assets/Textures/crosshair.png", crosshair);
    for (unsigned i = 0; i < 10; ++i)
    {
        sprintf(buffer, "./Assets/Textures/%d.png", i);
        loadTexture(buffer, digits[i]);
    }
}
Hud &Hud::instance()
{
    static Hud hud;
    return hud;
}
void Hud::draw()
{
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D((-16.0f / 2.0f),
               (16.0f / 2.0f),
               (-9.0f / 2.0f),
               (9.0f / 2.0f));
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Draw here
    drawQuad(crosshair, glm::vec2(0.1f, 0.0f), {1, 1});
    drawHP();
    drawAmmo();

    glBindTexture(GL_TEXTURE_2D, 0);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}
void Hud::loadTexture(const char *path, GLuint &tex)
{
    Image image;
    if (!image.loadFromFile(path))
    {
        throw "Couldn't load HUD texture file";
    }
    image.flipVertically();
    int imgHeight = image.getSize().y;
    int imgWidth = image.getSize().x;
    const Uint8 *imgData = image.getPixelsPtr();

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, imgWidth, imgHeight, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
}
void Hud::drawQuad(GLuint texture, glm::vec2 pos, glm::vec2 size)
{
    size /= 2.0f;
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 0.0f);
    glVertex2f(pos.x - size.x, pos.y - size.y);

    glTexCoord2f(1.0f, 0.0f);
    glVertex2f(pos.x + size.x, pos.y - size.y);

    glTexCoord2f(1.0f, 1.0f);
    glVertex2f(pos.x + size.x, pos.y + size.y);

    glTexCoord2f(0.0f, 1.0f);
    glVertex2f(pos.x - size.x, pos.y + size.y);

    glEnd();
}
void Hud::drawHP()
{
    if (hp >= 100)
    {
        drawQuad(digits[hp / 100], {6, -4}, {1, 1});
    }
    if (hp >= 10)
    {
        drawQuad(digits[(hp / 10) % 10], {6.6f, -4.0f}, {1, 1});
    }
    drawQuad(digits[hp % 10], {7.2f, -4.0f}, {1, 1});
}
void Hud::drawAmmo()
{
    if (ammo >= 100)
    {
        drawQuad(digits[ammo / 100], {-7.2f, -4.0f}, {1, 1});
    }
    if (ammo >= 10)
    {
        drawQuad(digits[(ammo / 10) % 10], {-6.6f, -4.0f}, {1, 1});
    }
    drawQuad(digits[ammo % 10], {-6, -4}, {1, 1});
}
void Hud::setHP(unsigned hp)
{
    this->hp = hp;
}
void Hud::setAmmo(unsigned ammo)
{
    this->ammo = ammo;
}