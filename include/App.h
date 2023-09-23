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
     * it also contains logic for inter-GameObjects interactions since game objects
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
        /** \brief Initilizes the application and main menu, awaits user level selection.
         * 
         * Runs Menu::loop until the user selects a level, loads the selected scene and sets
         * up ::currentScene and the HUD and sets ::gameStatus to Status::ONGOING.
         * 
         * \return false if the user closed the game while in the main menu.
         * \return true if the user selected a level from the main menu.
        */
        bool init();
        void loop();
        void terminate();
        float getTime();
    };
}
