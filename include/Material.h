#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
namespace aw
{
    /** \brief Mesh's material data, used to set uniform material struct in the
     * main shader to describe how lights affect the Mesh's surface.
     *
     * Each material is define by an ambient vector, a diffuse vector, a specular vector,
     * a shininess factor and an alpha value.
     *
     * Check out Shaders/main.frag for more implmenation info of the shader and how
     * the material data is used.
     */
    class Material
    {
    private:
        glm::vec4 ambient, diffuse, specular;
        float shininess, alpha = 1.0f;
        static GLint ambientLoc, diffuseLoc, specularLoc, shininessLoc, alphaLoc;

    public:
        /** \brief Creates a material using the provided parameters
         *
         * \param ambient The ambient color vector (unsigned normalized RGBA)
         * vector of the material.
         * \param diffuse The diffuse color vector
         * (unsigned normalized RGBA) of the material.
         * \param specular The specular color vector (unsigned normalized RGBA) of the material.
         * \param shininess The shininess factor of the material.
         */
        Material(glm::vec4 ambient, glm::vec4 diffuse, glm::vec4 specular,
                 float shininess);
        /** \brief Creates a material using predefine parameters, check out
         * the implementation for the parameters values.
         */
        Material();
        /** \param ambient Overwrites ::ambient*/
        void setAmbient(glm::vec4 ambient);
        /** \param diffure Overwrites ::diffuse*/
        void setDiffuse(glm::vec4 diffuse);
        /** \param specular Overwrites ::specular*/
        void setSpecular(glm::vec4 specular);
        /** \param shininess Overwrites ::shininess*/
        void setShininess(float shininess);
        /** \param alpha Overwrites ::alpha*/
        void setAlpha(float alpha);
        /** \return ::alpha.*/
        float getAlpha();
        /** \brief Writes the material data into the uniform material struct
         * in the main shader.
         */
        void apply();

        /** \brief Gets the shader's material struct data fields locations
         * which will be used to later apply the material in ::apply.
         *
         * Writes ::ambientLoc, ::diffuseLoc, ::specularLoc, ::shininessLoc
         * and ::alphaLoc values.
         *
         * \param program The shader program of which to extract material
         * fields locations.
         */
        static void setUniformsLocation(GLuint program);
    };
}