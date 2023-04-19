#ifndef H_FORMATERS_OBJECT
#define H_FORMATERS_OBJECT

#include "object.h"


#include <string>

namespace FileLoaders {

/**
 * Loads data from obj file.
 * 
 * Supports:
 *  'v' - vertices positions
 *  'vn' - normals
 *  'vt' - texture coradinates
 * 
 *  'f' - only v/vn/vt format
 */
Object loadObjectFile(std::string filename);

/**
 * Load code from spv files into code vector.
 */
void loadShaderFile(std::string filename, std::vector<char>& code);

}

#endif