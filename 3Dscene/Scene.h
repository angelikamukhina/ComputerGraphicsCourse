#ifndef INC_3DSCENE_SCENE_H
#define INC_3DSCENE_SCENE_H


#include <glm/glm.hpp>
#include <vector>
#include <assimp/scene.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <GLFW/glfw3.h>
#include "TransformHandler.h"
#include "Lights.h"

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

        if (vertices.size() < 3000 && vertices.size() > 100)
        {
            isRotated = true;
        }
        this->vertices = vertices;
        this->normals = normals;
        this->vertexOffset = vertexOffset;
    }

    glm::mat4 getModelMat()
    {
        return objectModelMatrix;
    }

    void draw()
    {
        glDrawArrays(GL_TRIANGLES, vertexOffset,
                     static_cast<GLsizei>(vertices.size()));
        rotate();
    }

    void drawStatic()
    {
        glDrawArrays(GL_TRIANGLES, vertexOffset,
                     static_cast<GLsizei>(vertices.size()));
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

private:
    glm::vec3 diffuseColor;
    glm::vec3 ambientColor;
    glm::vec3 specularColor;

    bool isRotated = false;
    glm::vec3 gOrientation;
    // For speed computation
	double lastTime = glfwGetTime();
	double lastFrameTime = lastTime;
	int nbFrames = 0;

    GLint vertexOffset;
    glm::mat4x4 objectModelMatrix = glm::mat4(1.0);
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
    void rotate()
    {
        if (isRotated)
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
    }
};

class Scene {
public:
    explicit Scene(const char * path, GLint matrixID, GLint modelMatrixID, GLint viewMatrixID,
                   GLint MatDiffuseColorID, GLint MatAmbientuseColorID, GLint MatSpecularColorID);

    void drawScene()
    {
        glm::mat4 Projection = TransformHandler::getProjectionMatrix();
        glm::mat4 View = TransformHandler::getViewMatrix();

        for (auto object : objects)
        {
            glm::vec3 diffuseColor = object->getDiffuseColor();
            glm::vec3 ambientColor = object->getAmbientColor();
            glm::vec3 specularColor = object->getSpecularColor();

            glUniform3f(MatDiffuseColorID, diffuseColor.r, diffuseColor.g, diffuseColor.b);
            glUniform3f(MatAmbientuseColorID, ambientColor.r, ambientColor.g, ambientColor.b);
            glUniform3f(MatSpecularColorID, specularColor.r, specularColor.g, specularColor.b);

            glm::mat4 Model = object->getModelMat();
            glm::mat4 MVP = Projection * View * Model;
            glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);
            glUniformMatrix4fv(modelMatID, 1, GL_FALSE, &Model[0][0]);
            glUniformMatrix4fv(viewMatId,  1, GL_FALSE, &View[0][0]);
            object->draw();
        }
    }

    void drawShadows(Light* light)
    {
        for (auto object : objects)
        {
            glm::mat4 Model = object->getModelMat();
            glm::mat4 depthProj = light->getProjection();
            glm::mat4 depthView = light->getView();
            glm::mat4 depthMVP = depthProj * depthView * Model;
            glUniformMatrix4fv(light->getMatrixID(), 1, GL_FALSE, &depthMVP[0][0]);
            object->drawStatic();
        }
    }

    ~Scene()
    {
        for(Object* object : objects)
        {
            delete object;
        }
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteBuffers(1, &normalbuffer);
    }

    GLuint getVertexbuffer()
    {
        return vertexbuffer;
    }

    GLuint getNormalbuffer()
    {
        return normalbuffer;
    }

private:
    GLint matrixID;
    GLint modelMatID;
    GLint viewMatId;

    GLint MatDiffuseColorID;
    GLint MatAmbientuseColorID;
    GLint MatSpecularColorID;

    GLuint normalbuffer;
    GLuint vertexbuffer;
    const aiScene* scene;
    std::vector<Object*> objects;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
};
#endif //INC_3DSCENE_SCENE_H
