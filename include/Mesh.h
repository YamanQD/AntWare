#pragma once
#include <vector>
#include <stdexcept>
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <SFML/Graphics/Image.hpp>
namespace aw
{
    enum albedoOptions
    {
        TEXTURE,
        VERTEX_COLORS,
        UNIFORM_COLOR
    };
    class Mesh
    {
    private:
        static Assimp::Importer importer;
        bool hasTexture, hasUniformColor;
        GLuint texture;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords; //TODO store trasformations in a suitable way
        std::vector<glm::vec4> colors;
        glm::vec4 uniformColor;
        void loadTexture(const char *path);

    public:
        Mesh(const char *path, const char *texPath = nullptr);
        Mesh(const char *path, glm::vec4 color, const char *texPath = nullptr);
        void draw();
        bool getTexture(GLuint &texture);
        void setTexture(GLuint texture);
        bool getUniformColor(glm::vec4 &color);
        void setUniformColor(glm::vec4 color);
    };
}