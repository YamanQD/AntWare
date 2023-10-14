#include <helpers.h>
#include <SkinnedMesh.h>
#include <cstddef>

using namespace aw;

SkinnedMesh::SkinnedMesh(const char *path, const char *texPath)
    : Mesh(path, texPath) {
  auto scene = importer.GetScene();

  auto mesh = scene->mMeshes[0];

  bonesIDs.resize(vertices.size(), 0);

  for (size_t i = 0; i < vertices.size(); ++i) {
    for (size_t j = 0; j < bonesIDs.size(); ++j) {
      if (mesh->mBones[j]->mWeights[i].mWeight >
          mesh->mBones[bonesIDs[i]]->mWeights[i].mWeight) {
        bonesIDs[i] = j;
      }
    }
  }

  bonesInverseBindMats.resize(mesh->mNumBones);
  for(size_t i=0;i<mesh->mNumBones;++i){
    bonesInverseBindMats[i]=convertAssimpMatToGLM(mesh->mBones[i]->mOffsetMatrix);
  }
}