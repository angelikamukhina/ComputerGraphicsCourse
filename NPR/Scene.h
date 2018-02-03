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
#include "ToonShadowsPassHandler.h"

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

    void drawFill()
    {
        glDrawArrays(GL_TRIANGLES, vertexOffset,
                     static_cast<GLsizei>(vertices.size()));
        rotate();
    }

    void drawWireframe()
    {
        for(int i = 0; i < static_cast<GLsizei>(vertices.size()); i += 3)
            glDrawArrays(GL_LINE_LOOP, vertexOffset + i, 3);
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
    explicit Scene(const char * path, ToonShadowsPassHandler * toonShadowsPassHandler);

    void drawScene(utils::Mode mode);

    void drawShadows(Light* light)
    {
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                0,  // The attribute we want to configure
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );

        for (auto object : objects)
        {
            glm::mat4 Model = object->getModelMat();
            glm::mat4 depthProj = light->getProjection();
            glm::mat4 depthView = light->getView();
            glm::mat4 depthMVP = depthProj * depthView * Model;
            glUniformMatrix4fv(light->getMatrixID(), 1, GL_FALSE, &depthMVP[0][0]);
            object->drawStatic();
        }
        glDisableVertexAttribArray(0);
    }

    ~Scene()
    {
        for(Object* object : objects)
        {
            delete object;
        }
        glDeleteVertexArrays(1, &VertexArrayID);
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
    ToonShadowsPassHandler * toonShadowsPassHandler;
    GLuint VertexArrayID;
    GLuint normalbuffer;
    GLuint vertexbuffer;
    const aiScene* scene;
    std::vector<Object*> objects;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
};
#endif //INC_3DSCENE_SCENE_H
