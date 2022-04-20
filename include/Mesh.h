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
        static Assimp::Importer importer;
        bool hasTexture, hasUniformColor, hasIndices;
        GLuint texture;
        std::vector<unsigned> indices;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;
        glm::vec4 uniformColor;
        void loadTexture(const char *path);

        static GLuint VAO, VBO, EBO;
        GLuint offsets[NumBuffers];
        GLuint sizes[NumBuffers];
        unsigned baseVertex;

    public:
        Mesh(const char *path, const char *texPath = nullptr);
        Mesh(const char *path, glm::vec4 color, const char *texPath = nullptr);
        Mesh(const char *path, glm::vec3 color, const char *texPath = nullptr);
        void draw();
        bool getTexture(GLuint &texture);
        void setTexture(GLuint texture);
        bool getUniformColor(glm::vec4 &color);
        void setUniformColor(glm::vec4 color);
        const std::vector<glm::vec3> &getVertices();
        static int createTexture(const char *path);
        static void constructVAO(std::vector<std::shared_ptr<Mesh>> meshes);
    };
}