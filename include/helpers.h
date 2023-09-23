/** \file helpers.h
 *  \brief A set of general helper functions.
 */
#pragma once
#include <fstream>
#include <vector>
#include <assert.h>
namespace aw
{
    /** \brief Reads a binary file.
     * \param path The path of the binary file to be read.
     * \return The bytes of the file specified in path.
     */
    std::vector<char> readBinFile(const char *path);
}