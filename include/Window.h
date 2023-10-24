#pragma once
#include <SFML/Window.hpp>
#define WINDOW aw::Window::instance()

#define FALLBACK_RES_WIDTH 1280u
#define FALLBACK_RES_HEIGHT 720u
#define WINDOW_TITLE "AntWare"

namespace aw
{
    class Window
    {
    private:
        Window();

    public:
        sf::Window internal;
        static Window &instance();
        void init(int height, int width,bool fullScreen);
        void terminate();
    };
}