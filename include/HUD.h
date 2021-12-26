#pragma once
#include <GL/glew.h>
#define HUD aw::Hud::instance()
namespace aw
{
    class Hud
    {
    private:
        Hud();

    public:
        static Hud &instance();
        void draw();
    };
}