#pragma once
#include <SFML/Window.hpp>
#define WINDOW aw::Window::instance()

#define FALLBACK_RES_WIDTH 1280u
#define FALLBACK_RES_HEIGHT 720u
#define WINDOW_TITLE "AntWare"

namespace aw
{
    /** \brief Internal sf::Window handle.*/
    class Window
    {
    private:
        Window();

    public:
        /** \brief A handle to SFML's sf::Window instance, used for low-level window operations.*/
        sf::Window internal;
        static Window &instance();
        /** \brief Creates an OpenGL 3.3 capable window.
         *
         * \param height The height of the window.
         * \param width The width of the window.
         * \param fullScreen Controls whether the game runs in fullscreen (if true) or windowed mode (if false).
         */
        void init(int height, int width,bool fullScreen);
        /** \brief Closes ::internal window.*/
        void terminate();
    };
}