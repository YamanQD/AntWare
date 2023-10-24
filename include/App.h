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
namespace aw
{
    class App
    {
    private:
        struct Settings
        {
            int resHeight, resWidth;
            bool fullScreen;
            std::vector<std::string> levels;
            std::vector<std::string> levelsLabels;
            std::vector<std::string> levelsMusic;
        } settings;

        App();
        void start();
        void update();
        void readSettingsFile();

        sf::Clock timeSinceStart;
        Scene *currentScene;
        float deltaTime = 0.0f;
        Status gameStatus;
        sf::Music music;
        sf::SoundBuffer easterEggSoundBuffer;
        sf::Sound easterEggSound;

    public:
        static App &instance();
        bool init(int argc, char **argv);
        void loop();
        void terminate();
        float getTime();
    };
}
