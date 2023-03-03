#include "io.h"

#include <fstream>

namespace RenderEngine {
    
void loadShaderFile(std::string filename, std::vector<char>& code) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    size_t fileSize = (size_t) file.tellg();
    code.resize(fileSize);

    file.seekg(0);
    file.read(code.data(), fileSize);

    file.close();
} 

} // namespace RenderEngine