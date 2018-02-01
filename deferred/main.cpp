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

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
unsigned int loadTexture(const char *path, bool gammaCorrection);
void renderQuad();
//void renderCube();

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;
// camera
Camera camera(glm::vec3(0.0f, 5.0f, 5.0f));
float lastX = (float)SCR_WIDTH / 2.0;
float lastY = (float)SCR_HEIGHT / 2.0;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int lightsCount = 8;
enum Mode {
    DEFERRED_LIGHTING, POSITION, NORMALS, DIFFUSE_COLOR, AMBIENT_COLOR, SPECULAR_COLOR
};

Mode mode = DEFERRED_LIGHTING;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Deferred lighting", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetScrollCallback(window, scroll_callback);

//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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
    TwAddVarRW(GUI, "lightsCount", TW_TYPE_UINT32, &lightsCount, "step=1");
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

//    glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW); // - Directly redirect GLFW mouse button events to AntTweakBar
    // Set GLFW event callbacks. I removed glfwSetWindowSizeCallback for conciseness
    glfwSetMouseButtonCallback(window, (GLFWmousebuttonfun)TwEventMouseButtonGLFW); // - Directly redirect GLFW mouse button events to AntTweakBar
    glfwSetCursorPosCallback(window, (GLFWcursorposfun)TwEventMousePosGLFW);          // - Directly redirect GLFW mouse position events to AntTweakBar
    glfwSetScrollCallback(window, (GLFWscrollfun)TwEventMouseWheelGLFW);    // - Directly redirect GLFW mouse wheel events to AntTweakBar
    glfwSetKeyCallback(window, (GLFWkeyfun)TwEventKeyGLFW);                         // - Directly redirect GLFW key events to AntTweakBar
    glfwSetCharCallback(window, (GLFWcharfun)TwEventCharGLFW);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    // Cull triangles which normal is not towards the camera
    glEnable(GL_CULL_FACE);
    // build and compile shaders
    // -------------------------
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    GLuint geomProgramID = ShadersLoader::LoadShaders("g_buffer.vert", "g_buffer.frag");
    GLuint lightProgramID = ShadersLoader::LoadShaders("deferred_shading.vert", "deferred_shading.frag");
    GLuint debugProramID = ShadersLoader::LoadShaders("fbo_debug.vert", "fbo_debug.frag");

    glUseProgram(geomProgramID);

    GLint DiffuseColorID = glGetUniformLocation(geomProgramID, "diffuse");
    GLint SpecularColorID = glGetUniformLocation(geomProgramID, "specular");
    GLint AmbientColorID = glGetUniformLocation(geomProgramID, "ambient");

//    Scene scene("scene.obj");
    // load models
    // -----------
    Scene scene("scene.obj", DiffuseColorID, AmbientColorID, SpecularColorID);


    // configure g-buffer framebuffer
    // ------------------------------
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
    // create and attach depth buffer (renderbuffer)
    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    // finally check if framebuffer is complete
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // lighting info
    // -------------
    std::vector<Light> lights;
    srand(13);
    for (unsigned int i = 0; i < lightsCount; i++)
    {
        // calculate slightly random offsets
        float xPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        float yPos = 0.1;
        float zPos = ((rand() % 100) / 100.0) * 6.0 - 3.0;
        // also calculate random color
        float rColor = (float)rand() / RAND_MAX; // between 0.5 and 1.0
        float gColor = (float)rand() / RAND_MAX; // between 0.5 and 1.0
        float bColor = (float)rand() / RAND_MAX; // between 0.5 and 1.0
        lights.push_back(Light(glm::vec3(xPos, yPos, zPos), glm::vec3(rColor, gColor, bColor)));
    }

    // shader configuration
    // --------------------
    glUseProgram(lightProgramID);
    glUniform1i(glGetUniformLocation(lightProgramID, "gPosition"), 0);
    glUniform1i(glGetUniformLocation(lightProgramID, "gNormal"), 1);
    glUniform1i(glGetUniformLocation(lightProgramID, "gDiffuseColor"), 2);
    glUniform1i(glGetUniformLocation(lightProgramID, "gSpecularColor"), 3);
    glUniform1i(glGetUniformLocation(lightProgramID, "gAmbientColor"), 4);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // 1. geometry pass: render scene's geometry/color data into gbuffer
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

        glUniformMatrix4fv(glGetUniformLocation(geomProgramID, "projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(geomProgramID, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(geomProgramID, "model"), 1, GL_FALSE, &model[0][0]);

        scene.drawScene();

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        // 2. lighting pass: calculate lighting by iterating over a screen filled quad pixel-by-pixel using the gbuffer's content.
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

            // send light relevant uniforms
            for (unsigned int i = 0; i < lights.size(); i++)
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
            // finally render quad
            renderQuad();
        }

        // 2.5. copy content of geometry's depth buffer to default framebuffer's depth buffer
        // ----------------------------------------------------------------------------------
        glBindFramebuffer(GL_READ_FRAMEBUFFER, gBuffer);
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0); // write to default framebuffer
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

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}
