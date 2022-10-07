#ifndef H_RENDERENGINE
#define H_RENDERENGINE

#include "graphics/renderengineconfiguration.h"
#include "graphics/vertex.h"

namespace Game {

/**
 * Singleton class of main render engine of the game.
 */
class RenderEngine {
public:
    RenderEngineConfiguration config;

const std::vector<Vertex> vertices = {
    {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},

    {{-0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
    {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
    {{0.5f, 0.5f, -0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
    {{-0.5f, 0.5f, -0.5f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
};

const std::vector<uint16_t> indices = {
    0, 1, 2, 2, 3, 0,
    4, 5, 6, 6, 7, 4
};

public:
    static RenderEngine& getInstance();

private:
    RenderEngine() {};

public:
    /**
     * Initial intilization to prepare engine to work.
     */
    void initializate();

public:
    /**
     * Terminates all process to stop engine.
     */
    void terminate();

private:
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

public:
    void drawFrame();

private:
    void writeVertexBuffer();

private:
    void writeIndexBuffer();

private:
    void updateUniformBuffer();
};

} // namespace Game

#endif 