#pragma once
#include <vector>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>
#include <Window.h>
#include <HUD.h>
#include<glm/gtc/matrix_transform.hpp>
#define MENU Menu::instance()
namespace aw
{
    /** \brief Main %Menu lifecycle manager.
     * 
     * Manages tha main menu from App::init until App::init returns 
     * and a user selects a Scene or quits the game.
    */
    class Menu
    {
    private:
        Menu();
        sf::Music music;
        sf::SoundBuffer menuPickSoundBuffer, menuNavigateSoundBuffer;
        sf::Sound menuPickSound, menuNavigateSound;
        std::vector<std::string> levels;
        std::vector<GLuint> labels;
        GLuint backgroundTex, gameLabelTex, creditsTex;
        glm::vec2 backgroundSize = {12, 12};
        glm::vec2 gameLabelSize = {5, 5};
        glm::vec2 gameLabelPos = {-5.5f, 1};
        glm::vec2 creditsSize = {5, 5};
        glm::vec2 creditsPos = {5.4f, -5.0f};
        glm::vec3 clearColor = {0, 0, 0};
        /** \brief Non-selected Scene labels textures color multiplier.*/
        glm::vec3 dimColor = {0.5f, 0.5f, 0.5f};
        int selectedLvl = 0;
        glm::vec2 firstLevelPos = {-6, 0};
        glm::vec2 labelSize = {5, 5};
        float yMargain = -0.7f;

    public:
        static Menu &instance();
        /** \brief Loads the Main Menu resources.
         * 
         * Loads the main theme, SFX, main menu textures
         * and \a lables textures.
         * 
         * \param levels The paths to Scene files corresponding to \a labels.
         * \param labels The paths to labels textures.
        */
        void init(std::vector<std::string> levels, std::vector<std::string> labels);
        /** \brief Renders main menu and handles user input.
         * 
         * Handles user navigation, selecting or quiting the game.
         * The main menu rendering is using Hud::drawQuad and shader, and hence
         * using its coordination system.
         * 
         * \return An index to a Scene path in ::levels if the selects a Scene.
         * \return -1 if the user chooses to quit the game by either closing the window
         * or pressing ESC.
        */
        int loop();
    };
}