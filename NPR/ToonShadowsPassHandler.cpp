#include "ToonShadowsPassHandler.h"
#include "ShadersLoader.h"
#include "Lights.h"
#include "Window.h"
#include <glm/glm.hpp>
#include <string>
#include <vector>

ToonShadowsPassHandler::ToonShadowsPassHandler(const char * vertFilePath, const char * fragFilePath) {
    programID = ShadersLoader::LoadShaders(vertFilePath, fragFilePath);
    glUseProgram(programID);
    MatrixID = glGetUniformLocation(programID, "MVP");
    ViewMatrixID = glGetUniformLocation(programID, "V");
    ModelMatrixID = glGetUniformLocation(programID, "M");

    MatDiffuseColorID = glGetUniformLocation(programID, "MaterialDiffuseColor");
    MatAmbientuseColorID = glGetUniformLocation(programID, "MaterialAmbientColor");
    MatSpecularColorID = glGetUniformLocation(programID, "MaterialSpecularColor");
}

void ToonShadowsPassHandler::initializeShader(std::vector<Light*> const & lights) {
    // Use our shader
    use();
    Window * window = Window::getInstance();
    // Compute the MVP matrix from keyboard and mouse input
    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(window->camera->Zoom),
                                                  (float)window->width / (float)window->height,
                                                  0.1f, 100.0f);
    glm::mat4 ViewMatrix = window->camera->GetViewMatrix();

    const GLenum depthTextures[] = {GL_TEXTURE0, GL_TEXTURE1};

    for (size_t i = 0; i < lights.size(); ++i) {
        glActiveTexture(depthTextures[i]);
        auto light = lights[i];
        glBindTexture(GL_TEXTURE_2D, light->getTexture());
        std::string lightIdx = std::to_string(i);
        const GLint positionID = glGetUniformLocation(programID, ("LightPositions[" + lightIdx + "]").c_str());
        glm::vec3 lightPos = light->getPos();
        glUniform3f(positionID, lightPos.x, lightPos.y, lightPos.z);
        const GLint DepthBiasID = glGetUniformLocation(programID, ("DepthBiasVPs[" + lightIdx + "]").c_str());
        glm::mat4 depthBiasMVP = light->getDepthBiasVP();
        glUniformMatrix4fv(DepthBiasID, 1, GL_FALSE, &depthBiasMVP[0][0]);
        const auto shadowMaps = "shadowMaps[" + lightIdx + "]";
        const GLint ShadowMapID = glGetUniformLocation(programID, shadowMaps.c_str());
        glUniform1i(ShadowMapID, static_cast<GLint>(i));
        glUniformMatrix4fv(DepthBiasID, 1, GL_FALSE, &depthBiasMVP[0][0]);
    }
}


