// Include standard headers
#include <cstdio>
#include <vector>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ShadersLoader.h"
#include "TransformHandler.h"
#include "Window.h"
#include "Scene.h"

// We would expect width and height to be 1024 and 768
int windowWidth = 1024;
int windowHeight = 768;

int main( void )
{
    Window* window = Window::getInstance(windowWidth, windowHeight);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = ShadersLoader::LoadShaders( "ShadowMapping.vert", "ShadowMapping.frag" );
    glUseProgram(programID);
    // Get a handle for our "MVP" uniform
    GLint MatrixID = glGetUniformLocation(programID, "MVP");
    GLint ViewMatrixID = glGetUniformLocation(programID, "V");
    GLint ModelMatrixID = glGetUniformLocation(programID, "M");

    GLint MatDiffuseColorID = glGetUniformLocation(programID, "MaterialDiffuseColor");
    GLint MatAmbientuseColorID = glGetUniformLocation(programID, "MaterialAmbientColor");
    GLint MatSpecularColorID = glGetUniformLocation(programID, "MaterialSpecularColor");

    Scene scene("scene.obj", MatrixID, ModelMatrixID, ViewMatrixID,
                MatDiffuseColorID, MatAmbientuseColorID, MatSpecularColorID);

    Light* staticLight = Light::getStatic();
    Light* movingLight = Light::getMoving();

    std::vector<Light*> lights{staticLight, movingLight};

    // Create and compile our GLSL program from the shaders
    GLuint depthProgramID = ShadersLoader::LoadShaders( "DepthRTT.vert", "DepthRTT.frag" );

    for (auto light : lights)
    {
        glUseProgram(depthProgramID);
        // Get a handle for our "MVP" uniform
        GLint depthMatrixID = glGetUniformLocation(depthProgramID, "depthMVP");
        light->setMatrixID(depthMatrixID);

        // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
        GLuint FramebufferName = 0;
        glGenFramebuffers(1, &FramebufferName);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

        light->setFramebuffer(FramebufferName);
        // Depth texture. Slower than a depth buffer, but you can sample it later in your shader
        GLuint depthTexture;
        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

        // No color output in the bound framebuffer, only depth.
        glDrawBuffer(GL_NONE);

        // Always check that our framebuffer is ok
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            return false;
        light->setTexture(depthTexture);
    }

    do{
        for (auto light : lights)
        {
            GLuint FramebufferName = light->getFramebuffer();
            // Render to our framebuffer
            glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
            glViewport(0, 0, windowWidth, windowWidth); // Render on the whole framebuffer, complete from the lower left corner to the upper right

            // We don't use bias in the shader, but instead we draw back faces,
            // which are already separated from the front faces by a small distance
            // (if your geometry is made this way)
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Use our shader
            glUseProgram(depthProgramID);

            // 1rst attribute buffer : vertices
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, scene.getVertexbuffer());
            glVertexAttribPointer(
                    0,  // The attribute we want to configure
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void*)0            // array buffer offset
            );
            scene.drawShadows(light);
            glDisableVertexAttribArray(0);

        }

        // Render to the screen
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glViewport(0, 0, windowWidth, windowHeight); // Render on the whole framebuffer, complete from the lower left corner to the upper right
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, scene.getVertexbuffer());
        glVertexAttribPointer(
                0,                  // attribute
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );

        // 2nd attribute buffer : normals
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, scene.getNormalbuffer());
        glVertexAttribPointer(
                1,                                // attribute
                3,                                // size
                GL_FLOAT,                         // type
                GL_FALSE,                         // normalized?
                0,                                // stride
                (void*)0                          // array buffer offset
        );

        // Compute the MVP matrix from keyboard and mouse input
        TransformHandler::computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix = TransformHandler::getProjectionMatrix();
        glm::mat4 ViewMatrix = TransformHandler::getViewMatrix();

        const GLenum depthTextures[] = {GL_TEXTURE0, GL_TEXTURE1};

        for (size_t i = 0; i < lights.size(); ++i) {
            glActiveTexture(depthTextures[i]);
            auto light = lights[i];
            glBindTexture(GL_TEXTURE_2D, light->getTexture());
            std::string lightIdx = std::to_string(i);
            const GLint positionID = glGetUniformLocation(programID, ("LightPositions[" + lightIdx + "]").c_str());
            glm::vec3 lightPos = light->getPos();
            glUniform3f(positionID, lightPos.x, lightPos.y, lightPos.z);
            const GLint DepthBiasID = glGetUniformLocation(programID, ("DepthBiasVPs[" + lightIdx + "]").c_str());
            glm::mat4 depthBiasMVP = light->getDepthBiasVP();
            glUniformMatrix4fv(DepthBiasID, 1, GL_FALSE, &depthBiasMVP[0][0]);
            const auto shadowMaps = "shadowMaps[" + lightIdx + "]";
            const GLint ShadowMapID = glGetUniformLocation(programID, shadowMaps.c_str());
            glUniform1i(ShadowMapID, static_cast<GLint>(i));
            glUniformMatrix4fv(DepthBiasID, 1, GL_FALSE, &depthBiasMVP[0][0]);
        }

        scene.drawScene();
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        for (auto light : lights)
        {
            light->moveLight();
        }
        window->endLoop();
    } while(window->shouldNotEndLoop());

    // Cleanup VBO and shader
    glDeleteProgram(programID);
    glDeleteProgram(depthProgramID);

    glDeleteVertexArrays(1, &VertexArrayID);

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

