#ifndef DEFERRED_GEOMPASSHANDLER_H
#define DEFERRED_GEOMPASSHANDLER_H


#include <GL/gl.h>
#include "Scene.h"

class GeomPassHandler {
public:
    GeomPassHandler(const char * vertex_file_path,
                    const char * fragment_file_path,
                    const char * scene_obj_file);
    void geomPass();
    unsigned int getPositionTexture()
    {
        return gPosition;
    }

    unsigned int getNormalTexture()
    {
        return gNormal;
    }

    unsigned int getDiffuseColorTexture()
    {
        return gDiffuseColor;
    }

    unsigned int getSpecularColorTexture()
    {
        return gSpecularColor;
    }

    unsigned int getAmbientColorTexture()
    {
        return gAmbientColor;
    }

    ~GeomPassHandler()
    {
        delete scene;
        glDeleteProgram(programID);
        glDeleteVertexArrays(1, &VertexArrayID);
    }
private:
    GLuint programID;
    Scene * scene;
    unsigned int gBuffer;
    unsigned int gPosition, gNormal, gDiffuseColor, gSpecularColor, gAmbientColor;
    GLuint VertexArrayID;
    void initializeGBuffer(int windowWidth, int windowHeight);
    void use();
};


#endif //DEFERRED_GEOMPASSHANDLER_H
