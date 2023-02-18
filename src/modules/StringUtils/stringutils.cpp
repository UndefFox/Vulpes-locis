#include "stringutils.h"

namespace StringUtils {

std::vector<std::string> split(const std::string& str, char delimetr) {
    std::vector<std::string> output = {};

    int lastDelimetr = 0;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == delimetr) {
            output.push_back(str.substr(lastDelimetr, i - lastDelimetr));
            lastDelimetr = i + 1;
        }
    }

    output.push_back(str.substr(lastDelimetr));

    return output;
}

}