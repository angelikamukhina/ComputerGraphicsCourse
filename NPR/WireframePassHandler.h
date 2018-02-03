#ifndef NPR_WIREFRAMEPASSHANDLER_H
#define NPR_WIREFRAMEPASSHANDLER_H


#include <GL/glew.h>

class WireframePassHandler {
public:
    WireframePassHandler(const char * vertFilePath, const char * fragFilePath);
    void wireframePass(GLint firstFrontTexture, GLint secondFrontTexture, GLint backTexture);
private:
    GLuint programID;
};


#endif //NPR_WIREFRAMEPASSHANDLER_H
