#include "valuesfactory.h"

#include <set>
#include <algorithm>
#include <limits>
#include <array>

#include "image.h"
#include "vertex.h"
#include "memory.h"
#include "ubo.h"
#include "io.h"
#include "objectConstant.h"

namespace RenderEngine {

namespace {

bool chooseQueues(VkPhysicalDevice& device, VkSurfaceKHR testSurface = surfaceKHR) {
    bool graphicFinded = false;
    bool presentationFinded = false;

    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

    std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

    for (uint32_t i = 0; i < queueFamilyCount; i++) {
        if (!graphicFinded && (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)) {
            graphicFamilyIndex = i;

            graphicFinded = true;
        }

        VkBool32 supportPresentationCheck = false;
        vkGetPhysicalDeviceSurfaceSupportKHR(device, i, testSurface, &supportPresentationCheck);

        if (!presentationFinded && supportPresentationCheck) {
            presentationFamilyIndex = i;

            presentationFinded = true;
        }
    }

    return (graphicFinded && presentationFinded);

}

void createShaderModule(const std::vector<char>& code, VkShaderModule& shaderModule) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    vkCreateShaderModule(logicalDevice, &createInfo, nullptr, &shaderModule);
}

} // namespace <anonymous>


void createVulkanInstance() {
    VkApplicationInfo appInfo{};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

    appInfo.pApplicationName = "Vulpes locis";
    appInfo.pEngineName = "Fox engine";

    appInfo.apiVersion = VK_API_VERSION_1_3;
    appInfo.applicationVersion = VK_MAKE_VERSION(0, 0, 1);
    appInfo.engineVersion = VK_MAKE_VERSION(0, 0, 1);


    VkInstanceCreateInfo instInfo{};
    instInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instInfo.pApplicationInfo = &appInfo;

    instInfo.enabledLayerCount = 0;

    uint32_t count = 0;
    instInfo.ppEnabledExtensionNames = glfwGetRequiredInstanceExtensions(&count);
    instInfo.enabledExtensionCount = count;


    vkCreateInstance(&instInfo, nullptr, &vulkanInstance);
}

void destroyVulkanInstance() {
    vkDestroyInstance(vulkanInstance, nullptr);
}


void createSurface() {
    glfwCreateWindowSurface(vulkanInstance, window, nullptr, &surfaceKHR);
}

void destroySurface() {
    vkDestroySurfaceKHR(vulkanInstance, surfaceKHR, nullptr);
}


std::vector<VkPhysicalDevice> getAvailablePhysicalDevices() {
    uint32_t deviceCount = 0;
    vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, nullptr);
    std::vector<VkPhysicalDevice> physicalDevices(deviceCount);
    vkEnumeratePhysicalDevices(vulkanInstance, &deviceCount, physicalDevices.data());

    return physicalDevices;
}

bool minimuPhysicalDeviceCheck(VkPhysicalDevice& device, VkSurfaceKHR testSurface) {
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
        features.geometryShader &&
        features.samplerAnisotropy
    ))) {
        return false;
    }

    // Check extensions support
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> checkingExtesnions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    for (VkExtensionProperties extProperties : availableExtensions) {
        checkingExtesnions.erase(extProperties.extensionName);
    }

    if (!checkingExtesnions.empty()) {
        return false;
    }


    // Checking for required families support
    if (!chooseQueues(device, testSurface)) {
        return false;
    }

    return true;
}


void setPhysicalDevice(uint32_t deviceId) {
    for (VkPhysicalDevice device : getAvailablePhysicalDevices()) {
        VkPhysicalDeviceProperties properties{};
        vkGetPhysicalDeviceProperties(device, &properties);

        if (deviceId == properties.deviceID) {
            physcialDevice = device;
        }
    }
}


void createDevice() {
    const uint32_t INFOS_COUNT = 1;
    VkDeviceQueueCreateInfo queuesCreateInfo[INFOS_COUNT]{};
    chooseQueues(physcialDevice);

    queuesCreateInfo[0].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queuesCreateInfo[0].queueFamilyIndex = graphicFamilyIndex;
    queuesCreateInfo[0].queueCount = 2;
    const float queuePriorities1[] = {1.0f, 1.0f};
    queuesCreateInfo[0].pQueuePriorities = queuePriorities1;

    // TODO: update create device func so queueCreateInfo want have same graphicFamilyIndex

    // queuesCreateInfo[1].sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    // queuesCreateInfo[1].queueFamilyIndex = presentationFamilyIndex;
    // queuesCreateInfo[1].queueCount = 1;
    // const float queuePriorities2[] = {1.0f};
    // queuesCreateInfo[1].pQueuePriorities = queuePriorities2;

    VkPhysicalDeviceFeatures deviceFeatures{};
    deviceFeatures.samplerAnisotropy = VK_TRUE;

    const std::vector<const char*> requiredDeviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME
    };

    VkDeviceCreateInfo deviceCreateInfo{};
    deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    deviceCreateInfo.pQueueCreateInfos = queuesCreateInfo;
    deviceCreateInfo.queueCreateInfoCount = INFOS_COUNT;
    deviceCreateInfo.pEnabledFeatures = &deviceFeatures;
    deviceCreateInfo.ppEnabledExtensionNames = requiredDeviceExtensions.data();
    deviceCreateInfo.enabledExtensionCount = requiredDeviceExtensions.size();
    deviceCreateInfo.enabledLayerCount = 0;

    
    vkCreateDevice(physcialDevice, &deviceCreateInfo, nullptr, &logicalDevice);

    vkGetDeviceQueue(logicalDevice, graphicFamilyIndex, 0, &graphicsQueue);
    vkGetDeviceQueue(logicalDevice, presentationFamilyIndex, 1, &presentQueue);
}

