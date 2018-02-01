#ifndef DEFERRED_DEBUGDRAWTEXTURESHANDLER_H
#define DEFERRED_DEBUGDRAWTEXTURESHANDLER_H


#include <GL/glew.h>
#include "GeomPassHandler.h"
#include "utils.h"

class DebugDrawTexturesHandler {
public:
    DebugDrawTexturesHandler(const char * vert_file_path, const char * frag_file_path,
                            GeomPassHandler * geomPassHandler);
    void debugDraw()
    {
        glUseProgram(programID);
        glActiveTexture(GL_TEXTURE0);
        unsigned int texture;
        switch (utils::mode)
        {
            case utils::POSITION: texture = geomPassHandler->getPositionTexture();
                break;
            case utils::NORMALS: texture = geomPassHandler->getNormalTexture();
                break;
            case utils::DIFFUSE_COLOR: texture = geomPassHandler->getDiffuseColorTexture();
                break;
            case utils::AMBIENT_COLOR: texture = geomPassHandler->getAmbientColorTexture();
                break;
            case utils::SPECULAR_COLOR: texture = geomPassHandler->getSpecularColorTexture();
                break;
            default: assert(0);
        }
        glBindTexture(GL_TEXTURE_2D, texture);
        GLint textureID = glGetUniformLocation(programID, "fboAttachment");
        glUniform1i(textureID, 0);
        QuadDrawer::renderQuad();
    }
    ~DebugDrawTexturesHandler()
    {
        glDeleteProgram(programID);
    }
private:
    GLuint programID;
    GeomPassHandler * geomPassHandler;
};


#endif //DEFERRED_DEBUGDRAWTEXTURESHANDLER_H
