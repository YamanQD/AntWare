#pragma once
#include <GL/glew.h>
#include <Window.h>
#include <Camera.h>
#define RENDERER aw::Renderer::instance()
namespace aw
{
    class Renderer
    {
    private:
        Renderer();
        Camera camera;

    public:
        static Renderer &instance();
        void init();
        void terminate();
    };
}