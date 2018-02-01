#include "DebugDrawTexturesHandler.h"
#include "ShadersLoader.h"

DebugDrawTexturesHandler::DebugDrawTexturesHandler(const char *vert_file_path, const char *frag_file_path,
                                                   GeomPassHandler * geomPassHandler) {
    this->geomPassHandler = geomPassHandler;
    programID = ShadersLoader::LoadShaders(vert_file_path, frag_file_path);
}
