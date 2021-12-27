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
        GLuint transperncyTex;
        void loadTexture(const char *path, GLuint &tex);
        void drawQuad(GLuint texture, glm::vec2 pos, glm::vec2 size);

    public:
        static Hud &instance();
        void draw();
    };
}