void destroyDevice() {
    vkDestroyDevice(logicalDevice, nullptr);
}


void updateSwapchainConfiguration() {
    
    // Choosing format
    uint32_t formatCount;
    vkGetPhysicalDeviceSurfaceFormatsKHR(physcialDevice, surfaceKHR, &formatCount, nullptr);
    std::vector<VkSurfaceFormatKHR> formats(formatCount);
    vkGetPhysicalDeviceSurfaceFormatsKHR(physcialDevice, surfaceKHR, &formatCount, formats.data());

    swapchainFormat = formats[0];
}


void createSwapchain() {
    VkSurfaceCapabilitiesKHR capabilities;
    vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physcialDevice, surfaceKHR, &capabilities);

    VkSwapchainCreateInfoKHR swapchainCreateInfo{};
    swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    swapchainCreateInfo.surface = surfaceKHR;
    swapchainCreateInfo.imageArrayLayers = 1;
    swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
    swapchainCreateInfo.preTransform = capabilities.currentTransform;
    swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    swapchainCreateInfo.clipped = VK_TRUE;
    swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;
    swapchainCreateInfo.imageFormat = swapchainFormat.format;
    swapchainCreateInfo.imageColorSpace = swapchainFormat.colorSpace;

    // Choosing image count
    swapchainCreateInfo.minImageCount = capabilities.minImageCount + 1;
    if (capabilities.maxImageCount > 0 && swapchainCreateInfo.minImageCount > capabilities.maxImageCount) {
        swapchainCreateInfo.minImageCount = capabilities.maxImageCount;
    }

    // Choosing presentation mode
    swapchainCreateInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;

    // Choosing extent
    if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
        swapchainCreateInfo.imageExtent = capabilities.currentExtent;
    } else {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        VkExtent2D actualExtent = {
            static_cast<uint32_t>(width),
            static_cast<uint32_t>(height)
        };

        actualExtent.width = std::clamp(actualExtent.width, capabilities.minImageExtent.width, capabilities.maxImageExtent.width);
        actualExtent.height = std::clamp(actualExtent.height, capabilities.minImageExtent.height, capabilities.maxImageExtent.height);

        swapchainCreateInfo.imageExtent = actualExtent;
    }

    swapchainExtent = swapchainCreateInfo.imageExtent;

    // Queues setup
    uint32_t queueFamilyIndices[] = {graphicFamilyIndex, presentationFamilyIndex};

    if (graphicFamilyIndex != presentationFamilyIndex) {
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        swapchainCreateInfo.queueFamilyIndexCount = 2;
        swapchainCreateInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfo.queueFamilyIndexCount = 0;
        swapchainCreateInfo.pQueueFamilyIndices = nullptr;
    }

    vkCreateSwapchainKHR(logicalDevice, &swapchainCreateInfo, nullptr, &swapchainKHR);

    uint32_t imageCount = 0;
    vkGetSwapchainImagesKHR(logicalDevice, swapchainKHR, &imageCount, nullptr);
    swapchainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(logicalDevice, swapchainKHR, &imageCount, swapchainImages.data());

    swapchainImageViews.resize(swapchainImages.size());

    for (uint32_t i = 0; i < swapchainImages.size(); i++) {
        swapchainImageViews[i] = createImageView(swapchainImages[i], swapchainFormat.format, VK_IMAGE_ASPECT_COLOR_BIT);
    }
}

void destroySwapchain() {

    for (VkFramebuffer framebuffer : swapchainFramebuffers) {
        vkDestroyFramebuffer(logicalDevice, framebuffer, nullptr);
    }
    for (VkImageView imageview : swapchainImageViews) {
        vkDestroyImageView(logicalDevice, imageview, nullptr);
    }

    vkDestroySwapchainKHR(logicalDevice, swapchainKHR, nullptr);
}

