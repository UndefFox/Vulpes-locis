#include "fileLoaders.h"

#include "stringutils.h"


#include <fstream>
#include <stdlib.h>

namespace FileLoaders {

Mesh loadObjectFile(std::string filename) {
    Mesh mesh{};

    std::ifstream fileStream{};
    fileStream.open(filename);

    std::string buff;
    std::vector<std::string> substrings;
    buff.resize(256);

    std::vector<ct::Vector3> verticesCords{};
    std::vector<ct::Vector3> normalsCords{};
    std::vector<ct::Vector2> UVCords{};
    std::vector<std::array<std::array<int, 3>, 3>> faces;
    while (fileStream.getline(buff.data(), 256)) {
        substrings = StringUtils::split(buff, ' ');

        if (substrings[0] == "v") {
            verticesCords.push_back((ct::Vector3){
                std::atof(substrings[1].data()),
                std::atof(substrings[2].data()),
                std::atof(substrings[3].data())
            });
        }
        else if (substrings[0] == "vt") {
            UVCords.push_back((ct::Vector2){
                std::atof(substrings[1].data()),
                std::atof(substrings[2].data())
            });
        }
        if (substrings[0] == "vn") {
            normalsCords.push_back((ct::Vector3){
                std::atof(substrings[1].data()),
                std::atof(substrings[2].data()),
                std::atof(substrings[3].data())
            });
        }
        else if (substrings[0] == "f") {
            std::vector<std::string> first = StringUtils::split(substrings[1], '/');
            std::vector<std::string> second = StringUtils::split(substrings[2], '/');
            std::vector<std::string> third = StringUtils::split(substrings[3], '/');

            faces.push_back((std::array<std::array<int, 3>, 3>) {
                (std::array<int, 3>){ std::atoi(first[0].data()) - 1, std::atoi(first[1].data()) - 1, std::atoi(first[2].data()) - 1 },
                (std::array<int, 3>){ std::atoi(second[0].data()) - 1, std::atoi(second[1].data()) - 1, std::atoi(second[2].data()) - 1 },
                (std::array<int, 3>){ std::atoi(third[0].data()) - 1, std::atoi(third[1].data()) - 1, std::atoi(third[2].data()) - 1 }
            });
        }
    }

    std::vector<std::array<int, 3>> existingVertices{};
    for (int i = 0; i < faces.size(); i++) {
        Face newFace{};

        for (int k = 0; k < 3; k++) {
            
            int verticeIndex = -1;
            for (int z = 0; z < existingVertices.size(); z++) {
                if (existingVertices[z][0] == faces[i][k][0] &&
                    existingVertices[z][1] == faces[i][k][1] &&
                    existingVertices[z][2] == faces[i][k][2]) {
                    
                    verticeIndex = z;
                    break;
                }

            }

            if (verticeIndex == -1) {
                Vertice newVertice{};
                newVertice.cords = verticesCords[faces[i][k][0]];
                newVertice.UV = UVCords[faces[i][k][1]];
                newVertice.normal = normalsCords[faces[i][k][2]];
                mesh.vertices.push_back(newVertice);

                verticeIndex = existingVertices.size();

                existingVertices.push_back(faces[i][k]);
            }

            newFace.verticeIndexes[k] = verticeIndex;
        }

        mesh.faces.push_back(newFace);
    }

    return mesh;
}

void loadShaderFile(std::string filename, std::vector<char>& code) {
    std::ifstream file(filename, std::ios::ate | std::ios::binary);

    size_t fileSize = (size_t) file.tellg();
    code.resize(fileSize);

    file.seekg(0);
    file.read(code.data(), fileSize);

    file.close();
} 

}