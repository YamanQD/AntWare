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
    /** \brief Scene Renderer.
     * 
     * As of version 2.0, the rendering pipeline is a shaders-based, it uses Blinn-Phong
     * implemented shaders with no shadows, the renderer is also a basic forward-shading one.
     * 
     * More info on Blinn-Phong shading [here](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_reflection_model)
    */
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
        /** \brief Renders the whole \a scene plus the Hud.
         * 
         * Calls Camera::update and Light::update on Scene::camera
         * and Scene::lights instances, then it calls Scene::skybox::draw,
         * Scene::gameObjects::draw and Hud::draw,
         * it draws the CLASSES::ANT and CLASSES::RAGED_ANT in the end
         * for better transpareny effects.
         *
         * \param scene A pointer to the to-be-rendered Scene.
        */
        void renderScene(Scene *scene);
        /** \brief Does nothing.*/
        void terminate();
        /** \brief Reads and compiles the vertex shader in \a vertexShaderPath
        * and the fragment shader in \a fragmentShaderPath.
        *
        * \param vertexShaderPath A path to the vertex shader source code.
        * \param fragementShaderPath A path to the fragment shader source code.
        * \return A handle to the compiled shader program.
        */
        GLuint loadShaderProgram(const char *vertexShaderPath, const char *fragmentShaderPath);
        /** \param uniform The uniform variable name in ::mainShader.
        * \return \a uniform handle.
        */
        GLuint getUniformLocation(const char* uniform);
        /** \return ::mainShader.*/
        GLuint getMainShader();
    };
}