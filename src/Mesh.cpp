#include <Mesh.h>
using namespace aw;
using namespace glm;
using namespace std;
using namespace Assimp;
using namespace sf;

Importer Mesh::importer;
GLuint Mesh::VAO;
GLuint Mesh::VBO;
GLuint Mesh::EBO;

Mesh::Mesh(const char *path, const char *texPath)
{
    const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate);
    if (!scene)
        throw runtime_error(path); // TODO prettier formatting
    aiMesh *mesh = scene->mMeshes[0];
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
    uniformColor = color;
}
Mesh::Mesh(const char *path, glm::vec3 color, const char *texPath) : Mesh(path,
                                                                          glm::vec4(color, 1),
                                                                          texPath) {}
void Mesh::loadTexture(const char *path)
{
    Image image;
    if (!image.loadFromFile(path))
    {
        throw runtime_error(path); // TODO prettier formatting
    }
    image.flipVertically();
    hasTexture = true;
    int imgHeight = image.getSize().y;
    int imgWidth = image.getSize().x;
    const Uint8 *imgData = image.getPixelsPtr();

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    glGenerateMipmap(GL_TEXTURE_2D);
}
int Mesh::createTexture(const char *path)
{
    Image image;
    if (!image.loadFromFile(path))
    {
        throw runtime_error(path);
    }
    image.flipVertically();
    int imgHeight = image.getSize().y;
    int imgWidth = image.getSize().x;
    const Uint8 *imgData = image.getPixelsPtr();
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
    glGenerateMipmap(GL_TEXTURE_2D);
    return texture;
}
void Mesh::draw()
{
    if (hasTexture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    glBindVertexArray(VAO);
    glDrawElementsBaseVertex(GL_TRIANGLES, sizes[INDEX_BUFFER] / sizeof(unsigned), GL_UNSIGNED_INT, 0, baseVertex);

    glBindTexture(GL_TEXTURE_2D, 0);
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
const vector<vec3> &Mesh::getVertices()
{
    return vertices;
}

void Mesh::constructVAO(vector<shared_ptr<Mesh>> meshes)
{
    vector<char> vertexBuffer, indexBuffer;
    size_t vertexBufferSize = 0, indexBufferSize = 0,
           normalsOffset = 0, texCoordsOffset = 0, indicesOffset = 0;
    for (unsigned i = 0; i < meshes.size(); ++i)
    {
        for (unsigned j = 0; j < NumBuffers; ++j)
        {
            meshes[i]->offsets[j] = (i == 0) ? 0 : meshes[i - 1]->offsets[j] + meshes[i - 1]->sizes[j];
        }
        meshes[i]->sizes[VERTEX_BUFFER_POS] = meshes[i]->vertices.size() * sizeof(vec3);
        meshes[i]->sizes[VERTEX_BUFFER_NORM] = meshes[i]->normals.size() * sizeof(vec3);
        meshes[i]->sizes[VERTEX_BUFFER_TEX] = meshes[i]->texCoords.size() * sizeof(vec2);
        meshes[i]->sizes[INDEX_BUFFER] = meshes[i]->indices.size() * sizeof(unsigned int);
        vertexBufferSize += meshes[i]->sizes[VERTEX_BUFFER_POS] +
                            meshes[i]->sizes[VERTEX_BUFFER_NORM] +
                            meshes[i]->sizes[VERTEX_BUFFER_TEX];

        meshes[i]->baseVertex = indicesOffset;
        indicesOffset += meshes[i]->vertices.size();
    }
    indexBufferSize = meshes[meshes.size() - 1]->offsets[INDEX_BUFFER] +
                      meshes[meshes.size() - 1]->sizes[INDEX_BUFFER];
    normalsOffset = meshes[meshes.size() - 1]->offsets[VERTEX_BUFFER_POS] +
                    meshes[meshes.size() - 1]->sizes[VERTEX_BUFFER_POS];
    texCoordsOffset = normalsOffset +
                      meshes[meshes.size() - 1]->offsets[VERTEX_BUFFER_NORM] +
                      meshes[meshes.size() - 1]->sizes[VERTEX_BUFFER_NORM];

    vertexBuffer.resize(vertexBufferSize);
    indexBuffer.resize(indexBufferSize);
    for (unsigned i = 0; i < meshes.size(); ++i)
    {
        memcpy(vertexBuffer.data() + meshes[i]->offsets[VERTEX_BUFFER_POS],
               meshes[i]->vertices.data(), meshes[i]->sizes[VERTEX_BUFFER_POS]);
        memcpy(vertexBuffer.data() + meshes[i]->offsets[VERTEX_BUFFER_NORM] + normalsOffset,
               meshes[i]->normals.data(), meshes[i]->sizes[VERTEX_BUFFER_NORM]);
        memcpy(vertexBuffer.data() + meshes[i]->offsets[VERTEX_BUFFER_TEX] + texCoordsOffset,
               meshes[i]->texCoords.data(), meshes[i]->sizes[VERTEX_BUFFER_TEX]);
        memcpy(indexBuffer.data() + meshes[i]->offsets[INDEX_BUFFER],
               meshes[i]->indices.data(), meshes[i]->sizes[INDEX_BUFFER]);
    }

    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, vertexBuffer.data(), GL_STATIC_DRAW);
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexBuffer.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)normalsOffset);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *)texCoordsOffset);

    assert(glGetError() == 0);
}
