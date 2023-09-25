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
    /** \brief Scene Renderer.*/
    class Renderer
    {
    private:
        Renderer();
        GLuint mainShader;
        /** \brief A handle to shadeless variable in ::mainShader.
         * 
         * Used to draw shadeless objects in the Scene, most notably
         * the Bullet flash texture.
        */
        GLuint shadelessLocation;

    public:
        static Renderer &instance();
        /** \brief Sets up OpenGL variables and loads shaders.
         * 
         * Initializes GLEW, sets up OpenGL vars and loads and compiles 
         * the ::mainShader and
         * Hud::shaderProgram. 
        */
        void init();
        /** \brief Renders the while \a scene plus the Hud.
         * 
         * Calls Camera::update and Light::update on Scene::camera
         * and Scene::lights instances //TODO continue...
        */
        void renderScene(Scene *scene);
        void terminate();
        GLuint loadShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath);
        GLuint getUniformLocation(const char* uniform);
        GLuint getMainShader();
    };
}