#include "filemanager.h"

namespace FileManager {

bool loadShaderFile(std::string filename, std::vector<char>& code) {
    std::ifstream file(SHADER_FILES_DIR + filename, std::ios::ate | std::ios::binary);

    if (!file) {
        return false;
    }

    size_t fileSize = (size_t) file.tellg();
    code.resize(fileSize);

    file.seekg(0);
    file.read(code.data(), fileSize);

    file.close();

    return true;
}

}