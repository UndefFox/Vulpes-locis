#ifndef H_RENDERENGINE_RENDERER
#define H_RENDERENGINE_RENDERER

#include <vector>
#include <array>

namespace RenderEngine {

/**
 * Draws a new frame and displaying it on window.
 */
void drawFrame(std::vector<int> IDs, std::vector<std::array<float, 3>> dynamic);

}

#endif