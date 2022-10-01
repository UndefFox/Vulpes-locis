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
    getQueuesObjects();
    createSwapchain();
    getSwapchainImages();
    createImagesViews();
    createRenderPass();
    createGraphicsPipeline();
    createFramebuffers();
    createCommandPool();
    createCommandBuffer();
    createSyncObjects();
}

void RenderEngineConfiguration::destroy() {
    vkDestroySemaphore(v_device, imageAvailableSemaphore, nullptr);
    vkDestroySemaphore(v_device, renderFinishedSemaphore, nullptr);
    vkDestroyFence(v_device, inFlightFence, nullptr);

    vkDestroyCommandPool(v_device, v_commandPool, nullptr);
    for (auto framebuffer : v_swapchainFramebuffers) {
        vkDestroyFramebuffer(v_device, framebuffer, nullptr);
    }
    vkDestroyPipelineLayout(v_device, v_pipelineLayout, nullptr);
    vkDestroyRenderPass(v_device, v_renderPass, nullptr);
    for (VkImageView imageView : v_swapchainImageViews) {
        vkDestroyImageView(v_device, imageView, nullptr);
    }

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

void RenderEngineConfiguration::getQueuesObjects() {
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

void RenderEngineConfiguration::getSwapchainImages() {
    uint32_t imageCount = 0;
    vkGetSwapchainImagesKHR(v_device, v_swapchain, &imageCount, nullptr);
    v_swapchainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(v_device, v_swapchain, &imageCount, v_swapchainImages.data());
}

void RenderEngineConfiguration::createImagesViews() {
    v_swapchainImageViews.resize(v_swapchainImages.size());

    VkImageViewCreateInfo viewCreateInfo{};
    viewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    viewCreateInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    viewCreateInfo.format = v_swapchainFormat;
    viewCreateInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewCreateInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewCreateInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewCreateInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    viewCreateInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    viewCreateInfo.subresourceRange.baseMipLevel = 0;
    viewCreateInfo.subresourceRange.levelCount = 1;
    viewCreateInfo.subresourceRange.baseArrayLayer = 0;
    viewCreateInfo.subresourceRange.layerCount = 1;

    for (uint32_t i = 0; i < v_swapchainImages.size(); i++) {
        viewCreateInfo.image = v_swapchainImages[i];

        vkCreateImageView(v_device, &viewCreateInfo, nullptr, &v_swapchainImageViews[i]);
    }

}

void RenderEngineConfiguration::createRenderPass() {
    VkAttachmentDescription colorAttachment{};
    colorAttachment.format = v_swapchainFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef{};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass{};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkSubpassDependency dependency{};
    dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    dependency.dstSubpass = 0;
    dependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.srcAccessMask = 0;
    dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

    VkRenderPassCreateInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &dependency;

    vkCreateRenderPass(v_device, &renderPassInfo, nullptr, &v_renderPass);
}

void RenderEngineConfiguration::createGraphicsPipeline() {
    std::vector<char> vertShader;
    std::vector<char> fragShader;

    FileManager::loadShaderFile(FILE_NAME_VERT_SHADER, vertShader);
    FileManager::loadShaderFile(FILE_NAME_FRAG_SHADER, fragShader);

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
    vertexInputInfo.vertexBindingDescriptionCount = 0;
    vertexInputInfo.vertexAttributeDescriptionCount = 0;

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
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
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

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pushConstantRangeCount = 0;

    vkCreatePipelineLayout(v_device, &pipelineLayoutInfo, nullptr, &v_pipelineLayout);

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
    pipelineInfo.layout = v_pipelineLayout;
    pipelineInfo.renderPass = v_renderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;

    vkCreateGraphicsPipelines(v_device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &v_graphicsPipeline);

    vkDestroyShaderModule(v_device, vertModule, nullptr);
    vkDestroyShaderModule(v_device, fragModule, nullptr);
}

void RenderEngineConfiguration::createShaderModule(const std::vector<char>& code, VkShaderModule& shaderModule) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    vkCreateShaderModule(v_device, &createInfo, nullptr, &shaderModule);
}

void RenderEngineConfiguration::createFramebuffers() {
    v_swapchainFramebuffers.resize(v_swapchainImageViews.size());

    for (size_t i = 0; i < v_swapchainImageViews.size(); i++) {
        VkImageView attachments[] = {
            v_swapchainImageViews[i]
        };

        VkFramebufferCreateInfo framebufferInfo{};
        framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
        framebufferInfo.renderPass = v_renderPass;
        framebufferInfo.attachmentCount = 1;
        framebufferInfo.pAttachments = attachments;
        framebufferInfo.width = v_swapchainExtent.width;
        framebufferInfo.height = v_swapchainExtent.height;
        framebufferInfo.layers = 1;

        vkCreateFramebuffer(v_device, &framebufferInfo, nullptr, &v_swapchainFramebuffers[i]);
    }
}

void RenderEngineConfiguration::createCommandPool() {
    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    poolInfo.queueFamilyIndex = v_graphicFamilyIndex;

    vkCreateCommandPool(v_device, &poolInfo, nullptr, &v_commandPool);
}

void RenderEngineConfiguration::createCommandBuffer() {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = v_commandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    vkAllocateCommandBuffers(v_device, &allocInfo, &v_commandBuffer);
}

void RenderEngineConfiguration::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = v_renderPass;
    renderPassInfo.framebuffer = v_swapchainFramebuffers[imageIndex];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = v_swapchainExtent;

    VkClearValue clearColor = {{{0.0f, 0.0f, 0.0f, 1.0f}}};
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, v_graphicsPipeline);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(v_swapchainExtent.width);
    viewport.height = static_cast<float>(v_swapchainExtent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = v_swapchainExtent;
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    vkCmdDraw(commandBuffer, 3, 1, 0, 0);

    vkCmdEndRenderPass(commandBuffer);

    vkEndCommandBuffer(commandBuffer);
}

void RenderEngineConfiguration::createSyncObjects() {
    VkSemaphoreCreateInfo semaphoreInfo{};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo{};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    vkCreateSemaphore(v_device, &semaphoreInfo, nullptr, &imageAvailableSemaphore);
    vkCreateSemaphore(v_device, &semaphoreInfo, nullptr, &renderFinishedSemaphore);
    vkCreateFence(v_device, &fenceInfo, nullptr, &inFlightFence);
}









