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

class Object
{
public:
    Object(std::vector<glm::vec3>& vertices,
           std::vector<glm::vec3>& normals,
           GLint vertexOffset,
           glm::vec3 diffuseColor,
           glm::vec3 ambientColor,
           glm::vec3 specularColor) {
        this->diffuseColor = diffuseColor;
        this->ambientColor = ambientColor;
        this->specularColor = specularColor;
        this->vertices = vertices;
        this->normals = normals;
        this->vertexOffset = vertexOffset;
    }

    void draw() {
        glDrawArrays(GL_TRIANGLES, vertexOffset,
                     static_cast<GLsizei>(vertices.size()));
    }

    glm::vec3 getDiffuseColor() {
        return diffuseColor;
    }

    glm::vec3 getAmbientColor() {
        return ambientColor;
    }

    glm::vec3 getSpecularColor() {
        return specularColor;
    }

private:
    glm::vec3 diffuseColor;
    glm::vec3 ambientColor;
    glm::vec3 specularColor;
    GLint vertexOffset;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> normals;
};

class Scene {
public:
    explicit Scene(const char * path, GLint MatDiffuseColorID, GLint MatAmbientuseColorID, GLint MatSpecularColorID);

    void drawScene() {
        for (auto object : objects) {
            glm::vec3 diffuseColor = object->getDiffuseColor();
            glm::vec3 ambientColor = object->getAmbientColor();
            glm::vec3 specularColor = object->getSpecularColor();

            glUniform3f(MatDiffuseColorID, diffuseColor.r, diffuseColor.g, diffuseColor.b);
            glUniform3f(MatAmbientuseColorID, ambientColor.r, ambientColor.g, ambientColor.b);
            glUniform3f(MatSpecularColorID, specularColor.r, specularColor.g, specularColor.b);
            object->draw();
        }
    }

    ~Scene() {
        for(Object* object : objects) {
            delete object;
        }
        glDeleteBuffers(1, &vertexbuffer);
        glDeleteBuffers(1, &normalbuffer);
    }

    GLuint getVertexbuffer() {
        return vertexbuffer;
    }

    GLuint getNormalbuffer() {
        return normalbuffer;
    }

private:
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
