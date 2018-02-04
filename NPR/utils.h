#ifndef NPR_UTILS_H
#define NPR_UTILS_H

namespace utils {
    enum Mode {
        TOON_SHADING, WIREFRAME
    };

    static Mode mode = TOON_SHADING;
    
    static bool pause = false;
}

#endif //NPR_UTILS_H
