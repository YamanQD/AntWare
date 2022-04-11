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
    ctxSettings.antialiasingLevel = 1;
    ctxSettings.depthBits = 24;
    ctxSettings.majorVersion = 3;
    ctxSettings.minorVersion = 3;
    ctxSettings.stencilBits = 0;
    ctxSettings.attributeFlags = ctxSettings.Core;
    internal.create(sf::VideoMode(width, height), "AntWare: LEGACY EDITION", sf::Style::Default, ctxSettings);
    internal.setMouseCursorVisible(false);
}
void Window::terminate()
{
    internal.close();
}