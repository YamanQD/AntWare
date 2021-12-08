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
    class Mesh
    {
    private:
        static Assimp::Importer importer;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords; //TODO store trasformations in a suitable way
        void loadTexture(const char *path);

    public:
        Mesh(const char *path);
        Mesh(const char *path, const char *texPath = nullptr);
        void draw();
        GLuint texture = 0;
    };
}