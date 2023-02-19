#include "objectToMesh.h"

#include <vector>
#include <array>

namespace ObjectToMesh {

RenderEngine::Mesh convert(Object& object) {
    
    std::vector<std::array<int, 3>> existingVertices;
    RenderEngine::Mesh mesh{};
    int lastIndex = 0;

    for (int i = 0; i < object.faces.size() * 3; i++) {
        bool finded = false;
        for (int x = 0; x < existingVertices.size(); x++) {
            if (existingVertices[x][0] == object.faces[i/3][i%3][0] &&
                existingVertices[x][1] == object.faces[i/3][i%3][1] &&
                existingVertices[x][2] == object.faces[i/3][i%3][2]) {
                mesh.indexes.push_back(x);
                finded = true;
                break;
            }
        }

        if (finded)
            continue;

        existingVertices.push_back(object.faces[i/3][i%3]);

        mesh.vertices.push_back({
            object.verticesCords[object.faces[i/3][i%3][0] - 1][0],
            object.verticesCords[object.faces[i/3][i%3][0] - 1][1],
            object.verticesCords[object.faces[i/3][i%3][0] - 1][2],

            object.textureCords[object.faces[i/3][i%3][1] - 1][0],
            object.textureCords[object.faces[i/3][i%3][1] - 1][1],

            object.normalCords[object.faces[i/3][i%3][2] - 1][0],
            object.normalCords[object.faces[i/3][i%3][2] - 1][1],
            object.normalCords[object.faces[i/3][i%3][2] - 1][2]
        });

        mesh.indexes.push_back(lastIndex++);
    }

    return mesh;

}

}