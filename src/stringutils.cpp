#include "stringutils.h"

#include <sstream>

namespace StringUtils {

std::vector<std::string> split(const std::string& str,const char delimetr) {
    std::vector<std::string> output{};

    std::stringstream ss(str);
    std::string item;

    while(std::getline(ss, item, delimetr)) {
        output.push_back(item);
    }


    return output;
}

}