void createFramebuffers() {
    swapchainFramebuffers.resize(swapchainImageViews.size());

    for (size_t i = 0; i < swapchainImageViews.size(); i++) {
        std::array<VkImageView, 2> attachments = {
            swapchainImageViews[i],
            depthImageView
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = renderPass;
        framebufferInfo.attachmentCount = attachments.size();
        framebufferInfo.pAttachments = attachments.data();
        framebufferInfo.width = swapchainExtent.width;
        framebufferInfo.height = swapchainExtent.height;
        framebufferInfo.layers = 1;

        vkCreateFramebuffer(logicalDevice, &framebufferInfo, nullptr, &swapchainFramebuffers[i]);
    }
}


void createRenderPass() {
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = swapchainFormat.format;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentDescription depthAttachment{};
    depthAttachment.format = findSupportedFormat(
        {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
    );
    depthAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    depthAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    depthAttachment.storeOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    depthAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    depthAttachment.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkAttachmentReference depthAttachmentRef{};
    depthAttachmentRef.attachment = 1;
    depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;
    subpass.pDepthStencilAttachment = &depthAttachmentRef;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcAccessMask = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;


    std::array<VkAttachmentDescription, 2> attachments = {colorAttachment, depthAttachment};
    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = attachments.size();
    renderPassInfo.pAttachments = attachments.data();
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;

    vkCreateRenderPass(logicalDevice, &renderPassInfo, nullptr, &renderPass);
}

void destroyRenderPass() {
    vkDestroyRenderPass(logicalDevice, renderPass, nullptr);
}


void createDescriptorSetLayout() {
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
    uboLayoutBinding.pImmutableSamplers = nullptr;

    std::array<VkDescriptorSetLayoutBinding, 1> bindings = {uboLayoutBinding};

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = bindings.size();
    layoutInfo.pBindings = bindings.data();

    vkCreateDescriptorSetLayout(logicalDevice, &layoutInfo, nullptr, &descriptorSetLayout);
}


void createGraphicsPipelineLayout() {
    VkPushConstantRange constans;
    constans.offset = 0;
    constans.size = sizeof(ObjectConstant);
    constans.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 1;
    pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout;
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &constans;


    vkCreatePipelineLayout(logicalDevice, &pipelineLayoutInfo, nullptr, &pipelineLayout);
}

void destroyGraphicsPipelineLayout() {
    vkDestroyPipelineLayout(logicalDevice, pipelineLayout, nullptr);
}


void createGraphicsPipeline(std::string vertexShader, std::string fragmentShader) {
    std::vector<char> vertShader;
    std::vector<char> fragShader;

    loadShaderFile(vertexShader, vertShader);
    loadShaderFile(fragmentShader, fragShader);

    VkShaderModule vertModule{};
    VkShaderModule fragModule{};

    createShaderModule(vertShader, vertModule);
    createShaderModule(fragShader, fragModule);

    VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
    vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageInfo.module = vertModule;
    vertShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
    fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageInfo.module = fragModule;
    fragShaderStageInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageInfo, fragShaderStageInfo};

    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

    VkVertexInputBindingDescription bindingDescription{};
    bindingDescription.binding = 0;
    bindingDescription.stride = sizeof(Vertex);
    bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

    std::array<VkVertexInputAttributeDescription, 3> attributeDescriptions{};

    attributeDescriptions[0].binding = 0;
    attributeDescriptions[0].location = 0;
    attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[0].offset = offsetof(Vertex, Vertex::pos);

    attributeDescriptions[1].binding = 0;
    attributeDescriptions[1].location = 1;
    attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
    attributeDescriptions[1].offset = offsetof(Vertex, Vertex::normal);

    attributeDescriptions[2].binding = 0;
    attributeDescriptions[2].location = 2;
    attributeDescriptions[2].format = VK_FORMAT_R32G32_SFLOAT;
    attributeDescriptions[2].offset = offsetof(Vertex, Vertex::texCoord);


    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.pVertexBindingDescriptions = &bindingDescription;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size());
    vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkPipelineViewportStateCreateInfo viewportState{};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.scissorCount = 1;

    VkPipelineRasterizationStateCreateInfo rasterizer{};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multisampling{};
    multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multisampling.sampleShadingEnable = VK_FALSE;
    multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachment{};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_FALSE;

    VkPipelineColorBlendStateCreateInfo colorBlending{};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    std::vector<VkDynamicState> dynamicStates = {
        VK_DYNAMIC_STATE_VIEWPORT,
        VK_DYNAMIC_STATE_SCISSOR
    };

    VkPipelineDynamicStateCreateInfo dynamicState{};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
    dynamicState.pDynamicStates = dynamicStates.data();

    VkPipelineDepthStencilStateCreateInfo depthStencil{};
    depthStencil.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencil.depthTestEnable = VK_TRUE;
    depthStencil.depthWriteEnable = VK_TRUE;
    depthStencil.depthCompareOp = VK_COMPARE_OP_LESS;
    depthStencil.depthBoundsTestEnable = VK_FALSE;
    depthStencil.stencilTestEnable = VK_FALSE;

    VkGraphicsPipelineCreateInfo pipelineInfo{};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multisampling;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = &dynamicState;
    pipelineInfo.pDepthStencilState = &depthStencil;
    pipelineInfo.layout = pipelineLayout;
    pipelineInfo.renderPass = renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    vkCreateGraphicsPipelines(logicalDevice, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &graphicsPipeline);

    vkDestroyShaderModule(logicalDevice, vertModule, nullptr);
    vkDestroyShaderModule(logicalDevice, fragModule, nullptr);
}

