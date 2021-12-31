#pragma once
#include <SFML/Graphics/Image.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#define HUD aw::Hud::instance()
namespace aw
{
    enum Status
    {
        WIN,
        LOSE,
        ONGOING,
        LOADING
    };
    class Hud
    {
    private:
        Hud();
        GLuint crosshair;
        GLuint digits[10];
        GLuint backSlash, plus, ammo;
        GLuint hurt;
        GLuint lose, win, loading;
        void loadTexture(const char *path, GLuint &tex);
        void drawQuad(GLuint texture, glm::vec2 pos, glm::vec2 size);
        void drawHP();
        void drawAmmo();
        void drawHurtEffect();
        int hp;
        int inHandAmmo, totalAmmo;
        bool isHurting = false;
        Status status;

    public:
        static Hud &instance();
        void draw();
        void setHP(unsigned hp);
        void setInHandAmmo(unsigned ammo);
        void setTotalAmmo(unsigned ammo);
        void setStatus(Status);
        void setIsHurting(bool isHurting);
    };
}