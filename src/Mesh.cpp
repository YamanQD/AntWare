#include <Mesh.h>
using namespace aw;
using namespace glm;
using namespace std;
using namespace Assimp;
using namespace sf;
Importer Mesh::importer;
Mesh::Mesh(const char *path, const char *texPath)
{
    aiMesh *mesh;
    try
    {
        mesh = importer.ReadFile(path, aiProcess_Triangulate)->mMeshes[0];
    }
    catch (exception e)
    {
        throw runtime_error(path); //TODO prettier formatting
    }
    if (texPath)
    {
        Image image;
        if (!image.loadFromFile(path))
        {
            throw runtime_error(path); //TODO prettier formatting
        }
        int imgHeight = image.getSize().y;
        int imgWidth = image.getSize().x;
        const Uint8 *imgData = image.getPixelsPtr();
    }
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

void Mesh::draw()
{
    // TODO Texture mapping
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < vertices.size(); i++)
    {
        // glTexCoord2f(texCoords[i].x, texCoords[i].y);
        glNormal3f(normals[i].x, normals[i].y, normals[i].z);
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();
}
