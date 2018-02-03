#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Scene.h"
#include "ToonShadowsPassHandler.h"


Scene::Scene(const char *path, ToonShadowsPassHandler * toonShadowsPassHandler)
{
    this->toonShadowsPassHandler = toonShadowsPassHandler;

    Assimp::Importer importer;
    scene = importer.ReadFile(path, 0);
    if( !scene)
    {
        printf("%s\n", importer.GetErrorString());
        assert(0);
    }
    for(unsigned int i = 0; i < scene->mNumMeshes; ++i)
    {
        const aiMesh* mesh = scene->mMeshes[i];
        aiMaterial *mtl = scene->mMaterials[mesh->mMaterialIndex];
        aiColor4D diffuse;
        glm::vec3 diffuseColor;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
        {
            diffuseColor = glm::vec3(diffuse.r, diffuse.g, diffuse.b);
        }

        glm::vec3 ambientColor = 0.05f * diffuseColor;

        aiColor4D specular;
        glm::vec3 specularColor;
        if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
        {
            specularColor = glm::vec3(specular.r, specular.g, specular.b);
        }

        std::vector<glm::vec3> objectVertices;
        std::vector<glm::vec3> objectNormals;
        GLint offset = vertices.size();
        for(unsigned int vert = 0; vert < mesh->mNumVertices; ++vert)
        {
            aiVector3D vertPos = mesh->mVertices[vert];
            glm::vec3 vertPos_glm = glm::vec3(vertPos.x, vertPos.y, vertPos.z);
            objectVertices.push_back(vertPos_glm);
            vertices.push_back(vertPos_glm);
        }
        for(unsigned int norm = 0; norm < mesh->mNumVertices; ++norm)
        {
            aiVector3D normal = mesh->mNormals[norm];
            glm::vec3 normal_glm = glm::vec3(normal.x, normal.y, normal.z);
            objectNormals.push_back(normal_glm);
            normals.push_back(normal_glm);
        }
        auto * object = new Object(objectVertices, objectNormals, offset,
                                   diffuseColor, ambientColor, specularColor);
        objects.push_back(object);
    }

    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);


    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}


void Scene::drawScene(utils::Mode mode)
{
    Window * window = Window::getInstance();
    glm::mat4 Projection = glm::perspective(glm::radians(window->camera->Zoom),
                                            (float)window->width / (float)window->height,
                                            0.1f, 100.0f);
    glm::mat4 View = window->camera->GetViewMatrix();

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
            0,                  // attribute
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void*)0
    );

    for (auto object : objects)
    {
        glm::vec3 diffuseColor = object->getDiffuseColor();
        glm::vec3 ambientColor = object->getAmbientColor();
        glm::vec3 specularColor = object->getSpecularColor();

        glUniform3f(toonShadowsPassHandler->MatDiffuseColorID, diffuseColor.r, diffuseColor.g, diffuseColor.b);
        glUniform3f(toonShadowsPassHandler->MatAmbientuseColorID, ambientColor.r, ambientColor.g, ambientColor.b);
        glUniform3f(toonShadowsPassHandler->MatSpecularColorID, specularColor.r, specularColor.g, specularColor.b);

        glm::mat4 Model = object->getModelMat();
        glm::mat4 MVP = Projection * View * Model;
        glUniformMatrix4fv(toonShadowsPassHandler->MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(toonShadowsPassHandler->ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
        glUniformMatrix4fv(toonShadowsPassHandler->ViewMatrixID,  1, GL_FALSE, &View[0][0]);
        if (mode == utils::TOON_SHADING) {
            object->drawFill();
        } else {
            object->drawWireframe();
        }
    }

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
