#ifndef INC_3DSCENE_SCENE_H
#define INC_3DSCENE_SCENE_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include <assimp/scene.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <GLFW/glfw3.h>
#include "Lights.h"
#include "Window.h"
#include "utils.h"

class Object
{
public:
    Object(std::vector<glm::vec3>& vertices,
           std::vector<glm::vec3>& normals,
           GLint vertexOffset,
           glm::vec3 diffuseColor,
           glm::vec3 ambientColor,
           glm::vec3 specularColor)
    {
        this->diffuseColor = diffuseColor;
        this->ambientColor = ambientColor;
        this->specularColor = specularColor;
        this->vertices = vertices;
        this->normals = normals;
        this->vertexOffset = vertexOffset;
    }

    glm::mat4 getModelMat()
    {
        return objectModelMatrix;
    }

    glm::vec3 getDiffuseColor()
    {
        return diffuseColor;
    }

    glm::vec3 getAmbientColor()
    {
        return ambientColor;
    }

    glm::vec3 getSpecularColor()
    {
        return specularColor;
    }

    void setCorrectLastUpdateTime() {
        lastFrameTime = glfwGetTime();
    }
    
    void rotate()
    {
        // Measure speed
        double currentTime = glfwGetTime();
        float deltaTime = (float)(currentTime - lastFrameTime);
        lastFrameTime = currentTime;
        nbFrames++;
        if ( currentTime - lastTime >= 1.0 ){ // If last prinf() was more than 1sec ago
            // printf and reset
            nbFrames = 0;
            lastTime += 1.0;
        }
        gOrientation.y += 3.14159f/2.0f * deltaTime;

        // Build the model matrix
        glm::mat4 RotationMatrix = glm::eulerAngleYXZ(gOrientation.y, gOrientation.x, gOrientation.z);
        glm::mat4 ScalingMatrix = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
        objectModelMatrix = RotationMatrix * ScalingMatrix;
    }

    const std::vector<glm::vec3> &getVertices()
    {
        return vertices;
    }

    const std::vector<glm::vec3> &getNormals()
    {
        return normals;
    }

    const GLint getVertexOffset() const
    {
        return vertexOffset;
    }

private:
    glm::vec3 diffuseColor;
    glm::vec3 ambientColor;
    glm::vec3 specularColor;

    bool isRotated = true;
    glm::vec3 gOrientation;
    // For speed computation
	double lastTime = glfwGetTime();
	double lastFrameTime = lastTime;
	int nbFrames = 0;

    GLint vertexOffset;
    glm::mat4x4 objectModelMatrix = glm::mat4(1.0);
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
};

class Scene {
public:
    explicit Scene(const char * path);

    ~Scene()
    {
        for(Object* object : objects)
        {
            delete object;
        }
    }

    const std::vector<Object*> getObjects() const
    {
        return objects;
    }

    const std::vector<glm::vec3> getVertices() const
    {
        return vertices;
    }

    const std::vector<glm::vec3> getNormals() const
    {
        return normals;
    }

private:
    const aiScene* scene;
    std::vector<Object*> objects;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
};
#endif //INC_3DSCENE_SCENE_H
