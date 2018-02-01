#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "AntTweakBar.h"

#include <iostream>
#include "camera.h"
#include "Lights.h"
#include "Scene.h"
#include "ShadersLoader.h"

void mouseButtonCallback(GLFWwindow * window, int button, int action, int);
void mousePosCallback(GLFWwindow * window, double xpos, double ypos);
void processInput(GLFWwindow *window);
void renderQuad();

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
// camera
Camera camera(glm::vec3(0.0f, 5.0f, 5.0f));

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int lightsCount = 32;
enum Mode {
    DEFERRED_LIGHTING, POSITION, NORMALS, DIFFUSE_COLOR, AMBIENT_COLOR, SPECULAR_COLOR
};

Mode mode = DEFERRED_LIGHTING;



int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Deferred lighting", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    TwInit(TW_OPENGL_CORE, NULL);
    TwWindowSize(SCR_WIDTH, SCR_HEIGHT);
    TwBar * GUI = TwNewBar("Settings");
    TwAddVarRW(GUI, "Lights number", TW_TYPE_UINT32, &lightsCount, "step=1 min=0 max=32");
    TwEnumVal modes[] = {
            {Mode::DEFERRED_LIGHTING, "Deferred lighting"},
            {Mode::POSITION, "Position"},
            {Mode::NORMALS, "Normals"},
            {Mode::DIFFUSE_COLOR, "Diffuse color"},
            {Mode::AMBIENT_COLOR, "Ambient color"},
            {Mode::SPECULAR_COLOR, "Specular color"},
    };
    TwType modeType = TwDefineEnum("ModeType", modes, 6);
    TwAddVarRW(GUI, "Mode", modeType, &mode, NULL);

    glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun) mouseButtonCallback);
    glfwSetCursorPosCallback(window, (GLFWcursorposfun) mousePosCallback);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    GLuint geomProgramID = ShadersLoader::LoadShaders("../g_buffer.vert", "../g_buffer.frag");
    GLuint lightProgramID = ShadersLoader::LoadShaders("../deferred_shading.vert", "../deferred_shading.frag");
    GLuint debugProramID = ShadersLoader::LoadShaders("../fbo_debug.vert", "../fbo_debug.frag");

    glUseProgram(geomProgramID);

    GLint DiffuseColorID = glGetUniformLocation(geomProgramID, "diffuse");
    GLint SpecularColorID = glGetUniformLocation(geomProgramID, "specular");
    GLint AmbientColorID = glGetUniformLocation(geomProgramID, "ambient");

    Scene scene("../scene.obj", DiffuseColorID, AmbientColorID, SpecularColorID);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    unsigned int gBuffer;
    glGenFramebuffers(1, &gBuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
    unsigned int gPosition, gNormal, gDiffuseColor, gSpecularColor, gAmbientColor;
    // position color buffer
    glGenTextures(1, &gPosition);
    glBindTexture(GL_TEXTURE_2D, gPosition);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);
    // normal color buffer
    glGenTextures(1, &gNormal);
    glBindTexture(GL_TEXTURE_2D, gNormal);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);
    // color + specular color buffer
    glGenTextures(1, &gDiffuseColor);
    glBindTexture(GL_TEXTURE_2D, gDiffuseColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gDiffuseColor, 0);

    glGenTextures(1, &gSpecularColor);
    glBindTexture(GL_TEXTURE_2D, gSpecularColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gSpecularColor, 0);

    glGenTextures(1, &gAmbientColor);
    glBindTexture(GL_TEXTURE_2D, gAmbientColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, gAmbientColor, 0);

    // tell OpenGL which color attachments we'll use (of this framebuffer) for rendering
    unsigned int attachments[5] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2,
                                    GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4};
    glDrawBuffers(5, attachments);
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    std::vector<Light> lights;
    srand(13);
    for (unsigned int i = 0; i < lightsCount; i++)
    {
        // calculate slightly random offsets
        float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        float yPos = 0.0;
        float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        // also calculate random color
        float rColor = (float)rand() / RAND_MAX; // between 0.0 and 1.0
        float gColor = (float)rand() / RAND_MAX; // between 0.0 and 1.0
        float bColor = (float)rand() / RAND_MAX; // between 0.0 and 1.0
        lights.push_back(Light(glm::vec3(xPos, yPos, zPos), glm::vec3(rColor, gColor, bColor)));
    }

    glUseProgram(lightProgramID);
    glUniform1i(glGetUniformLocation(lightProgramID, "gPosition"), 0);
    glUniform1i(glGetUniformLocation(lightProgramID, "gNormal"), 1);
    glUniform1i(glGetUniformLocation(lightProgramID, "gDiffuseColor"), 2);
    glUniform1i(glGetUniformLocation(lightProgramID, "gSpecularColor"), 3);
    glUniform1i(glGetUniformLocation(lightProgramID, "gAmbientColor"), 4);

    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // geometry pass
        // -----------------------------------------------------------------
        glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 model = glm::mat4(1.0);

        glUseProgram(geomProgramID);

        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, scene.getVertexbuffer());
        glVertexAttribPointer(
                0,                  // attribute
                3,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*) nullptr     // array buffer offset
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
                (void*) nullptr                   // array buffer offset
        );

        glUniformMatrix4fv(glGetUniformLocation(geomProgramID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(geomProgramID, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(geomProgramID, "model"), 1, GL_FALSE, &model[0][0]);

        scene.drawScene();

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // lighting pass
        // -----------------------------------------------------------------------------------------------------------------------
        glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);

        if (mode != DEFERRED_LIGHTING) {

            glUseProgram(debugProramID);
            glActiveTexture(GL_TEXTURE0);
            unsigned int texture;
            switch (mode)
            {
                case POSITION: texture = gPosition;
                    break;
                case NORMALS: texture = gNormal;
                    break;
                case DIFFUSE_COLOR: texture = gDiffuseColor;
                    break;
                case AMBIENT_COLOR: texture = gAmbientColor;
                    break;
                case SPECULAR_COLOR: texture = gSpecularColor;
                    break;
            }
            glBindTexture(GL_TEXTURE_2D, texture);
            GLint textureID = glGetUniformLocation(debugProramID, "fboAttachment");
            glUniform1i(textureID, 0);
            renderQuad();
        }
        else
        {
            glUseProgram(lightProgramID);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, gPosition);
            glActiveTexture(GL_TEXTURE1);
            glBindTexture(GL_TEXTURE_2D, gNormal);
            glActiveTexture(GL_TEXTURE2);
            glBindTexture(GL_TEXTURE_2D, gDiffuseColor);
            glActiveTexture(GL_TEXTURE3);
            glBindTexture(GL_TEXTURE_2D, gSpecularColor);
            glActiveTexture(GL_TEXTURE4);
            glBindTexture(GL_TEXTURE_2D, gAmbientColor);

            GLint cameraPosID = glGetUniformLocation(lightProgramID, "viewPos");
            glUniform3f(cameraPosID, camera.Position.x, camera.Position.y, camera.Position.z);

            GLint actLightNumber = glGetUniformLocation(lightProgramID, "actLightNumber");
            glUniform1i(actLightNumber, lightsCount);

            for (unsigned int i = 0; i < lightsCount; i++)
            {
                GLint positionID = glGetUniformLocation(lightProgramID, ("lights[" + std::to_string(i) + "].Position").c_str());
                glm::vec3 position = lights[i].getPos();
                glUniform3f(positionID, position.x, position.y, position.z);
                GLint colorID = glGetUniformLocation(lightProgramID, ("lights[" + std::to_string(i) + "].Color").c_str());
                glm::vec3 color = lights[i].getColor();
                glUniform3f(colorID, color.r, color.g, color.b);
                lights[i].moveLight();
                const float linear = 0.8;
                const float quadratic = 8;
                GLint linearID = glGetUniformLocation(lightProgramID, ("lights[" + std::to_string(i) + "].Linear").c_str());
                glUniform1f(linearID, linear);
                GLint quadraticID = glGetUniformLocation(lightProgramID, ("lights[" + std::to_string(i) + "].Quadratic").c_str());
                glUniform1f(quadraticID, quadratic);
            }
            renderQuad();
        }

        glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(0, 0, SCR_WIDTH, SCR_HEIGHT, 0, 0, SCR_WIDTH, SCR_HEIGHT, GL_DEPTH_BUFFER_BIT, GL_NEAREST);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // Draw GUI
        TwDraw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    TwTerminate();
    glfwTerminate();
    return 0;
}

unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
    if (quadVAO == 0)
    {
        float quadVertices[] = {
                // positions        // texture Coords
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        };
        glGenBuffers(1, &quadVBO);
        glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);

        // setup plane VAO
        glGenVertexArrays(1, &quadVAO);
        glBindVertexArray(quadVAO);
    }

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void mouseButtonCallback(GLFWwindow * window, int button, int action, int) {
    TwEventMouseButtonGLFW(button, action);
}

void mousePosCallback(GLFWwindow * window, double xpos, double ypos) {
    TwEventMousePosGLFW(int(xpos), int(ypos));
}
