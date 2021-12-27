#include <HUD.h>
using namespace aw;
using namespace sf;
Hud::Hud()
{
    const char *path = "Assets/Textures/Y.png";
    loadTexture(path);
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
    drawQuad(Y, glm::vec2(0.0f, 0.0f), glm::vec2(4.0f, 4.0f));

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}
void Hud::loadTexture(const char *path)
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

    glGenTextures(1, &Y);
    glBindTexture(GL_TEXTURE_2D, Y);

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
    glBindTexture(GL_TEXTURE_2D, 0);
}