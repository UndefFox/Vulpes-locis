#ifndef H_RENDERENGINE_RENDERER
#define H_RENDERENGINE_RENDERER

#include <vector>
#include <array>

namespace RenderEngine {

/**
 * Draws a new frame and displaying it on window.
 */
void drawFrame();

struct DrawCall {
    int meshId;
    std::array<float, 3> position;
};

void addDrawCall(DrawCall drawCall);

} // namespace RenderEngine

#endif