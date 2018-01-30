#ifndef INC_3DSCENE_LIGHTS_H
#define INC_3DSCENE_LIGHTS_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/euler_angles.hpp>


class Light {
public:
    static Light* getStatic()
    {
        if(!staticLight)
        {
            staticLight = new Light(false);
        }
        return staticLight;
    }
    static Light* getMoving()
    {
        if(!movingLight)
        {
            movingLight = new Light(true);
        }
        return movingLight;
    }
    glm::mat4 getDepthBiasVP()
    {
        const glm::mat4 biasMatrix(
                0.5, 0.0, 0.0, 0.0,
                0.0, 0.5, 0.0, 0.0,
                0.0, 0.0, 0.5, 0.0,
                0.5, 0.5, 0.5, 1.0
        );
        return biasMatrix * depthProjectionMatrix * depthViewMatrix;
    }

    glm::mat4 getProjection()
    {
        return depthProjectionMatrix;
    }

    glm::mat4 getView()
    {
        return depthViewMatrix;
    }

    glm::vec3 getPos()
    {
        return lightPos;
    }

    void setTexture(GLint texture)
    {
        depthTexture = texture;
    }

    void setMatrixID(GLint matrixID)
    {
        depthMVPID = matrixID;
    }

    void setFramebuffer(GLuint framebuffer)
    {
        this->framebuffer = framebuffer;
    }

    GLint getTexture()
    {
        return depthTexture;
    }

    GLint getMatrixID()
    {
        return depthMVPID;
    }

    GLuint getFramebuffer()
    {
        return framebuffer;
    }

    void moveLight()
    {
        if (isRotated)
        {
            lightPos = glm::rotateY(lightPos, 0.01f);
            depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
            depthViewMatrix = glm::lookAt(lightPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        }
    }

    ~Light()
    {
        glDeleteFramebuffers(1, &framebuffer);
        delete movingLight;
        delete staticLight;
    }

private:
    GLuint framebuffer;
    GLint depthTexture;
    GLint depthMVPID;
    bool isRotated = false;

    glm::vec3 lightPos;
    glm::mat4 depthProjectionMatrix;
    glm::mat4 depthViewMatrix;
    Light(bool isRotated)
    {
        this->isRotated = isRotated;
        lightPos = glm::vec3(4, 4, 4);
        depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
        depthViewMatrix = glm::lookAt(lightPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    }
    static Light* staticLight;
    static Light* movingLight;
};


#endif //INC_3DSCENE_LIGHT_H
