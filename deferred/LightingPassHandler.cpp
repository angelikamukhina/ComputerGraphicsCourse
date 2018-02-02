#include <vector>
#include "LightingPassHandler.h"
#include "ShadersLoader.h"
#include "Lights.h"
#include "utils.h"

std::vector<Light> getLights(int lightsNumber);

LightingPassHandler::LightingPassHandler(const char *vertex_file_path, const char *fragment_file_path,
                                        GeomPassHandler * geomPassHandler, int maxLightsNumber) {
    programID = ShadersLoader::LoadShaders(vertex_file_path, fragment_file_path);
    lights = getLights(maxLightsNumber);
    this->geomPassHandler = geomPassHandler;
    glUseProgram(programID);
    glUniform1i(glGetUniformLocation(programID, "gPosition"), 0);
    glUniform1i(glGetUniformLocation(programID, "gNormal"), 1);
    glUniform1i(glGetUniformLocation(programID, "gDiffuseColor"), 2);
    glUniform1i(glGetUniformLocation(programID, "gSpecularColor"), 3);
    glUniform1i(glGetUniformLocation(programID, "gAmbientColor"), 4);
}

void LightingPassHandler::lightingPass() {
    glUseProgram(programID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, geomPassHandler->getPositionTexture());
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, geomPassHandler->getNormalTexture());
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, geomPassHandler->getDiffuseColorTexture());
    glActiveTexture(GL_TEXTURE3);
    glBindTexture(GL_TEXTURE_2D, geomPassHandler->getSpecularColorTexture());
    glActiveTexture(GL_TEXTURE4);
    glBindTexture(GL_TEXTURE_2D, geomPassHandler->getAmbientColorTexture());

    GLint cameraPosID = glGetUniformLocation(programID, "viewPos");
    glUniform3f(cameraPosID, utils::cameraPos.x, utils::cameraPos.y, utils::cameraPos.z);

    GLint actLightNumber = glGetUniformLocation(programID, "actLightNumber");
    glUniform1i(actLightNumber, lightsCount);

    for (unsigned int i = 0; i < lightsCount; i++)
    {
        GLint positionID = glGetUniformLocation(programID, ("lights[" + std::to_string(i) + "].Position").c_str());
        glm::vec3 position = lights[i].getPos();
        glUniform3f(positionID, position.x, position.y, position.z);
        GLint colorID = glGetUniformLocation(programID, ("lights[" + std::to_string(i) + "].Color").c_str());
        glm::vec3 color = lights[i].getColor();
        glUniform3f(colorID, color.r, color.g, color.b);
        lights[i].moveLight();
        const float linear = 0.8;
        const float quadratic = 8;
        GLint linearID = glGetUniformLocation(programID, ("lights[" + std::to_string(i) + "].Linear").c_str());
        glUniform1f(linearID, linear);
        GLint quadraticID = glGetUniformLocation(programID, ("lights[" + std::to_string(i) + "].Quadratic").c_str());
        glUniform1f(quadraticID, quadratic);
    }
    QuadDrawer::renderQuad();
}

std::vector<Light> getLights(int lightsNumber) {
    std::vector<Light> lights;
    srand(13);
    for (unsigned int i = 0; i < lightsNumber; i++) {
        // calculate slightly random offsets
        float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        float yPos = 0.0;
        float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        // also calculate random color
        float rColor = (float)rand() / RAND_MAX; // between 0.0 and 1.0
        float gColor = (float)rand() / RAND_MAX; // between 0.0 and 1.0
        float bColor = (float)rand() / RAND_MAX; // between 0.0 and 1.0
        lights.emplace_back(glm::vec3(xPos, yPos, zPos), glm::vec3(rColor, gColor, bColor));
    }
    return lights;
}
