#ifndef H_RENDERENGINE_IO
#define H_RENDERENGINE_IO

#include <string>
#include <vector>

namespace RenderEngine {

void loadShaderFile(std::string filename, std::vector<char>& code);

}

#endif