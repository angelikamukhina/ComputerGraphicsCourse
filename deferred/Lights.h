#ifndef INC_3DSCENE_LIGHTS_H
#define INC_3DSCENE_LIGHTS_H

#include <glm/gtx/rotate_vector.hpp>


class Light {
public:
    Light(glm::vec3 position, glm::vec3 color) : lightPos(position), lightColor(color) {}
    glm::vec3 getPos()
    {
        return lightPos;
    }
    glm::vec3 getColor()
    {
        return lightColor;
    }
    void moveLight()
    {
        lightPos = glm::rotateY(lightPos, 0.01f);
    }
private:
    glm::vec3 lightPos;
    glm::vec3 lightColor;
};


#endif //INC_3DSCENE_LIGHT_H
