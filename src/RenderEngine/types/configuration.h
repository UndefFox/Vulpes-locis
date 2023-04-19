#ifndef RENDERENGINE_CONFIGURATION_H
#define RENDERENGINE_CONFIGURATION_H

#include <GLFW/glfw3.h>
#include <string>

namespace RenderEngine {

struct Configuration {
    /**
     * Window where render result will be displayed.
     */
    GLFWwindow* window;

    /**
     * Id of device that must be used for rendering.
     */
    int deviceId;

    
    size_t memoryAmount;

    /**
     * Data of vertices spv shader file.
     */
    std::vector<char> verticesShaderCode;

    /**
     * Data of fragment spv shader file.
     */
    std::vector<char> fragmentShaderCode;
};

}

#endif