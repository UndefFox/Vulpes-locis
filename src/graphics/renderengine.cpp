#include "graphics/renderengine.h"

#include <iostream>
#include <cstring>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

#include "graphics/ubo.h"
#include "graphics/objectConstant.h"
#include "world.h"

using namespace Game;

RenderEngine& RenderEngine::getInstance() {
    static RenderEngine instance;

    return instance;
}

void RenderEngine::initializate() {
    configurator.initializate();

    writeVertexBuffer();
    writeIndexBuffer();
}

void RenderEngine::terminate() {
    configurator.destroy();

    glfwTerminate();
}

void RenderEngine::drawFrame() {
    vkWaitForFences(configurator.logicalDevice, 1, &configurator.inFlightFence, VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(configurator.logicalDevice, configurator.swapchainKHR, UINT64_MAX, configurator.imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        configurator.recreateSwapchain();
        return;
    }

    vkResetFences(configurator.logicalDevice, 1, &configurator.inFlightFence);

    vkResetCommandBuffer(configurator.commandBuffer, 0);

    recordCommandBuffer(configurator.commandBuffer, imageIndex);

    updateUniformBuffer();

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {configurator.imageAvailableSemaphore};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &configurator.commandBuffer;

    VkSemaphore signalSemaphores[] = {configurator.renderFinishedSemaphore};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkQueueSubmit(configurator.graphicsQueue, 1, &submitInfo, configurator.inFlightFence);

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {configurator.swapchainKHR};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(configurator.v_presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
        configurator.recreateSwapchain();
    }
}

void RenderEngine::recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = configurator.renderPass;
    renderPassInfo.framebuffer = configurator.swapchainFramebuffers[imageIndex];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent = configurator.swapchainExtent;

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassInfo.clearValueCount = clearValues.size();
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, configurator.graphicsPipeline);

    VkBuffer vertexBuffers[] = {configurator.vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

    vkCmdBindIndexBuffer(commandBuffer, configurator.indexBuffer, 0, VK_INDEX_TYPE_UINT16);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(configurator.swapchainExtent.width);
    viewport.height = static_cast<float>(configurator.swapchainExtent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent = configurator.swapchainExtent;
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, configurator.pipelineLayout, 0, 1, &configurator.descriptorSet, 0, nullptr);

    for (Object obj : World::getInstance().objects) {

        ObjectConstant constant;
        constant.pos.x = obj.position[0];
        constant.pos.y = obj.position[1];
        constant.pos.z = obj.position[2];

        vkCmdPushConstants(commandBuffer, configurator.pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(constant), &constant);
        vkCmdDrawIndexed(commandBuffer, static_cast<uint32_t>(indices.size()), 1, 0, 0, 0);

    }


    vkCmdEndRenderPass(commandBuffer);

    vkEndCommandBuffer(commandBuffer);
}

void RenderEngine::writeVertexBuffer() {
    VkDeviceSize bufferSize = sizeof(Vertex) * vertices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    configurator.createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(configurator.logicalDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
        memcpy(data, vertices.data(), (size_t) bufferSize);
    vkUnmapMemory(configurator.logicalDevice, stagingBufferMemory);

    configurator.copyBuffer(stagingBuffer, configurator.vertexBuffer, bufferSize);

    vkDestroyBuffer(configurator.logicalDevice, stagingBuffer, nullptr);
    vkFreeMemory(configurator.logicalDevice, stagingBufferMemory, nullptr);
}

void RenderEngine::writeIndexBuffer() {
    VkDeviceSize bufferSize = sizeof(uint16_t) * indices.size();

    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;
    configurator.createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

    void* data;
    vkMapMemory(configurator.logicalDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
    memcpy(data, indices.data(), (size_t) bufferSize);
    vkUnmapMemory(configurator.logicalDevice, stagingBufferMemory);

    configurator.copyBuffer(stagingBuffer, configurator.indexBuffer, bufferSize);

    vkDestroyBuffer(configurator.logicalDevice, stagingBuffer, nullptr);
    vkFreeMemory(configurator.logicalDevice, stagingBufferMemory, nullptr);
}

void RenderEngine::updateUniformBuffer() {
    static auto startTime = std::chrono::high_resolution_clock::now();

    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();

    UniformBufferObject ubo{};
    ubo.model = glm::rotate(glm::mat4(1.0f), time * glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    ubo.proj = glm::perspective(glm::radians(45.0f), configurator.swapchainExtent.width / (float) configurator.swapchainExtent.height, 0.1f, 10.0f);
    ubo.proj[1][1] *= -1;

    World::getInstance().objects[0].position[2] += 0.001;

    void* data;
    vkMapMemory(configurator.logicalDevice, configurator.uniformBufferMemory, 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(configurator.logicalDevice, configurator.uniformBufferMemory);
}
