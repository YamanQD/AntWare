#pragma once
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
            std::vector<std::string> levels;
        } settings;

        App();
        void start();
        void update();
        void readSettingsFile();
        void switchScene(int index);

        sf::Clock timeSinceStart;
        Scene *currentScene = nullptr;
        int currentSceneIndex;
        float deltaTime = 0.0f;
        Status gameStatus;
        float waitToSwitchLevel = 0.5f;
        float timeSinceWon = 0.0f;
        sf::Music music01;

    public:
        static App &instance();
        void init(int argc, char **argv);
        void loop();
        void terminate();
        float getTime();
    };
}
