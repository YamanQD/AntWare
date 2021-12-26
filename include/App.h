#pragma once
#include <fstream>
#include <vector>
#include <exception>
#include <rapidjson/document.h>
#include <GL/glew.h>
#include <SFML/System/Clock.hpp>
#include <Window.h>
#include <Renderer.h>
#include <Mesh.h>
#include <Transform.h>
#include <Physics.h>
#include <Scene.h>
#include <Player.h>
#include <Ant.h>
#include <SoundBuffers.h>
#define APP aw::App::instance()
namespace aw
{
    class App
    {
    private:
        struct Settings
        {
            int resHeight, resWidth;
        } settings;

        App();
        void start();
        void update();
        void readSettingsFile();

        Scene *currentScene;

    public:
        static App &instance();
        void init(int argc, char **argv);
        void loop();
        void terminate();
    };
}
