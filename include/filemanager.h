#ifndef H_FILEMANAGER
#define H_FILEMANAGER

#define SHADER_FILES_DIR  "shaders/"

#define FILE_NAME_VERT_SHADER "vertical.spv"
#define FILE_NAME_FRAG_SHADER "fragment.spv"

#include <vector>
#include <string>
#include <array>
#include <fstream>

class FileManager {
public:

private:

public:
    /**
     * Loading shader file.
     * 
     * @param filename Name of the shader wich must be loaded.
     * @param code Where to store byte code of the file.
     * @return true File readed succesfully.
     * @return false Unable to read file.
     */
    static bool loadShaderFile(std::string filename, std::vector<char>& code);
};

#endif