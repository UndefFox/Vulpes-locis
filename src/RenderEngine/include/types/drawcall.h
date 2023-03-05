#ifndef H_RENDERNGINE_DRAWCALL
#define H_RENDERNGINE_DRAWCALL

#include <array>

namespace RenderEngine {

struct DrawCall {
    int meshId;
    std::array<float, 3> position;
};

}

#endif
