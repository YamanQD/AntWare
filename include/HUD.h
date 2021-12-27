#pragma once
#include <SFML/Graphics/Image.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#define HUD aw::Hud::instance()
namespace aw
{
    class Hud
    {
    private:
        Hud();
        GLuint crosshair;
        GLuint digits[10];
        void loadTexture(const char *path, GLuint &tex);
        void drawQuad(GLuint texture, glm::vec2 pos, glm::vec2 size);
        void drawHP();
        void drawAmmo();
        unsigned hp = 100;
        unsigned ammo = 10;

    public:
        static Hud &instance();
        void draw();
        void setHP(unsigned hp);
        void setAmmo(unsigned ammo);
    };
}