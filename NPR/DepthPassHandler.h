#ifndef NPR_DEPTHPASSHANDLER_H
#define NPR_DEPTHPASSHANDLER_H


#include <GL/glew.h>

class DepthPassHandler {
public:
    DepthPassHandler(const char * vertFilePath, const char * fragFilePath);
    GLint getDepthTexture();
private:
    GLuint framebuffer;
    GLuint programID;
};


#endif //NPR_DEPTHPASSHANDLER_H
