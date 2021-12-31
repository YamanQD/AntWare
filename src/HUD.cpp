#include <HUD.h>
using namespace aw;
using namespace sf;
Hud::Hud()
{
    char buffer[128];
    loadTexture("Assets/Textures/crosshair.png", crosshair);
    loadTexture("Assets/Textures/backSlash.png", backSlash);
    loadTexture("Assets/Textures/plus.png", plus);
    loadTexture("Assets/Textures/ammo.png", ammo);
    loadTexture("Assets/Textures/loading.png", loading);
    loadTexture("Assets/Textures/lose.png", lose);
    loadTexture("Assets/Textures/win.png", win);
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
    if (status == ONGOING)
    {
        drawQuad(crosshair, glm::vec2(0.1f, 0.0f), {1, 1});
        drawHP();
        drawAmmo();
    }
    else if (status == WIN)
    {
        drawQuad(win, glm::vec2(0.0f, 0.0f), {16.0f, 16.0f});
    }
    else if (status == LOSE)
    {
        drawQuad(lose, glm::vec2(0.0f, 0.0f), {16.0f, 16.0f});
    }
    else if (status == LOADING)
    {
        drawQuad(loading, glm::vec2(0.0f, 0.0f), {16.0f, 16.0f});
    }

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
void Hud::drawAmmo()
{
    float inHandAmmoY = -3.9f, totalAmmoY = -4.0f;
    float inHandAmmoSize = 0.8f, totalAmmoSize = 0.5f;
    float inHandDiff = 0.6 * inHandAmmoSize;
    float totalDiff = 0.6 * totalAmmoSize;
    float slashX = 6.0f;
    float inHand3X = slashX - inHandDiff, inHand2X = inHand3X - inHandDiff, inHand1X = inHand2X - inHandDiff;
    float total1X = slashX + totalDiff, total2X = total1X + totalDiff, total3X = total2X + totalDiff;
    float bulletDiff = totalDiff - 0.18f, bulletX = total3X + totalDiff + 0.1f, bulletY = totalAmmoY - 0.1f, bulletSize = 0.4f;

    if (totalAmmo < 0)
        totalAmmo = 0;
    if (inHandAmmo < 0)
        inHandAmmo = 0;

    if (totalAmmo >= 100)
    {
        drawQuad(ammo, {bulletX, bulletY}, {bulletSize, bulletSize});

        drawQuad(digits[totalAmmo / 100], {total1X, totalAmmoY}, {totalAmmoSize, totalAmmoSize});
        drawQuad(digits[(totalAmmo / 10) % 10], {total2X, totalAmmoY}, {totalAmmoSize, totalAmmoSize});
        drawQuad(digits[totalAmmo % 10], {total3X, totalAmmoY}, {totalAmmoSize, totalAmmoSize});

        drawQuad(backSlash, {slashX, totalAmmoY}, {totalAmmoSize, totalAmmoSize});

        if (inHandAmmo >= 100)
        {
            drawQuad(digits[inHandAmmo / 100], {inHand1X, inHandAmmoY}, {inHandAmmoSize, inHandAmmoSize});
        }
        if (inHandAmmo >= 10)
        {
            drawQuad(digits[(inHandAmmo / 10) % 10], {inHand2X, inHandAmmoY}, {inHandAmmoSize, inHandAmmoSize});
        }
        drawQuad(digits[inHandAmmo % 10], {inHand3X, inHandAmmoY}, {inHandAmmoSize, inHandAmmoSize});
    }
    else if (totalAmmo >= 10)
    {
        slashX += totalDiff;
        inHand3X = slashX - inHandDiff, inHand2X = inHand3X - inHandDiff, inHand1X = inHand2X - inHandDiff;
        total1X = slashX + totalDiff, total2X = total1X + totalDiff, total3X = total2X + totalDiff;
        bulletDiff = totalDiff - 0.18f, bulletX = total2X + totalDiff + 0.1f, bulletY = totalAmmoY - 0.1f, bulletSize = 0.4f;

        drawQuad(ammo, {bulletX, bulletY}, {bulletSize, bulletSize});

        drawQuad(digits[(totalAmmo / 10) % 10], {total1X, totalAmmoY}, {totalAmmoSize, totalAmmoSize});
        drawQuad(digits[totalAmmo % 10], {total2X, totalAmmoY}, {totalAmmoSize, totalAmmoSize});

        drawQuad(backSlash, {slashX, totalAmmoY}, {totalAmmoSize, totalAmmoSize});

        if (inHandAmmo >= 100)
        {
            drawQuad(digits[inHandAmmo / 100], {inHand1X, inHandAmmoY}, {inHandAmmoSize, inHandAmmoSize});
        }
        if (inHandAmmo >= 10)
        {
            drawQuad(digits[(inHandAmmo / 10) % 10], {inHand2X, inHandAmmoY}, {inHandAmmoSize, inHandAmmoSize});
        }
        drawQuad(digits[inHandAmmo % 10], {inHand3X, inHandAmmoY}, {inHandAmmoSize, inHandAmmoSize});
    }
    else
    {
        slashX += totalDiff * 2;
        inHand3X = slashX - inHandDiff, inHand2X = inHand3X - inHandDiff, inHand1X = inHand2X - inHandDiff;
        total1X = slashX + totalDiff, total2X = total1X + totalDiff, total3X = total2X + totalDiff;
        bulletDiff = totalDiff - 0.18f, bulletX = total1X + totalDiff + 0.1f, bulletY = totalAmmoY - 0.1f, bulletSize = 0.4f;

        drawQuad(ammo, {bulletX, bulletY}, {bulletSize, bulletSize});

        drawQuad(digits[totalAmmo % 10], {total1X, totalAmmoY}, {totalAmmoSize, totalAmmoSize});

        drawQuad(backSlash, {slashX, totalAmmoY}, {totalAmmoSize, totalAmmoSize});

        if (inHandAmmo >= 100)
        {
            drawQuad(digits[inHandAmmo / 100], {inHand1X, inHandAmmoY}, {inHandAmmoSize, inHandAmmoSize});
        }
        if (inHandAmmo >= 10)
        {
            drawQuad(digits[(inHandAmmo / 10) % 10], {inHand2X, inHandAmmoY}, {inHandAmmoSize, inHandAmmoSize});
        }
        drawQuad(digits[inHandAmmo % 10], {inHand3X, inHandAmmoY}, {inHandAmmoSize, inHandAmmoSize});
    }
}
void Hud::drawHP()
{
    float hpY = -3.9f, hpSize = 0.9f;
    float hpDiff = 0.6f * hpSize;
    float plusX = -7.0f, plusY = -3.75f, plusSize = 1.8f;
    float hp1X = plusX + hpDiff + 0.1f, hp2X = hp1X + hpDiff, hp3X = hp2X + hpDiff;

    if (hp < 0)
        hp = 0;

    drawQuad(plus, {plusX, plusY}, {plusSize, plusSize});
    if (hp >= 100)
    {
        drawQuad(digits[hp / 100], {hp1X, hpY}, {hpSize, hpSize});
    }
    if (hp >= 10)
    {
        drawQuad(digits[(hp / 10) % 10], {hp2X, hpY}, {hpSize, hpSize});
    }
    drawQuad(digits[hp % 10], {hp3X, hpY}, {hpSize, hpSize});
}
void Hud::setHP(unsigned hp)
{
    this->hp = hp;
}
void Hud::setInHandAmmo(unsigned ammo)
{
    this->inHandAmmo = ammo;
}
void Hud::setTotalAmmo(unsigned ammo)
{
    this->totalAmmo = ammo;
}
void Hud::setStatus(Status status)
{
    this->status = status;
}