#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <Window.h>
using namespace aw;
Window::Window() {}
Window &Window::instance() {
  static Window window;
  return window;
}
void Window::init(int height, int width, bool fullScreen) {
  sf::ContextSettings ctxSettings;
  ctxSettings.antialiasingLevel = 1;
  ctxSettings.depthBits = 24;
  ctxSettings.majorVersion = 3;
  ctxSettings.minorVersion = 3;
  ctxSettings.stencilBits = 0;
  ctxSettings.attributeFlags = ctxSettings.Core;
  if (fullScreen) {
    auto fullScreenModes = sf::VideoMode::getFullscreenModes();
    if (height > 0 && width > 0) {
      sf::VideoMode vm(width, height, 24);
      if (vm.isValid()) {
        internal.create(vm, WINDOW_TITLE, sf::Style::Fullscreen, ctxSettings);
      } else {
        printf("%s\n", "Providied resolution not supported, falling back to "
                       "best settings.");
        internal.create(fullScreenModes[0], WINDOW_TITLE, sf::Style::Fullscreen,
                        ctxSettings);
      }
    } else {
      internal.create(fullScreenModes[0], WINDOW_TITLE, sf::Style::Fullscreen | sf::Style::None,
                      ctxSettings);
    }
  } else if (height > 0 && width > 0) {
    internal.create(sf::VideoMode(width, height), WINDOW_TITLE,
                    sf::Style::Default, ctxSettings);
  } else {
    internal.create(sf::VideoMode(FALLBACK_RES_WIDTH, FALLBACK_RES_HEIGHT),
                    WINDOW_TITLE, sf::Style::Default, ctxSettings);
  }
  internal.setMouseCursorVisible(false);
}
void Window::terminate() { internal.close(); }