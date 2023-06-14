#include "RenderEngine/storage.h"

#include "src/memory.h"
#include "src/types/vertex.h"
#include "src/values.h"

#include <vulkan/vulkan.h>
#include <cstring>


namespace RenderEngine {

int addMesh(Mesh& mesh) {
    savedObjects.push_back({});

    std::vector<Vertex> vertices(mesh.vertices.size());
    for (int i = 0; i < mesh.vertices.size(); i++) {
        Vertice vertice = mesh.vertices[i];

        vertices[i].pos[0] = vertice.cords.x;
        vertices[i].pos[1] = vertice.cords.y;
        vertices[i].pos[2] = vertice.cords.z;

        vertices[i].texCoord[0] = vertice.UV.x;
        vertices[i].texCoord[1] = vertice.UV.y;

        vertices[i].normal[0] = vertice.normal.x;
        vertices[i].normal[1] = vertice.normal.y;
        vertices[i].normal[2] = vertice.normal.z;
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

    std::vector<int16_t> indexes{};
    for (int i = 0; i < mesh.faces.size(); i++) {
        indexes.push_back(mesh.faces[i].verticeIndexes[0]);
        indexes.push_back(mesh.faces[i].verticeIndexes[1]);
        indexes.push_back(mesh.faces[i].verticeIndexes[2]);
    }
    size = indexes.size() * sizeof(uint16_t);

    createBuffer(
        size,
        VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        buffer,
        bufferMemory
    );

    vkMapMemory(logicalDevice, bufferMemory, 0, size, 0, &data);
        memcpy(data, indexes.data(), (size_t) size);
    vkUnmapMemory(logicalDevice, bufferMemory);

    copyBuffer(
        buffer,
        indexBuffer,
        size,
        indexSavedAmount * sizeof(uint16_t)
    );
    savedObjects[lastIndex].firstIndexIndex = indexSavedAmount;
    savedObjects[lastIndex].indexAmount = indexes.size();
    indexSavedAmount += indexes.size();

    vkDestroyBuffer(logicalDevice, buffer, nullptr);
    vkFreeMemory(logicalDevice, bufferMemory, nullptr);

    return lastIndex++;
}

} // namespace RenderEngine