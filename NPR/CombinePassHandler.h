#ifndef NPR_COMBINEPASSHANDLER_H
#define NPR_COMBINEPASSHANDLER_H

#include <GL/glew.h>
#include <glm/vec3.hpp>

class CombinePassHandler {
public:
    CombinePassHandler(const char * vertPathFile, const char * fragFilePath);

    void combinePass(GLuint firstFrontTexture, GLuint secondFrontTexture, GLuint backTexture,
                     const glm::vec3 &bgColor, const glm::vec3 &fgColor);

    void use() {
        glUseProgram(programID);
    }

    virtual ~CombinePassHandler();
private:
    GLuint programID;
    GLint firstID, secondID, thirdID;
    GLint bgColorID, fgColorID;
    GLuint quadVAO = 0, quadVBO;
    void renderQuad();
};


#endif //NPR_COMBINEPASSHANDLER_H
