#include <Window.h>
using namespace aw;
Window::Window() {}
Window &Window::instance()
{
    static Window window;
    return window;
}
void Window::init(int height, int width)
{
    sf::ContextSettings ctxSettings;
    ctxSettings.antialiasingLevel = 4;
    ctxSettings.depthBits = 24;
    ctxSettings.majorVersion = 1;
    ctxSettings.minorVersion = 5;
    ctxSettings.stencilBits = 0;
    internal.create(sf::VideoMode(width, height), "Ants-Fighter: LEGACY EDITION", sf::Style::Default, ctxSettings);
    internal.setMouseCursorVisible(false);
}
void Window::terminate()
{
    internal.close();
}