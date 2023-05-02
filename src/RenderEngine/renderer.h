#ifndef H_RENDERENGINE_RENDERER
#define H_RENDERENGINE_RENDERER

#include "RenderEngine/types/drawcall.h"

#include <array>

/**
 * \defgroup RenderEngine
 * \brief All render engine components.
 */

/**
 * \defgroup RenderInterface
 * \brief All components for using render engine.
 * \ingroup RenderEngine
 */

/**
 * \defgroup RenderSource
 * \brief All components used only in render engine.
 * \ingroup RenderEngine
 */

/**
 * \file
 * \brief All functionality for rendering.
 * 
 * Implements all functionality for rendering frames.
 * 
 * \ingroup RenderInterface
 */

/**
 * \brief Render engine of game.
 * 
 * Implements rendering, storing assets.
 */
namespace RenderEngine {

/**
 * Duration of last frame in seconds.
 */
extern double lastFrameDuration;

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