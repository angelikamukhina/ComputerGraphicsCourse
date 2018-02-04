#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Lights.h"

Light* Light::staticLight = 0;
Light* Light::movingLight = 0;

Light::Light(bool isRotated)
{
    this->isRotated = isRotated;
    lightPos = glm::vec3(4, 4, 4);
    depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
    depthViewMatrix = glm::lookAt(lightPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

void Light::moveLight()
{
    if (isRotated)
    {
        lightPos = glm::rotateY(lightPos, 0.01f);
        depthProjectionMatrix = glm::ortho<float>(-10, 10, -10, 10, -10, 20);
        depthViewMatrix = glm::lookAt(lightPos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    }
}

Light::~Light()
{
    glDeleteFramebuffers(1, &framebuffer);
    delete movingLight;
    delete staticLight;
}



