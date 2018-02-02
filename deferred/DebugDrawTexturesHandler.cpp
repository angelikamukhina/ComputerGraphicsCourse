#include "DebugDrawTexturesHandler.h"
#include "ShadersLoader.h"

DebugDrawTexturesHandler::DebugDrawTexturesHandler(const char *vert_file_path, const char *frag_file_path,
                                                   GeomPassHandler * geomPassHandler) {
    this->geomPassHandler = geomPassHandler;
    programID = ShadersLoader::LoadShaders(vert_file_path, frag_file_path);
}

void DebugDrawTexturesHandler::debugDraw(utils::Mode mode) {
    glUseProgram(programID);
    glActiveTexture(GL_TEXTURE0);
    unsigned int texture;
    switch (mode) {
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
