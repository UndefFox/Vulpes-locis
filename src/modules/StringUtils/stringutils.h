#ifndef H_STRINGUTILS
#define H_STRINGUTILS

#include <vector>
#include <string>

namespace StringUtils {

/**
 * Splits string into parts separated by delimetr.
 */
std::vector<std::string> split(const std::string& str, char delimetr);

}

#endif