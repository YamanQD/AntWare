#include <assimp/matrix4x4.h>
#include <glm/matrix.hpp>
#include<helpers.h>
using namespace std;
using namespace glm;

vector<char> aw::readBinFile(const char* path){
    vector<char> data;
    fstream fileStream(path, ios::binary | ios::ate | ios::in);
    if(!fileStream.is_open()){
        printf("Failed to open file at %s", path);
        assert(0);
    }
    data.resize(fileStream.tellg());
    fileStream.seekg(0, ios::beg);
    fileStream.read(data.data(), data.size());
    fileStream.flush();
    fileStream.close();
    return data;
}

mat4 aw::convertAssimpMatToGLM(aiMatrix4x4& matrix){
    mat4* reinterpretedMatrix=reinterpret_cast<mat4*>(&matrix);

    //Assimp matrices are row-major while GLM's are column-major
    return transpose(*reinterpretedMatrix);
}