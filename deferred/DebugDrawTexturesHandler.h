#ifndef DEFERRED_DEBUGDRAWTEXTURESHANDLER_H
#define DEFERRED_DEBUGDRAWTEXTURESHANDLER_H


#include <GL/glew.h>
#include "GeomPassHandler.h"
#include "utils.h"

class DebugDrawTexturesHandler {
public:
    DebugDrawTexturesHandler(const char * vert_file_path, const char * frag_file_path,
                            GeomPassHandler * geomPassHandler);
    void debugDraw(utils::Mode mode);
    ~DebugDrawTexturesHandler() {
        glDeleteProgram(programID);
    }
private:
    GLuint programID;
    GeomPassHandler * geomPassHandler;
};


#endif //DEFERRED_DEBUGDRAWTEXTURESHANDLER_H
