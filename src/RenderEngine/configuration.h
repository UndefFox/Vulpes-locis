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


    /**
     * Path to vertices spv shader file.
     */
    std::string verticesShaderPath;

    /**
     * Path to fragment spv shader file.
     */
    std::string fragmentShaderPath;
};

}

#endif