#pragma once
#include <GL/glew.h>
#include<helpers.h>
#include <Window.h>
#include <Camera.h>
#include <Scene.h>
#include <HUD.h>
#define RENDERER aw::Renderer::instance()
namespace aw
{
    class Renderer
    {
    private:
        Renderer();
        GLuint mainShader;

    public:
        static Renderer &instance();
        void init();
        void renderScene(Scene *scene);
        void terminate();
        GLuint loadShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath);
        GLuint getUniformLocation(const char* uniform);
        GLuint getMainShader();
    };
}