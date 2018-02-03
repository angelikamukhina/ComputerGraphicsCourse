#ifndef NPR_DEPTHPASSHANDLER_H
#define NPR_DEPTHPASSHANDLER_H

#include <GL/glew.h>
#include <vector>
#include "Lights.h"

class LightDepthPassHandler {
public:
    LightDepthPassHandler(const char * vert_file_path, const char * frag_file_path);
    void setDepthTextures(std::vector<Light *> const &lights);
    void use() {
        glUseProgram(programID);
    }
    ~LightDepthPassHandler() {
        glDeleteProgram(programID);
    }
    GLuint programID;
};


#endif //NPR_DEPTHPASSHANDLER_H
