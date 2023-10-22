#include <Renderer.h>
#include <SkinnedMesh.h>
#include <cstddef>
#include <helpers.h>

using namespace std;
using namespace aw;
using namespace glm;

GLuint SkinnedMesh::skinnedVAO;
GLuint SkinnedMesh::skinnedVBO;
GLuint SkinnedMesh::skinnedEBO;

SkinnedMesh::SkinnedMesh(const char *path, const char *texPath)
    : Mesh(path, texPath) {
  auto scene = importer.GetScene();

  auto mesh = scene->mMeshes[0];

  bonesIDs.resize(vertices.size(), 0);

  for (size_t i = 0; i < vertices.size(); ++i) {
    for (size_t j = 0; j < mesh->mNumBones; ++j) {
      if (mesh->mBones[j]->mWeights[i].mWeight >
          mesh->mBones[bonesIDs[i]]->mWeights[i].mWeight) {
        bonesIDs[i] = j;
      }
    }
  }

  bonesInverseBindMats.resize(mesh->mNumBones);
  for (size_t i = 0; i < mesh->mNumBones; ++i) {
    bonesInverseBindMats[i] =
        convertAssimpMatToGLM(mesh->mBones[i]->mOffsetMatrix);
  }
}

void SkinnedMesh::constructSkinnedVAO(
    std::vector<std::shared_ptr<SkinnedMesh>> meshes) {
  vector<char> vertexBuffer, indexBuffer;
  size_t vertexBufferSize = 0, indexBufferSize = 0, normalsOffset = 0,
         texCoordsOffset = 0, bonesIDsOffset, indicesOffset = 0;
  for (unsigned i = 0; i < meshes.size(); ++i) {
    for (unsigned j = 0; j < NUM_BUFFERS; ++j) {
      meshes[i]->offsets[j] =
          (i == 0) ? 0 : meshes[i - 1]->offsets[j] + meshes[i - 1]->sizes[j];
    }
    meshes[i]->sizes[VERTEX_BUFFER_POS] =
        meshes[i]->vertices.size() * sizeof(vec3);
    meshes[i]->sizes[VERTEX_BUFFER_NORM] =
        meshes[i]->normals.size() * sizeof(vec3);
    meshes[i]->sizes[VERTEX_BUFFER_TEX] =
        meshes[i]->texCoords.size() * sizeof(vec2);
    meshes[i]->sizes[VERTEX_BUFFER_BONE_ID] =
        meshes[i]->bonesIDs.size() * sizeof(unsigned);
    meshes[i]->sizes[INDEX_BUFFER] =
        meshes[i]->indices.size() * sizeof(unsigned int);
    vertexBufferSize += meshes[i]->sizes[VERTEX_BUFFER_POS] +
                        meshes[i]->sizes[VERTEX_BUFFER_NORM] +
                        meshes[i]->sizes[VERTEX_BUFFER_TEX] +
                        meshes[i]->sizes[VERTEX_BUFFER_BONE_ID];

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
  bonesIDsOffset = texCoordsOffset +
                   meshes[meshes.size() - 1]->offsets[VERTEX_BUFFER_TEX] +
                   meshes[meshes.size() - 1]->sizes[VERTEX_BUFFER_TEX];

  vertexBuffer.resize(vertexBufferSize);
  indexBuffer.resize(indexBufferSize);
  for (unsigned i = 0; i < meshes.size(); ++i) {
    memcpy(vertexBuffer.data() + meshes[i]->offsets[VERTEX_BUFFER_POS],
           meshes[i]->vertices.data(), meshes[i]->sizes[VERTEX_BUFFER_POS]);
    memcpy(vertexBuffer.data() + meshes[i]->offsets[VERTEX_BUFFER_NORM] +
               normalsOffset,
           meshes[i]->normals.data(), meshes[i]->sizes[VERTEX_BUFFER_NORM]);
    memcpy(vertexBuffer.data() + meshes[i]->offsets[VERTEX_BUFFER_TEX] +
               texCoordsOffset,
           meshes[i]->texCoords.data(), meshes[i]->sizes[VERTEX_BUFFER_TEX]);
    memcpy(vertexBuffer.data() + meshes[i]->offsets[VERTEX_BUFFER_BONE_ID] +
               bonesIDsOffset,
           meshes[i]->bonesIDs.data(), meshes[i]->sizes[VERTEX_BUFFER_BONE_ID]);
    memcpy(indexBuffer.data() + meshes[i]->offsets[INDEX_BUFFER],
           meshes[i]->indices.data(), meshes[i]->sizes[INDEX_BUFFER]);
  }

  glGenVertexArrays(1, &skinnedVAO);

  glBindVertexArray(skinnedVAO);

  glGenBuffers(1, &skinnedVBO);
  glBindBuffer(GL_ARRAY_BUFFER, skinnedVBO);

  glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, vertexBuffer.data(),
               GL_STATIC_DRAW);
  glGenBuffers(1, &skinnedEBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skinnedEBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, indexBuffer.data(),
               GL_STATIC_DRAW);
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)normalsOffset);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void *)texCoordsOffset);
  glVertexAttribPointer(3, 1, GL_UNSIGNED_INT, GL_FALSE, 0,
                        (void *)bonesIDsOffset);

  assert(glGetError() == 0);
}


//NOTE: Not tested.
void SkinnedMesh::draw(){
  glUniform1i(RENDERER.getSkinnedToggleLocation(),1);
  glUniformMatrix4fv(RENDERER.getBonesLocation(),MAX_BONES,GL_FALSE,&bonesInverseBindMats[0][0][0]);


  if (hasTexture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
    }

    glBindVertexArray(skinnedVAO);
    glDrawElementsBaseVertex(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, (void *)(offsets[INDEX_BUFFER]), baseVertex);

    glBindTexture(GL_TEXTURE_2D, 0);

    glUniform1i(RENDERER.getSkinnedToggleLocation(),0);

    assert(glGetError() == 0);
}