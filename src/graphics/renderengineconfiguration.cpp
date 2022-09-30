#include <set>
#include <limits>
#include <algorithm>
#include <iostream>
#include <string>

#include "graphics/renderengineconfiguration.h"

using namespace Game;

void RenderEngineConfiguration::initializate() {
    createVkInstance();
    v_windowController.createNewWindow();
    createSurface();
    choosePhysicalDevice();
    createDevice();
    createSwapchain();
}

void RenderEngineConfiguration::destroy() {

    vkDestroySwapchainKHR(v_device, v_swapchain, nullptr);
    vkDestroyDevice(v_device, nullptr);
    // TODO: add window delete function
    vkDestroySurfaceKHR(v_instance, v_surface, nullptr);
    vkDestroyInstance(v_instance, nullptr);
}

void RenderEngineConfiguration::createVkInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

    appInfo.pApplicationName = "Vulpes locis";
    appInfo.pEngineName = "Fox engine";

    appInfo.apiVersion = VK_MAKE_API_VERSION(0, 0, 0, 1);
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);


    VkInstanceCreateInfo instInfo{};
    instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instInfo.pApplicationInfo = &appInfo;

    instInfo.enabledLayerCount = 0;

    uint32_t count = 0;
    instInfo.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&count);
    instInfo.enabledExtensionCount = count;


    vkCreateInstance(&instInfo, nullptr, &v_instance);
}

void RenderEngineConfiguration::createSurface() {
    glfwCreateWindowSurface(v_instance, v_windowController.getWindow(), nullptr, &v_surface);
    
}

void RenderEngineConfiguration::choosePhysicalDevice() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(v_instance, &deviceCount, nullptr);
    std::vector<VkPhysicalDevice> allDevices(deviceCount);
    vkEnumeratePhysicalDevices(v_instance, &deviceCount, allDevices.data());

    // Looking for suitable device
    for (VkPhysicalDevice device : allDevices) {
        // Check device properties and features
        VkPhysicalDeviceProperties properties;
        VkPhysicalDeviceFeatures features;
        vkGetPhysicalDeviceProperties(device, &properties);
        vkGetPhysicalDeviceFeatures(device, &features);

        if (!((
            // Properties check
            properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU
        ) && (
            // Features check
            features.geometryShader
        ))) {
            continue;
        }
    
        // Check extensions support
        uint32_t extensionCount;
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

        std::vector<VkExtensionProperties> availableExtensions(extensionCount);
        vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

        std::set<std::string> checkingExtesnions(EXTENSIONS.begin(), EXTENSIONS.end());
        
        for (VkExtensionProperties extProperties : availableExtensions) {
            checkingExtesnions.erase(extProperties.extensionName);
        }

        if (!checkingExtesnions.empty()) {
            continue;
        }


        // Checking for required families support
        if (!chooseQueues(device)) {
            continue;
        }


        v_physicalDevice = device;
        
        break;
    }
}

bool RenderEngineConfiguration::chooseQueues(VkPhysicalDevice& device) {
    bool graphicFinded = false;
    bool presentationFinded = false;
    
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    for (uint32_t i = 0; i < queueFamilyCount; i++) {
        if (!graphicFinded && (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
            v_graphicFamilyIndex = i;
            
            graphicFinded = true;
        }
        
        VkBool32 supportPresentationCheck = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, v_surface, &supportPresentationCheck);
        
        if (!presentationFinded && supportPresentationCheck) {
            v_presentationFamilyIndex = i;

            presentationFinded = true;
        }
    }

    return (graphicFinded && presentationFinded);
        
}

void RenderEngineConfiguration::createDevice() {
    const uint32_t INFOS_COUNT = 2;
    VkDeviceQueueCreateInfo queuesCreateInfo[INFOS_COUNT]{};

    queuesCreateInfo[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queuesCreateInfo[0].queueFamilyIndex = v_graphicFamilyIndex;
    queuesCreateInfo[0].queueCount = 1;
    const float queuePriorities1[] = {1.0f};
    queuesCreateInfo[0].pQueuePriorities = queuePriorities1;

    queuesCreateInfo[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queuesCreateInfo[1].queueFamilyIndex = v_presentationFamilyIndex;
    queuesCreateInfo[1].queueCount = 1;
    const float queuePriorities2[] = {1.0f};
    queuesCreateInfo[1].pQueuePriorities = queuePriorities2;

    VkPhysicalDeviceFeatures deviceFeatures{};

    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos = queuesCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = INFOS_COUNT;
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
    deviceCreateInfo.ppEnabledExtensionNames = EXTENSIONS.data();
    deviceCreateInfo.enabledExtensionCount = EXTENSIONS.size();
    deviceCreateInfo.enabledLayerCount = 0;

    vkCreateDevice(v_physicalDevice, &deviceCreateInfo, nullptr, &v_device);
}

void RenderEngineConfiguration::createQueuesObjects() {
    vkGetDeviceQueue(v_device, v_graphicFamilyIndex, 0, &v_graphicsQueue);
    vkGetDeviceQueue(v_device, v_presentationFamilyIndex, 0, &v_presentQueue);
}

void RenderEngineConfiguration::createSwapchain() {
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(v_physicalDevice, v_surface, &capabilities);

    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(v_physicalDevice, v_surface, &formatCount, nullptr);
    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(v_physicalDevice, v_surface, &formatCount, formats.data());


    VkSwapchainCreateInfoKHR swapchainCreateInfo{};
    swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainCreateInfo.surface = v_surface;
    swapchainCreateInfo.imageArrayLayers = 1;
    swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchainCreateInfo.preTransform = capabilities.currentTransform;
    swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchainCreateInfo.clipped = VK_TRUE;
    swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

    // Choosing image count
    swapchainCreateInfo.minImageCount = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount > 0 && swapchainCreateInfo.minImageCount > capabilities.maxImageCount) {
        swapchainCreateInfo.minImageCount = capabilities.maxImageCount;
    }

    // Choosing format
    swapchainCreateInfo.imageFormat = formats[0].format;
    swapchainCreateInfo.imageColorSpace = formats[0].colorSpace;
    v_swapchainFormat = formats[0].format;

    // Choosing presentation mode
    swapchainCreateInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;

    // Choosing extent
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        swapchainCreateInfo.imageExtent = capabilities.currentExtent;
    } else {
        int width, height;
        glfwGetFramebufferSize(v_windowController.getWindow(), &width, &height);

        VkExtent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        swapchainCreateInfo.imageExtent = actualExtent;
    }

    v_swapchainExtent = swapchainCreateInfo.imageExtent;

    // Queues setup
    uint32_t queueFamilyIndices[] = {v_graphicFamilyIndex, v_presentationFamilyIndex};

    if (v_graphicFamilyIndex != v_presentationFamilyIndex) {
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapchainCreateInfo.queueFamilyIndexCount = 2;
        swapchainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfo.queueFamilyIndexCount = 0;
        swapchainCreateInfo.pQueueFamilyIndices = nullptr;
    }

    vkCreateSwapchainKHR(v_device, &swapchainCreateInfo, nullptr, &v_swapchain);
}


