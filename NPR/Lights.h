#ifndef INC_3DSCENE_LIGHTS_H
#define INC_3DSCENE_LIGHTS_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light
{
public:
    static Light *getStatic() {
        if (!staticLight) {
            staticLight = new Light(false);
        }
        return staticLight;
    }

    static Light *getMoving() {
        if (!movingLight)
        {
            movingLight = new Light(true);
        }
        return movingLight;
    }

    glm::mat4 getDepthBiasVP() {
        const glm::mat4 biasMatrix(
                0.5, 0.0, 0.0, 0.0,
                0.0, 0.5, 0.0, 0.0,
                0.0, 0.0, 0.5, 0.0,
                0.5, 0.5, 0.5, 1.0
        );
        return biasMatrix * depthProjectionMatrix * depthViewMatrix;
    }

    glm::mat4 getProjection() {
        return depthProjectionMatrix;
    }

    glm::mat4 getView() {
        return depthViewMatrix;
    }

    glm::vec3 getPos() {
        return lightPos;
    }

    void setTexture(GLint texture) {
        depthTexture = texture;
    }

    void setMatrixID(GLint matrixID) {
        depthMVPID = matrixID;
    }

    void setFramebuffer(GLuint framebuffer) {
        this->framebuffer = framebuffer;
    }

    GLint getTexture() {
        return depthTexture;
    }

    GLint getMatrixID() {
        return depthMVPID;
    }

    GLuint getFramebuffer() {
        return framebuffer;
    }

    void moveLight();

    ~Light();

private:
    GLuint framebuffer;
    GLint depthTexture;
    GLint depthMVPID;
    bool isRotated = false;

    glm::vec3 lightPos;
    glm::mat4 depthProjectionMatrix;
    glm::mat4 depthViewMatrix;

    Light(bool isRotated);

    static Light *staticLight;
    static Light *movingLight;
};


#endif //INC_3DSCENE_LIGHT_H


