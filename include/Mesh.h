#pragma once
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/mesh.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
namespace aw
{
    class Mesh
    {
    private:
        static Assimp::Importer importer;
        std::vector<glm::vec3> vertices;
        std::vector<glm::vec3> normals;
        std::vector<glm::vec2> texCoords;

    public:
        Mesh(const char *path);
        //TODO draw function, recommended to be implemented by @YamanQD
    };
}