#pragma once

#include <Mesh.h>
#include <cstddef>
#include <glm/common.hpp>
#include <memory>
namespace aw {
class SkinnedMesh : public Mesh {
private:
  enum {
    VERTEX_BUFFER_POS,
    VERTEX_BUFFER_NORM,
    VERTEX_BUFFER_TEX,
    VERTEX_BUFFER_BONE_ID,
    INDEX_BUFFER,
    NUM_BUFFERS
  };

  static GLuint skinnedVBO, skinnedEBO, skinnedVAO;
  GLuint offsets[NUM_BUFFERS];
  GLuint sizes[NUM_BUFFERS];

  std::vector<unsigned> bonesIDs;
  
  std::vector<glm::mat4> bonesInverseBindMats;

public:
  SkinnedMesh(const char *path, const char *texPath = nullptr);

  static void constructSkinnedVAO(std::vector<std::shared_ptr<SkinnedMesh>> skinnedMeshes);
};
} // namespace aw