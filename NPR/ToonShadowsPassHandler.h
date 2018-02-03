#ifndef NPR_TOONSHADOWSPASSHANDLER_H
#define NPR_TOONSHADOWSPASSHANDLER_H


#include <GL/glew.h>
#include <vector>
#include "Lights.h"

class ToonShadowsPassHandler {
public:
    ToonShadowsPassHandler(const char * vertFilePath, const char * fragFilePath);
    ~ToonShadowsPassHandler()
    {
        glDeleteProgram(programID);
    }
    void initializeShader(std::vector<Light*> const & lights);
    void use() {
        glUseProgram(programID);
    }
    GLuint programID;
    GLint MatrixID;
    GLint ViewMatrixID;
    GLint ModelMatrixID;

    GLint MatDiffuseColorID;
    GLint MatAmbientuseColorID;
    GLint MatSpecularColorID;
};


#endif //NPR_TOONSHADOWSPASSHANDLER_H
