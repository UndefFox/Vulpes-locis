#ifndef H_RENDERENGINE_RENDERER
#define H_RENDERENGINE_RENDERER

#include "RenderEngine/types/drawcall.h"

#include <array>

namespace RenderEngine {

/**
 * Draws a new frame and displaying it on window. All drawcalls
 * deleted.
 */
void drawFrame();

/**
 * Adds new drawcall to queue. All drawcalls will be executed
 * at drawFrame() call.
 */
void addDrawCall(DrawCall drawCall);

/**
 * Sets render properties of view.
 */
void setCamera(std::array<float, 3> pos, std::array<float, 3> rotation);

} // namespace RenderEngine

#endif