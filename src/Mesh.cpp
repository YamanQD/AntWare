#include <Mesh.h>
using namespace aw;
using namespace glm;
using namespace std;
using namespace Assimp;
using namespace sf;
Importer Mesh::importer;
Mesh::Mesh(const char *path, const char *texPath)
{
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate);
    if (!scene)
        throw runtime_error(path); // TODO prettier formatting
    aiMesh *mesh = importer.ReadFile(path, aiProcess_Triangulate)->mMeshes[0];
    if (texPath)
    {
        loadTexture(texPath);
    }
    else
    {
        hasTexture = false;
    }
    vertices.resize(mesh->mNumVertices);
    for (unsigned i = 0; i < vertices.size(); ++i)
        vertices[i] = {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z};
    if (mesh->HasVertexColors(0))
    {
        colors.resize(mesh->mNumVertices);
        for (unsigned i = 0; i < colors.size(); ++i)
            colors[i] = {mesh->mColors[0][i].r, mesh->mColors[0][i].g,
                         mesh->mColors[0][i].b, mesh->mColors[0][i].a};
    }
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
Mesh::Mesh(const char *path, glm::vec4 color, const char *texPath):Mesh(path,texPath)
{
    hasUniformColor = true;
    uniformColor = color;
}
void Mesh::loadTexture(const char *path)
{
    Image image;
    if (!image.loadFromFile(path))
    {
        throw runtime_error(path); // TODO prettier formatting
    }
    hasTexture = true;
    int imgHeight = image.getSize().y;
    int imgWidth = image.getSize().x;
    const Uint8 *imgData = image.getPixelsPtr();

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, imgWidth, imgHeight, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
}
void Mesh::draw()
{
    if (hasTexture)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < vertices.size(); i++)
    {
        if (hasUniformColor)
        {
            glColor4f(uniformColor.r, uniformColor.g, uniformColor.b, uniformColor.a);
        }
        else if (hasTexture)
        {
            glTexCoord2f(texCoords[i].x, texCoords[i].y);
        }
        else
        {
            glColor4f(colors[i].r, colors[i].g, colors[i].b, colors[i].a);
        }
        glNormal3f(normals[i].x, normals[i].y, normals[i].z);
        glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z);
    }
    glEnd();
    glDisable(GL_TEXTURE_2D);
}
bool Mesh::getTexture(GLuint &texture)
{
    if (hasTexture)
    {
        texture = this->texture;
        return true;
    }
    return false;
}
void Mesh::setTexture(GLuint texture)
{
    hasTexture = true;
    this->texture = texture;
}
bool Mesh::getUniformColor(vec4 &color)
{
    if (hasUniformColor)
    {
        color = this->uniformColor;
        return true;
    }
    return false;
}
void Mesh::setUniformColor(vec4 color)
{
    hasUniformColor = true;
    uniformColor = color;
}