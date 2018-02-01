#ifndef DEFERRED_LIGHTINGPASSHANDLER_H
#define DEFERRED_LIGHTINGPASSHANDLER_H


#include <GL/glew.h>
#include "Lights.h"
#include "GeomPassHandler.h"

class LightingPassHandler {
public:
    LightingPassHandler(const char * vertex_file_path,
                        const char * fragment_file_path,
                        GeomPassHandler * geomPassHandler);
    void lightingPass();
    int lightsCount = 32;
    ~LightingPassHandler()
    {
        glDeleteProgram(programID);
    }
private:
    GLuint programID;
    std::vector<Light> lights;
    GeomPassHandler * geomPassHandler;
};


#endif //DEFERRED_LIGHTINGPASSHANDLER_H
