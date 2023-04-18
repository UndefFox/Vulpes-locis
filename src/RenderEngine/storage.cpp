#include "RenderEngine/storage.h"

#include "src/memory.h"
#include "src/types/vertex.h"
#include "src/values.h"

#include <vulkan/vulkan.h>
#include <cstring>


namespace RenderEngine {

int addMesh(Mesh& meshData) {
    savedObjects.push_back({});

    std::vector<Vertex> vertices(meshData.vertices.size());
    for (int i = 0; i < meshData.vertices.size(); i++) {
        vertices[i].pos[0] = meshData.vertices[i][0];
        vertices[i].pos[1] = meshData.vertices[i][1];
        vertices[i].pos[2] = meshData.vertices[i][2];

        vertices[i].texCoord[0] = meshData.vertices[i][3];
        vertices[i].texCoord[1] = meshData.vertices[i][4];

        vertices[i].normal[0] = meshData.vertices[i][5];
        vertices[i].normal[1] = meshData.vertices[i][6];
        vertices[i].normal[2] = meshData.vertices[i][7];
    }

    VkBuffer buffer;
    VkDeviceMemory bufferMemory;
    VkDeviceSize size = vertices.size() * sizeof(Vertex);

    createBuffer(
        size,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        buffer,
        bufferMemory
    );

    void* data;
    vkMapMemory(logicalDevice, bufferMemory, 0, size, 0, &data);
        memcpy(data, vertices.data(), (size_t) size);
    vkUnmapMemory(logicalDevice, bufferMemory);

    copyBuffer(
        buffer,
        vertexBuffer,
        size,
        vertexSavedAmount * sizeof(Vertex)
    );
    savedObjects[lastIndex].firstVertexIndex = vertexSavedAmount;
    vertexSavedAmount += vertices.size();


    vkDestroyBuffer(logicalDevice, buffer, nullptr);
    vkFreeMemory(logicalDevice, bufferMemory, nullptr);


    size = meshData.indexes.size() * sizeof(uint16_t);

    createBuffer(
        size,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        buffer,
        bufferMemory
    );

    vkMapMemory(logicalDevice, bufferMemory, 0, size, 0, &data);
        memcpy(data, meshData.indexes.data(), (size_t) size);
    vkUnmapMemory(logicalDevice, bufferMemory);

    copyBuffer(
        buffer,
        indexBuffer,
        size,
        indexSavedAmount * sizeof(uint16_t)
    );
    savedObjects[lastIndex].firstIndexIndex = indexSavedAmount;
    savedObjects[lastIndex].indexAmount = meshData.indexes.size();
    indexSavedAmount += meshData.indexes.size();

    vkDestroyBuffer(logicalDevice, buffer, nullptr);
    vkFreeMemory(logicalDevice, bufferMemory, nullptr);

    return lastIndex++;
}

} // namespace RenderEngine