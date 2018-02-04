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

void ToonShadowsPassHandler::initializeShader(Light *light) {
    // Use our shader
    use();
    Window * window = Window::getInstance();
    // Compute the MVP matrix from keyboard and mouse input
    glm::mat4 ProjectionMatrix = glm::perspective(glm::radians(window->camera->Zoom),
                                                  (float)window->width / (float)window->height,
                                                  0.1f, 100.0f);
    glm::mat4 ViewMatrix = window->camera->GetViewMatrix();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, light->getTexture());
    const GLint positionID = glGetUniformLocation(programID, "LightPosition");
    glm::vec3 lightPos = light->getPos();
    glUniform3f(positionID, lightPos.x, lightPos.y, lightPos.z);
    const GLint DepthBiasID = glGetUniformLocation(programID, "DepthBiasVP");
    glm::mat4 depthBiasMVP = light->getDepthBiasVP();
    glUniformMatrix4fv(DepthBiasID, 1, GL_FALSE, &depthBiasMVP[0][0]);
    const GLint ShadowMapID = glGetUniformLocation(programID, "shadowMap");
    glUniform1i(ShadowMapID, 0);
    glUniformMatrix4fv(DepthBiasID, 1, GL_FALSE, &depthBiasMVP[0][0]);
}


