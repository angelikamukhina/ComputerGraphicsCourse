#include "WireframePassHandler.h"
#include "ShadersLoader.h"

WireframePassHandler::WireframePassHandler(const char *vertFilePath, const char *fragFilePath) {
    programID = ShadersLoader::LoadShaders(vertFilePath, fragFilePath);
}

void WireframePassHandler::wireframePass(GLint firstFrontTexture, GLint secondFrontTexture, GLint backTexture) {

}
