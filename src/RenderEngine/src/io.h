#ifndef H_RENDERENGINE_IO
#define H_RENDERENGINE_IO

#include <string>
#include <vector>

namespace RenderEngine {

/**
 * Load code from spv files into code vector.
 */
void loadShaderFile(std::string filename, std::vector<char>& code);

} // namespace RenderEngine

#endif