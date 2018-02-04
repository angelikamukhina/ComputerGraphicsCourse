#include <cstdio>
#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <AntTweakBar.h>
#include <functional>
#include "ShadersLoader.h"
#include "Window.h"
#include "Scene.h"
#include "utils.h"
#include "LightDepthPassHandler.h"
#include "ToonShadowsPassHandler.h"
#include "WireframePassHandler.h"
#include "CombinePassHandler.h"

int windowWidth = 1280;
int windowHeight = 720;

int main() {
    Window *window = Window::getInstance(windowWidth, windowHeight);

    TwInit(TW_OPENGL_CORE, NULL);
    TwWindowSize(window->width, window->height);
    TwBar *GUI = TwNewBar("Settings");

    TwEnumVal modes[] = {
            {utils::Mode::TOON_SHADING, "Toon shading"},
            {utils::Mode::WIREFRAME,    "Wireframe"}
    };
    TwType modeType = TwDefineEnum("ModeType", modes, 2);
    TwAddVarRW(GUI, "Mode", modeType, &utils::mode, NULL);
    TwAddVarRW(GUI, "Pause", TW_TYPE_BOOLCPP, &utils::pause, NULL);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    const Scene scene("scene.obj");
    auto toonShadowsPassHandler = new ToonShadowsPassHandler("ShadowMapping.vert", "ShadowMapping.frag");
    auto first = new WireframePassHandler("Wireframe.vert", "Wireframe.frag", windowWidth, windowHeight);
    auto second = new WireframePassHandler("Wireframe.vert", "Wireframe.frag", windowWidth, windowHeight);
    auto third = new WireframePassHandler("Wireframe.vert", "Wireframe.frag", windowWidth, windowHeight);
    auto combiner = new CombinePassHandler("Combine.vert", "Combine.frag");

    GLuint VertexArrayID, vertexbuffer, normalbuffer, bcbuffer;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, scene.getVertices().size() * sizeof(glm::vec3), &scene.getVertices()[0],
                 GL_STATIC_DRAW);

    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, scene.getNormals().size() * sizeof(glm::vec3), &scene.getNormals()[0],
                 GL_STATIC_DRAW);

    glGenBuffers(1, &bcbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, bcbuffer);
    std::vector<glm::vec3> barycentricCoordinates(scene.getVertices().size());
    for (size_t i = 0; i < scene.getVertices().size(); ++i) {
        glm::vec3 v{0};
        v[i % 3] = 1;
        barycentricCoordinates[i] = v;
    }
    glBufferData(GL_ARRAY_BUFFER, scene.getVertices().size() * sizeof(glm::vec3), &barycentricCoordinates[0],
                 GL_STATIC_DRAW);

    Light* light = Light::getStatic();

    LightDepthPassHandler depthPassHandler("DepthRTT.vert", "DepthRTT.frag");
    depthPassHandler.setDepthTextures(light);

    do {
        glClearColor(0.0, 0.0, 0.4, 1.0);

        utils::Mode mode = utils::mode;
        bool pause = utils::pause;

        glm::mat4 Projection = glm::perspective(glm::radians(window->camera->Zoom),
                                                (float) window->width / (float) window->height,
                                                0.1f, 100.0f);
        glm::mat4 View = window->camera->GetViewMatrix();

        if (mode == utils::TOON_SHADING) {
            GLuint FramebufferName = light->getFramebuffer();
            glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
            glViewport(0, 0, windowWidth, windowHeight);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);

            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            depthPassHandler.use();
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                    0,  // The attribute we want to configure
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void *) 0            // array buffer offset
            );

            for (auto object : scene.getObjects()) {
                glm::mat4 Model = object->getModelMat();
                glm::mat4 depthProj = light->getProjection();
                glm::mat4 depthView = light->getView();
                glm::mat4 depthMVP = depthProj * depthView * Model;
                glUniformMatrix4fv(light->getMatrixID(), 1, GL_FALSE, &depthMVP[0][0]);
                glDrawArrays(GL_TRIANGLES, object->getVertexOffset(),
                             static_cast<GLsizei>(object->getVertices().size()));
            }
            glDisableVertexAttribArray(0);

            // Render to the screen
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, windowWidth, windowHeight);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            toonShadowsPassHandler->initializeShader(light);

            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
            glVertexAttribPointer(
                    0,                  // attribute
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    0,                  // stride
                    (void *) 0            // array buffer offset
            );

            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
            glVertexAttribPointer(
                    1,
                    3,
                    GL_FLOAT,
                    GL_FALSE,
                    0,
                    (void *) 0
            );

            for (auto object : scene.getObjects()) {
                glm::mat4 Model = object->getModelMat();
                glm::mat4 MVP = Projection * View * Model;
                glm::vec3 diffuseColor = object->getDiffuseColor();
                glm::vec3 ambientColor = object->getAmbientColor();
                glm::vec3 specularColor = object->getSpecularColor();

                glUniform3f(toonShadowsPassHandler->MatDiffuseColorID, diffuseColor.r, diffuseColor.g,
                            diffuseColor.b);
                glUniform3f(toonShadowsPassHandler->MatAmbientuseColorID, ambientColor.r, ambientColor.g,
                            ambientColor.b);
                glUniform3f(toonShadowsPassHandler->MatSpecularColorID, specularColor.r, specularColor.g,
                            specularColor.b);

                glUniformMatrix4fv(toonShadowsPassHandler->MatrixID, 1, GL_FALSE, &MVP[0][0]);
                glUniformMatrix4fv(toonShadowsPassHandler->ModelMatrixID, 1, GL_FALSE, &Model[0][0]);
                glUniformMatrix4fv(toonShadowsPassHandler->ViewMatrixID, 1, GL_FALSE, &View[0][0]);
                glDrawArrays(GL_TRIANGLES, object->getVertexOffset(),
                             static_cast<GLsizei>(object->getVertices().size()));
            }
            glDisableVertexAttribArray(0);
            glDisableVertexAttribArray(1);
        } else if (mode == utils::WIREFRAME) {
            for (auto object : scene.getObjects()) {
                glUseProgram(WireframePassHandler::programID);
                glm::mat4 Model = object->getModelMat();
                glm::mat4 MVP = Projection * View * Model;
                glUniformMatrix4fv(WireframePassHandler::mvpID, 1, GL_FALSE, &MVP[0][0]);

                first->pass(true, 1.5, object, vertexbuffer, bcbuffer);
                second->pass(false, 4.5, object, vertexbuffer, bcbuffer);
                third->pass(false, 1.5, object, vertexbuffer, bcbuffer);

                glBindFramebuffer(GL_FRAMEBUFFER, 0);
                glViewport(0, 0, windowWidth, windowHeight);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                combiner->combinePass(first->getOutTexture(), second->getOutTexture(), third->getOutTexture(),
                    glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
            }
        } else {
            assert(0);
        }

        if (!pause) {
            light->moveLight();

            for (auto object : scene.getObjects()) {
                object->rotate();
            }
        } else {
            for (auto object : scene.getObjects()) {
                object->setCorrectLastUpdateTime();
            }
        }
        window->endLoop();
    } while (window->shouldNotEndLoop());

    delete toonShadowsPassHandler;

    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteBuffers(1, &normalbuffer);
    TwTerminate();
    glfwTerminate();

    return 0;
}

