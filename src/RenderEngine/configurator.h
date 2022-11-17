#ifndef H_RENDERENGINE_CONFIGURATOR
#define H_RENDERENGINE_CONFIGURATOR

#include "rendersettings.h"
#include "deviceinfo.h"

#include <vector>

namespace RenderEngine {

/**
 * Configurator namespace contains tools for changing 
 * state of lib like changing settings of rendering.
 */
namespace Configurator {

/**
 * Initialization of components that needed for work
 * of library all of the time.
 */
void initializate ();

/**
 * Initializates rendering.
 * 
 * @param settings Settings by which the class will be configured.
 */
void configurateRender(RenderSettings& settings);

std::vector<DeviceInfo> getAvailableDevices();

}

}

#endif