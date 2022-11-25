#ifndef H_RENDERENGINE_RENDERENGINE
#define H_RENDERENGINE_RENDERENGINE

#include <vector>
#include <array>
#include <string>


/** 
 * 
 * \file renderengine.h
 * 
 * RenderEngine lib providing everything needed for rendering. Work model:
 * all objects saved in memory by addObject() function.
 * Then rendering them passing id of mesh to render with dynamic data of it like position,
 * rotation, texture and etc.
 */
namespace RenderEngine {

struct RenderSettings {
    /**
     * Id of the device that must be used for render.
     */
    uint32_t deviceId;

    std::string vertexShaderFile;
    std::string fragmentShaderFile;
};

struct DeviceInfo {
    uint32_t deviceId;
    std::string deviceName;
};

struct Mesh {
    std::vector<std::array<float, 3>> vertices;
    std::vector<uint16_t> indexes;

};

/**
 * Innitializing all components of library for work. Must be run 
 * before anything else.
 */
void initializate();

/**
 * Terminating all components and freeing all resources memory.
 */
void terminate();


/**
 * Draws a new frame and displaying it on window.
 */
void drawFrame(std::vector<int> IDs, std::vector<std::array<float, 3>> dynamic);


/**
 * Configuring rendder acording to settings. 
 */
void configurateRender(RenderSettings& settings);

std::vector<DeviceInfo> getAvailableDevices();

/**
 * Adding mesh to memory and returnng it's ID.
 * 
 * \param mesh 
 * sees drawFrame() wich will be added to memory.
 * 
 * \returns ID wich associeted with this object.
 */
int addObject(Mesh mesh);

}

#endif