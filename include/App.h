#pragma once
#include <fstream>
#include <vector>
#include <exception>
#include <rapidjson/document.h>
#include <GL/glew.h>
#include <Window.h>
#include <Renderer.h>
#include <Mesh.h>
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
        void readSettingsFile();

    public:
        static App &instance();
        void init(int argc, char **argv);
        void loop();
        void terminate();
    };
}
