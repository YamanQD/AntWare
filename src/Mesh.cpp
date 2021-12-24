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
    hasUniformColor = false;
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
    if (mesh->HasFaces())
    {
        hasIndices = true;
        indices.resize(mesh->mNumFaces * 3);
        for (unsigned i = 0; i < indices.size(); i += 3)
        {
            indices[i + 0] = mesh->mFaces[i / 3].mIndices[0];
            indices[i + 1] = mesh->mFaces[i / 3].mIndices[1];
            indices[i + 2] = mesh->mFaces[i / 3].mIndices[2];
        }
    }
    else
    {
        hasIndices = false;
    }
    if (mesh->HasVertexColors(0))
    {
        if (albedo != TEXTURE)
            albedo = VERTEX_COLORS;

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
Mesh::Mesh(const char *path, glm::vec4 color, const char *texPath) : Mesh(path, texPath)
{
    hasUniformColor = true;
    albedo = UNIFORM_COLOR;
    uniformColor = color;
}
Mesh::Mesh(const char *path, glm::vec3 color, const char *texPath) : Mesh(path,
                                                                          glm::vec4(color, 1),
                                                                          texPath) {}
Mesh::Mesh(const char *path, Material *material, const char *texPath) : Mesh(path, texPath)
{
    if (material != nullptr)
    {
        this->material = material;
    }
}
Mesh::~Mesh()
{
    if (material != nullptr)
    {
        delete material;
    }
}
void Mesh::loadTexture(const char *path)
{
    Image image;
    if (!image.loadFromFile(path))
    {
        throw runtime_error(path); // TODO prettier formatting
    }
    image.flipVertically();
    hasTexture = true;
    albedo = TEXTURE;
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
    if (albedo == TEXTURE)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
    }
    if (material != nullptr)
    {
        material->apply();
    }

    glBegin(GL_TRIANGLES);
    unsigned size = hasIndices ? indices.size() : vertices.size();
    for (unsigned i = 0; i < size; i++)
    {
        unsigned index = hasIndices ? indices[i] : i;

        switch (albedo)
        {
        case TEXTURE:
            glTexCoord2f(texCoords[index].x, texCoords[index].y);
            break;
        case UNIFORM_COLOR:
            glColor4f(uniformColor.r, uniformColor.g, uniformColor.b, uniformColor.a);
            break;
        case VERTEX_COLORS:
            glColor4f(colors[index].r, colors[index].g, colors[index].b, colors[index].a);
            break;
        default:
            glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
        }

        glNormal3f(normals[index].x, normals[index].y, normals[index].z);
        glVertex3f(vertices[index].x, vertices[index].y, vertices[index].z);
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
    albedo = TEXTURE;
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
    albedo = UNIFORM_COLOR;
    uniformColor = color;
}
const vector<vec3> &Mesh::getVertices()
{
    return vertices;
}