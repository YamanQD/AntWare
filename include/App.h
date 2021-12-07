#pragma once
#include <rapidjson/document.h>
#include <fstream>
#include<vector>
#include<glad/glad.h>
#include<Window.h>
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
