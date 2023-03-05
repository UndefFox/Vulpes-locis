#include "fileLoaders.h"

#include "object.h"

#include "StringUtils/stringutils.h"

#include <fstream>
#include <stdlib.h>

namespace FileLoaders {

Object loadObjectFile(std::string filename) {
    Object object{};

    std::ifstream fileStream{};
    fileStream.open(filename);

    std::string buff;
    std::vector<std::string> substrings;
    buff.resize(256);
    while (fileStream.getline(buff.data(), 256)) {
        substrings = StringUtils::split(buff, ' ');

        if (substrings[0] == "v") {
            object.verticesCords.push_back((std::array<float, 3>){
                std::atof(substrings[1].data()),
                std::atof(substrings[2].data()),
                std::atof(substrings[3].data())
            });
        }
        else if (substrings[0] == "vt") {
            object.textureCords.push_back((std::array<float, 2>){
                std::atof(substrings[1].data()),
                std::atof(substrings[2].data())
            });
        }
        if (substrings[0] == "vn") {
            object.normalCords.push_back((std::array<float, 3>){
                std::atof(substrings[1].data()),
                std::atof(substrings[2].data()),
                std::atof(substrings[3].data())
            });
        }
        else if (substrings[0] == "f") {
            std::vector<std::string> first = StringUtils::split(substrings[1], '/');
            std::vector<std::string> second = StringUtils::split(substrings[2], '/');
            std::vector<std::string> third = StringUtils::split(substrings[3], '/');

            object.faces.push_back((std::array<std::array<int, 3>, 3>) {
                (std::array<int, 3>){ std::atoi(first[0].data()), std::atoi(first[1].data()), std::atoi(first[2].data()) },
                (std::array<int, 3>){ std::atoi(second[0].data()), std::atoi(second[1].data()), std::atoi(second[2].data()) },
                (std::array<int, 3>){ std::atoi(third[0].data()), std::atoi(third[1].data()), std::atoi(third[2].data()) }
            });
        }
    }

    return object;
}

}