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
        GLuint Y;
        void loadTexture(const char *path);
        void drawQuad(GLuint texture, glm::vec2 pos, glm::vec2 size);

    public:
        static Hud &instance();
        void draw();
    };
}