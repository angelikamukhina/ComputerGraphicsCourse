#include <iostream>
#include "CombinePassHandler.h"
#include "ShadersLoader.h"

CombinePassHandler::CombinePassHandler(const char * vertFilePath, const char * fragFilePath) {
    programID = ShadersLoader::LoadShaders(vertFilePath, fragFilePath);
    firstID = glGetUniformLocation(programID, "first");
    secondID = glGetUniformLocation(programID, "second");
    thirdID = glGetUniformLocation(programID, "third");
    bgColorID = glGetUniformLocation(programID, "bgColor");
    fgColorID = glGetUniformLocation(programID, "fgColor");
}

void CombinePassHandler::renderQuad() {
    if (quadVAO == 0) {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        glGenBuffers(1, &quadVBO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
        glGenVertexArrays(1, &quadVAO);
        glBindVertexArray(quadVAO);
    }

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void CombinePassHandler::combinePass(GLuint firstFrontTexture, GLuint secondFrontTexture, GLuint backTexture,
                                     const glm::vec3 &bgColor, const glm::vec3 &fgColor)
{
    use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, firstFrontTexture);
    glUniform1i(firstID, 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, secondFrontTexture);
    glUniform1i(secondID, 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, backTexture);
    glUniform1i(thirdID, 2);

    glUniform3f(bgColorID, bgColor[0], bgColor[1], bgColor[2]);
    glUniform3f(fgColorID, fgColor[0], fgColor[1], fgColor[2]);
    renderQuad();
}

CombinePassHandler::~CombinePassHandler()
{
    glDeleteBuffers(1, &quadVBO);
    if (quadVAO != 0)
    {
        glDeleteVertexArrays(1, &quadVAO);
    }
    glDeleteProgram(programID);
}
