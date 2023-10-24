#pragma once
#include <assert.h>
#include <fstream>
#include <vector>
#include <exception>
#include <random>
#include <rapidjson/document.h>
#include <GL/glew.h>
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>
#include <Window.h>
#include <Renderer.h>
#include <Menu.h>
#include <Mesh.h>
#include <Transform.h>
#include <Physics.h>
#include <Scene.h>
#include <Player.h>
#include <Ant.h>
#define APP aw::App::instance()
/** \brief The namespace used across all of the game classes,
 * short for AntWare.
 */
namespace aw
{
    /** \brief Game's lifecycle manager.
     *
     * While it serves mainly as a lifecycle states manager,
     * it also contains logic for inter-GameObjects interactions since GameObject instances
     * do not have access to one another.
     *
     */
    class App
    {
    private:
        /** \brief Game's resolution and levels labels textures, music and JSON files paths
         *
         */
        struct Settings
        {
            int resHeight, resWidth;
            bool fullScreen;
            std::vector<std::string> levels;
            std::vector<std::string> levelsLabels;
            std::vector<std::string> levelsMusic;
        } settings;

        App();
        /** \brief Sets up the GameObject instances from the created Scene.
         *
         * Calls GameObject::start on all of the GameObject instances in ::currentScene,
         * it also restarts ::timeSinceStart timer.
         */
        void start();
        /** \brief Calls %update function on ::currentScene updatable members, handle mutual
         * interactions between GameObject instances and move game state from
         * Status::ONGOING to Status::WIN or Status::LOSE.
         *
         */
        void update();
        /** \brief Reads "settings.json" and fills App::settings using it, falls back to
         * "default_settings.json" if "settings.json" was not found.
         *
         */
        void readSettingsFile();

        /** \brief A timer since the ::currentScene start.*/
        sf::Clock timeSinceStart;

        /** \brief The loaded and currently running Scene.*/
        Scene *currentScene;
        float deltaTime = 0.0f;
        /** \brief The ::currentScene Status.*/
        Status gameStatus;
        sf::Music music;
        sf::SoundBuffer easterEggSoundBuffer;
        sf::Sound easterEggSound;

    public:
        static App &instance();
        /** \brief Initilizes the App and Main Menu, awaits user Scene selection.
         *
         * Initilizes the Window, Renderer and Menu, runs Menu::loop until the user
         * selects a Scene, loads the selected Scene and sets
         * up ::currentScene and the Hud and sets ::gameStatus to Status::ONGOING.
         *
         * \return false if the user closed the game while in the Main Menu.
         * \return true if the user selected a Scene from the Main Menu.
         */
        bool init();
        /** \brief Handles game main loop, processes a single frame.
         *
         * Calls Physics::apply, ::update and Renderer::renderScene if gameStatus is Status::ONGOING,
         * otherwise renders a single Hud screen (simply a YOU WIN or YOU LOSE screen),
         * handles user inputs that require handling using SFML events like a single key press or a single
         * key release
         */
        void loop();
        /** \brief Calls Renderer::terminate, Window::terminate and frees up ::currentScene.*/
        void terminate();
        /** \return ::timeSinceStart in seconds.*/
        float getTime();
    };
}
