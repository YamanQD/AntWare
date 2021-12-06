#pragma once
#define APP aw::App::instance()
namespace aw
{
    class App
    {
    private:
        App();

    public:
        static App &instance();
        void init(int argc, char **argv);
        void loop();
        void terminate();
    };
}