void destroyGraphicsPipeline() {
    vkDestroyPipeline(logicalDevice, graphicsPipeline, nullptr);
}


void createCommandPool() {
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = graphicFamilyIndex;

    vkCreateCommandPool(logicalDevice, &poolInfo, nullptr, &commandPool);
}

void destroyCommandPool() {
    vkDestroyCommandPool(logicalDevice, commandPool, nullptr);
}


void createCommandBuffer() {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    vkAllocateCommandBuffers(logicalDevice, &allocInfo, &commandBuffer);
}


void createDepthResources() {
    VkFormat depthFormat = findSupportedFormat(
        {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT},
        VK_IMAGE_TILING_OPTIMAL,
        VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
    );

    createImage(swapchainExtent.width, swapchainExtent.height, depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, depthImage, depthImageMemory);
    depthImageView = createImageView(depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT);

    transitionImageLayout(depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

void destroyDepthResources() {
    vkDestroyImageView(logicalDevice, depthImageView, nullptr);
    vkDestroyImage(logicalDevice, depthImage, nullptr);
    vkFreeMemory(logicalDevice, depthImageMemory, nullptr);
}


void createBuffers() {
    VkDeviceSize bufferSize;

    bufferSize = sizeof(Vertex) * 100000;
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

    bufferSize = sizeof(uint16_t) * 100000;
    createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

    bufferSize = sizeof(UniformBufferObject);
    createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffer, uniformBufferMemory);

}

void destroyBuffers() {
    vkDestroyBuffer(logicalDevice, vertexBuffer, nullptr);
    vkFreeMemory(logicalDevice, vertexBufferMemory, nullptr);

    vkDestroyBuffer(logicalDevice, indexBuffer, nullptr);
    vkFreeMemory(logicalDevice, indexBufferMemory, nullptr);

    vkDestroyBuffer(logicalDevice, uniformBuffer, nullptr);
    vkFreeMemory(logicalDevice, uniformBufferMemory, nullptr);
}


void createDescriptorPool() {
    std::array<VkDescriptorPoolSize, 1> poolSizes{};
    poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    poolSizes[0].descriptorCount = 1;

    VkDescriptorPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    poolInfo.poolSizeCount = poolSizes.size();
    poolInfo.pPoolSizes = poolSizes.data();
    poolInfo.maxSets = 3;

    vkCreateDescriptorPool(logicalDevice, &poolInfo, nullptr, &descriptorPool);
}

void destroyDesriptorPool() {
    vkDestroyDescriptorPool(logicalDevice, descriptorPool, nullptr);
}


void createDescriptorSet() {
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = descriptorPool;
    allocInfo.descriptorSetCount = 1;
    allocInfo.pSetLayouts = &descriptorSetLayout;

    vkAllocateDescriptorSets(logicalDevice, &allocInfo, &descriptorSet);

    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = uniformBuffer;
    bufferInfo.offset = 0;
    bufferInfo.range = sizeof(UniformBufferObject);

    std::array<VkWriteDescriptorSet, 1> descriptorWrites{};

    descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrites[0].dstSet = descriptorSet;
    descriptorWrites[0].dstBinding = 0;
    descriptorWrites[0].dstArrayElement = 0;
    descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrites[0].descriptorCount = 1;
    descriptorWrites[0].pBufferInfo = &bufferInfo;

    vkUpdateDescriptorSets(logicalDevice, descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);
}


void createSyncObjects() {
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    vkCreateSemaphore(logicalDevice, &semaphoreInfo, nullptr, &imageAvailableSemaphore);
    vkCreateSemaphore(logicalDevice, &semaphoreInfo, nullptr, &renderFinishedSemaphore);
    vkCreateFence(logicalDevice, &fenceInfo, nullptr, &inFlightFence);
}

void destroySyncObjects() {
    vkDestroyFence(logicalDevice, inFlightFence, nullptr);
    vkDestroySemaphore(logicalDevice, renderFinishedSemaphore, nullptr);
    vkDestroySemaphore(logicalDevice, imageAvailableSemaphore, nullptr);
}

} // namespace RenderEngine