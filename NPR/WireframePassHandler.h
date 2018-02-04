#ifndef NPR_WIREFRAMEPASSHANDLER_H
#define NPR_WIREFRAMEPASSHANDLER_H

#include <GL/glew.h>
#include "Scene.h"

class WireframePassHandler {
public:
    WireframePassHandler(const char * vertFilePath, const char * fragFilePath, int width, int height);

    GLuint getOutTexture() {
        return texture;
    }

    void pass(bool inverse, float linewidth, Object * object, GLint vertexbuffer, GLint bcbuffer);

    virtual ~WireframePassHandler();

    void use() {
        glUseProgram(programID);
    }

    GLuint framebuffer;
    GLuint texture, depth_texture;

    int width, height;

    static GLuint programID;
    static GLint mvpID, lineWidthID;
    static bool initialized;
};


#endif //NPR_WIREFRAMEPASSHANDLER_H
