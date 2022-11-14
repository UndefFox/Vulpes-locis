#ifndef H_FILEMANAGEr_FILEMANAGER
#define H_FILEMANAGEr_FILEMANAGER

#define SHADER_FILES_DIR  "shaders/"

#define FILE_NAME_VERT_SHADER "vertical.spv"
#define FILE_NAME_FRAG_SHADER "fragment.spv"

#include <vector>
#include <string>
#include <array>
#include <fstream>

namespace FileManager {

bool loadShaderFile(std::string filename, std::vector<char>& code);

};

#endif