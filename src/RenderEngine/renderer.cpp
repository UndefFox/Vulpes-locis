#include "renderer.h"

#include "src/values.h"
#include "src/valuesfactory.h"
#include "src/ubo.h"
#include "src/objectConstant.h"

#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>

namespace RenderEngine {

namespace {

void recordCommandBuffer(VkCommandBuffer commandBuffer, uint32_t imageIndex, std::vector<int> IDs, std::vector<std::array<float, 3>> dinamic) {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;

    vkBeginCommandBuffer(commandBuffer, &beginInfo);

    VkRenderPassBeginInfo renderPassInfo{};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass =   renderPass;
    renderPassInfo.framebuffer =   swapchainFramebuffers[imageIndex];
    renderPassInfo.renderArea.offset = {0, 0};
    renderPassInfo.renderArea.extent =   swapchainExtent;

    std::array<VkClearValue, 2> clearValues{};
    clearValues[0].color = {{0.0f, 0.0f, 0.0f, 1.0f}};
    clearValues[1].depthStencil = {1.0f, 0};
    renderPassInfo.clearValueCount = clearValues.size();
    renderPassInfo.pClearValues = clearValues.data();

    vkCmdBeginRenderPass(commandBuffer, &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

    vkCmdBindPipeline(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,   graphicsPipeline);

    VkBuffer vertexBuffers[] = {  vertexBuffer};
    VkDeviceSize offsets[] = {0};
    vkCmdBindVertexBuffers(commandBuffer, 0, 1, vertexBuffers, offsets);

    vkCmdBindIndexBuffer(commandBuffer,  indexBuffer, 0, VK_INDEX_TYPE_UINT16);

    VkViewport viewport{};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = static_cast<float>(  swapchainExtent.width);
    viewport.height = static_cast<float>(  swapchainExtent.height);
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;
    vkCmdSetViewport(commandBuffer, 0, 1, &viewport);

    VkRect2D scissor{};
    scissor.offset = {0, 0};
    scissor.extent =   swapchainExtent;
    vkCmdSetScissor(commandBuffer, 0, 1, &scissor);

    vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS,   pipelineLayout, 0, 1, &  descriptorSet, 0, nullptr);

    ObjectConstant constant{};
    for (int i = 0; i < IDs.size(); i++) {
        constant.pos = {dinamic[i][0], dinamic[i][1], dinamic[i][2]};

        vkCmdPushConstants(commandBuffer, pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(constant), &constant);
        
        vkCmdDrawIndexed(commandBuffer, savedObjects[IDs[i]].indexAmount, 1, savedObjects[IDs[i]].firstIndexIndex, savedObjects[IDs[i]].firstVertexIndex, 0);
    }

    vkCmdEndRenderPass(commandBuffer);

    vkEndCommandBuffer(commandBuffer);
}

void updateUniformBuffer() {
    UniformBufferObject ubo{};
    glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 view = glm::lookAt(glm::vec3(2.0f, 2.0f, 2.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f),   swapchainExtent.width / (float)   swapchainExtent.height, 0.1f, 10.0f);
    proj[1][1] *= -1;

    ubo.model = proj * view * model;

    void* data;
    vkMapMemory(  logicalDevice,   uniformBufferMemory, 0, sizeof(ubo), 0, &data);
        memcpy(data, &ubo, sizeof(ubo));
    vkUnmapMemory(  logicalDevice,   uniformBufferMemory);
}

}


void drawFrame(std::vector<int> IDs, std::vector<std::array<float, 3>> dinamic) {
    vkWaitForFences( logicalDevice, 1, & inFlightFence, VK_TRUE, UINT64_MAX);

    uint32_t imageIndex;
    VkResult result = vkAcquireNextImageKHR(  logicalDevice,   swapchainKHR, UINT64_MAX,   imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

    if (result == VK_ERROR_OUT_OF_DATE_KHR) {
        vkDeviceWaitIdle( logicalDevice);

         destroyDepthResources();
         destroySwapchain();
         createSwapchain();
         createDepthResources();
         createFramebuffers();

        return;
    }

    vkResetFences( logicalDevice, 1, &  inFlightFence);

    vkResetCommandBuffer( commandBuffer, 0);

    recordCommandBuffer( commandBuffer, imageIndex, IDs, dinamic);

    updateUniformBuffer();

    VkSubmitInfo submitInfo{};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

    VkSemaphore waitSemaphores[] = {  imageAvailableSemaphore};
    VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &  commandBuffer;

    VkSemaphore signalSemaphores[] = {  renderFinishedSemaphore};
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkQueueSubmit(  graphicsQueue, 1, &submitInfo,   inFlightFence);

    VkPresentInfoKHR presentInfo{};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;

    VkSwapchainKHR swapChains[] = {  swapchainKHR};
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;

    result = vkQueuePresentKHR(  presentQueue, &presentInfo);

    if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
        vkDeviceWaitIdle( logicalDevice);

         destroyDepthResources();
         destroySwapchain();
         createSwapchain();
         createDepthResources();
         createFramebuffers();

    }
}

    
}