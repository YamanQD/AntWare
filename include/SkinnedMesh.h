#pragma once

#include <Mesh.h>
namespace aw{
    class SkinnedMesh:public Mesh{
    private:
        enum{
            VERTEX_BUFFER_POS,
            VERTEX_BUFFER_NORM,
            VERTEX_BUFFER_TEX,
            VERTEX_BUFFER_BONE_ID,
            INDEX_BUFFER,
            NUM_BUFFERS
        };

        GLuint offsets[NUM_BUFFERS];
        GLuint sizes[NUM_BUFFERS];

        std::vector<unsigned> bonesIDs;
    };
}