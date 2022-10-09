#ifndef H_RENDERENGINE
#define H_RENDERENGINE

#include "graphics/renderconfigurator.h"
#include "graphics/vertex.h"

namespace Game {

/**
 * Singleton class of main render engine of the game.
 */
class RenderEngine {
public:
    RenderConfigurator configurator;

private:
    const std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
        {{0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
        {{0.5f, 0.5f, 0.0f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
        {{-0.5f, 0.5f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
    };

    const std::vector<uint16_t> indices = {
        0, 1, 2, 2, 3, 0
    };

public:
    /**
     * Return instance of RenderEngine instance.
     */
    static RenderEngine& getInstance();

private:
    RenderEngine(){};

public:
    /**
     * Initial intilization to prepare engine to work.
     * 
     * Must be called before any rendering.
     */
    void initializate();

public:
    /**
     * Terminates all process to stop engine.
     */
    void terminate();

    /**
     * Draw frame.
     */
public:
    void drawFrame();

private:
    void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex);

private:
    void writeVertexBuffer();

private:
    void writeIndexBuffer();

private:
    void updateUniformBuffer();
};

} // namespace Game

#endif 