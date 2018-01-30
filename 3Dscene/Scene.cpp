#include <assimp/Importer.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "Scene.h"


Scene::Scene(const char *path, GLint matrixID, GLint modelMatrixID, GLint viewMatrixID,
             GLint MatDiffuseColorID, GLint MatAmbientColorID, GLint MatSpecularColorID)
{
    this->matrixID = matrixID;
    this->modelMatID = modelMatrixID;
    this->viewMatId = viewMatrixID;
    this->MatDiffuseColorID = MatDiffuseColorID;
    this->MatAmbientuseColorID = MatAmbientColorID;
    this->MatSpecularColorID = MatSpecularColorID;

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

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);


    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
}
