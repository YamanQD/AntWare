#pragma once
#include <SFML/Graphics/Image.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define HUD aw::Hud::instance()
namespace aw
{
    /** \brief The Game's possible states.*/
    enum Status
    {
        WIN,
        LOSE,
        ONGOING,
        LOADING
    };
    /** \brief Heads-Up Display manager for the game.
     *
     * Handles drawing HUD elements on screen using a special shader.
     */
    class Hud
    {
    private:
        enum
        {
            MODEL_MAT,
            COLOR_VEC,
            NumUniforms
        };
        /** \brief Creates in-game textures using ::loadTexture and calls
         * ::createQuadVAO.
         */
        Hud();
        /** \brief The shader handle used to render Hud's elements.*/
        GLuint shaderProgram;
        GLuint uniformsLocations[NumUniforms];
        /** \brief Reusable quad vertex array object handle, used to draw textured quads
         * on screen, representing the Hud altogether.
         */
        GLuint quadVAO; // TODO switch to point sprites
        GLuint crosshair;
        GLuint digits[10];
        GLuint backSlash, plus, ammo;
        /** \brief A semi-transparent (RGBA=(1,0,0,0.3)) quad texture handle.*/
        GLuint hurt;
        GLuint lose, win, loading;
        /** \brief Draws the ::plus icon and ::hp digits.
         *
         * Uses ::drawQuad to draw the ::plus icon and each ::hp digit.
         */
        void drawHP();
        /** \brief Draws the ::ammo icon, ::inHandAmmo digits, ::totalAmmo
         * digits and a ::backSlash between ::inHandAmmo and ::totalAmmo digits.
         *
         * Uses ::drawQuad to draw each element and digit.
         */
        void drawAmmo();
        /** \brief [Depracted] Draws a semi-transparent (RGBA=(1,0,0,0.3)) quad that covers all the screen.
         *
         * Uses legacy OpenGL's immediate mode to achieve the effect.
         */
        void drawHurtEffect();
        /** \brief Current health points.*/
        int hp;
        int inHandAmmo, totalAmmo;
        bool isHurting = false;
        /** \brief Current game Status.*/
        Status status;

        /** \brief Creates a reusable quad vertex array object, stores its handle
         * in ::quadVAO.
         */
        void createQuadVAO();

    public:
        static Hud &instance();
        /** \param program Overwrites ::shaderProgram.
         */
        void setShaderProgram(GLuint program);
        /** \return ::shaderProgram*/
        GLuint getShaderProgram();
        /** \brief Loads the image in \a path into the VRAM and writes
         * its handle in \a tex.
         *
         * \param path The path of the image to be loaded, must be in a format supported by
         * sf::Image.
         * \param tex Gets overwritten with the handle to the newly created texture.
         */
        static void loadTexture(const char *path, GLuint &tex);
        /** \brief Draws a textured quad on the screen with the parameters specified.
         *
         * Draws the quad using ([-16,16],[-16,16]) coordination system.
         *
         * \param texture The quad's texture handle, zero-alpha pixels are discarded in the shader.
         * \param pos The quad's center position in the coord system.
         * \param size The quad's size in the coord system.
         * \param color The quad's color multiplier (tint) in RGB, encoded as unsigned normalized vector-3.
         */
        void drawQuad(GLuint texture, glm::vec2 pos, glm::vec2 size, glm::vec3 color = {1, 1, 1});
        /** \brief Draws in-game HUD according to game ::status.
         *
         * If ::status is Status::ONGOING, it draws the ::crosshair, calls ::drawHP, calls ::drawAmmo
         * and if ::isHurting is true, it draws ::hurt filling the whole screen.
         *
         * If ::status is NOT Status::ONGOING, the corresponding status screen is drawn filling the whole screen.
         */
        void draw();
        /** \param hp Overwrites ::hp.*/
        void setHP(unsigned hp);
        /** \param ammo Overwrites ::inHandAmmo.*/
        void setInHandAmmo(unsigned ammo);
        /** \param ammo Overwrites ::totalAmmo.*/
        void setTotalAmmo(unsigned ammo);
        /** \param status Overwrites ::status.*/
        void setStatus(Status status);
        /** \param isHurting Overwrites ::isHurting.*/
        void setIsHurting(bool isHurting);
    };
}