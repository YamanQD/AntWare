#pragma once
#include <vector>
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
        class Texture
        {
        public:
            GLuint id;
            Texture(const char *path);
        };
        static Assimp::Importer importer;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords; //TODO store trasformations in a suitable way
        Texture *texture = nullptr;

    public:
        Mesh(const char *path, const char *texPath = nullptr);
        //TODO draw function, recommended to be implemented by @YamanQD
    };
}