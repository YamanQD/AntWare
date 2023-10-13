#pragma once
#include <vector>
#include <memory>
#include <stdexcept>
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SFML/Graphics/Image.hpp>
#include <Material.h>
namespace aw
{
    /** \brief A textured mesh descriptor class, does not contain material info.
     *
     * All meshes data are stored in a single vertex array object.
     */
    class Mesh
    {
    private:
        enum
        {
            VERTEX_BUFFER_POS,
            VERTEX_BUFFER_NORM,
            VERTEX_BUFFER_TEX,
            INDEX_BUFFER,
            NumBuffers
        };

        static GLuint VAO, VBO, EBO;
        GLuint offsets[NumBuffers];
        GLuint sizes[NumBuffers];
    
    protected:
        /** \brief Assimp library importer class, used to parse meshes from files
         * to Assimp's representation.
         */
        static Assimp::Importer importer;
        bool hasTexture, hasUniformColor, hasIndices;
        std::string name;
        GLuint texture;
        std::vector<unsigned> indices;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;
        glm::vec4 uniformColor;
        /** \brief Loads and stores the textured parsed from \a path , stores the texture
         * handle in ::texture.
         *
         * \param path The path of the image to be loaded and parsed.
         */
        void loadTexture(const char *path);
        unsigned baseVertex;
    public:
        /** \brief Parses the mesh data from \a path and texture data from \a texPath
         * if it was provided.
         *
         * \param path The path of the Assimp's supported mesh file.
         * \param texPath The path of the sf::Image's supported image file, can be null for no texture.
         */
        Mesh(const char *path, const char *texPath = nullptr);
        /** \brief [Deprecated since the modern edition shaders rely
         * on color (albedo) textures only for fragment colors]*/
        Mesh(const char *path, glm::vec4 color, const char *texPath = nullptr);
        /** \brief [Deprecated since the modern edition shaders rely
         * on color (albedo) textures only for fragment colors]*/
        Mesh(const char *path, glm::vec3 color, const char *texPath = nullptr);
        /** \brief Draws the mesh with ::texture.
         *
         * Assumes the shader's uniform variables are set correctly (including
         * the model matrix) before calling this function.
         */
        void draw();
        /** \param texture Overwritten with the mesh's ::texture value only if ::hasTexture is true.
         * \return true if \a texture was overwritten successfully.
         * \return false if ::hasTexture was false and \a texture was not unchanged.
         */
        bool getTexture(GLuint &texture);
        /** \param texture Overwrites mesh's ::texture value and sets ::hasTexture to true.*/
        void setTexture(GLuint texture);
        /** \brief [Deprecated since version 2.0]
         *
         * \param color Overwritten with ::uniformColor only if ::hasUniformColor is true.
         * \return true if \a color was overwritten successfully.
         * \return false if ::hasUniformColor was false and \a color was left unchanged.
         */
        bool getUniformColor(glm::vec4 &color);
        /** \brief [Deprecated since version 2.0]
         *
         * \param color Overwrites ::uniformColor and sets ::hasUniformColor to true.
         */
        void setUniformColor(glm::vec4 color);
        /** \return A const-refernce to ::vertices array; model-space vertices data.*/
        const std::vector<glm::vec3> &getVertices();
        /** \return ::name of the mesh*/
        const std::string getName();
        /** \brief Loads and stores the textured parsed from \a path.
         *
         * \param path The path of the image to be loaded and parsed, must be supported
         * by sf::Image.
         * \return Handle to the newly created texture.
         */
        static int createTexture(const char *path);
        /** \brief Creates a one-for-all vertex array object, places all mesh data in a
         * single vertex buffer and a single elements buffer for better performance.
         *
         * \param meshes The meshes from which to extract data into the buffers, must
         * contain all the Scene meshes.
         */
        static void constructVAO(std::vector<std::shared_ptr<Mesh>> meshes);
        static void freeLastImportedScene();
    };
}