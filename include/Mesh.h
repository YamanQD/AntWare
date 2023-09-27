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

        static GLuint VAO, VBO, EBO;
        GLuint offsets[NumBuffers];
        GLuint sizes[NumBuffers];
        unsigned baseVertex;

    public:
        /** \brief Parses the mesh data from \a path and texture data from \a texPath
         * if it was provided.
         * 
         * \param path The path of the Assimp's supported mesh file.
         * \param texPath The path of the sf::Image's supported image file, can be null for no texture.
        */
        Mesh(const char *path, const char *texPath = nullptr);
        Mesh(const char *path, glm::vec4 color, const char *texPath = nullptr);
        Mesh(const char *path, glm::vec3 color, const char *texPath = nullptr);
        void draw();
        bool getTexture(GLuint &texture);
        void setTexture(GLuint texture);
        bool getUniformColor(glm::vec4 &color);
        void setUniformColor(glm::vec4 color);
        const std::vector<glm::vec3> &getVertices();
        const std::string getName();
        static int createTexture(const char *path);
        static void constructVAO(std::vector<std::shared_ptr<Mesh>> meshes);
    };
}