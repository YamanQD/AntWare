#pragma once
#include <SFML/Window.hpp>
#define WINDOW aw::Window::instance()
namespace aw
{
    class Window
    {
    private:
        Window();

    public:
        sf::Window internal;
        static Window &instance();
        void init(int height, int width);
        void terminate();
    };
}