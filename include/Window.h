#pragma once
#include <SFML/Window.hpp>
#define WINDOW aw::Window::instance()
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
        */
        void init(int height, int width);
        /** \brief Closes ::internal window.*/
        void terminate();
    };
}