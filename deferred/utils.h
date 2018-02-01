#ifndef DEFERRED_UTILS_H
#define DEFERRED_UTILS_H

#include <GL/glew.h>
#include "QuadDrawer.h"

namespace utils {
    const unsigned int SCR_WIDTH = 1280;
    const unsigned int SCR_HEIGHT = 720;
    const glm::vec3 cameraPos = glm::vec3(0.0, 5.0, 5.0);

    enum Mode {
        DEFERRED_LIGHTING, POSITION, NORMALS, DIFFUSE_COLOR, AMBIENT_COLOR, SPECULAR_COLOR
    };

    static Mode mode = DEFERRED_LIGHTING;
};


#endif //DEFERRED_UTILS_H
