#include<helpers.h>
using namespace std;
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