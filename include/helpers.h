/** \file helpers.h
 *  \brief A set of general helper functions.
 */
#pragma once
#include <assimp/matrix4x4.h>
#include <fstream>
#include <glm/fwd.hpp>
#include<glm/glm.hpp>
#include <vector>
#include <assert.h>
namespace aw
{
    /** \brief Reads a binary file.
     * \param path The path of the binary file to be read.
     * \return The bytes of the file specified in path.
     */
    std::vector<char> readBinFile(const char *path);

    glm::mat4 convertAssimpMatToGLM(aiMatrix4x4& matrix);
}