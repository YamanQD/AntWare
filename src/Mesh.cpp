#include <Mesh.h>
using namespace aw;
using namespace glm;
using namespace std;
using namespace Assimp;
using namespace sf;
Importer Mesh::importer;
Mesh::Mesh(const char *path, const char *texPath) //TODO create texture if not nullptr
{
    aiMesh *mesh = importer.ReadFile(path, aiProcess_Triangulate)->mMeshes[0];
    vertices.resize(mesh->mNumVertices);
    for (unsigned i = 0; i < vertices.size(); ++i)
        vertices[i] = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
    if (mesh->HasNormals())
    {
        normals.resize(mesh->mNumVertices);
        for (unsigned i = 0; i < normals.size(); ++i)
            normals[i] = {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z};
    }
    if (mesh->HasTextureCoords(0))
    {
        texCoords.resize(mesh->mNumVertices);
        for (unsigned i = 0; i < texCoords.size(); ++i)
            texCoords[i] = {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y};
    }
    importer.FreeScene();
}
Mesh::~Mesh()
{
    delete texture;
}
Mesh::Texture::Texture(const char* path){
    
}