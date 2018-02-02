#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "AntTweakBar.h"

#include <iostream>
#include "Window.h"
#include "GeomPassHandler.h"
#include "LightingPassHandler.h"
#include "DebugDrawTexturesHandler.h"

const int MAX_LIGHTS_NUMBER = 32;


int main()
{
    Window* window = Window::getInstance(utils::SCR_WIDTH, utils::SCR_HEIGHT);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    auto * geomPassHandler = new GeomPassHandler("../g_buffer.vert", "../g_buffer.frag",
                                    "../scene.obj");

    LightingPassHandler lightPassHandler("../deferred_shading.vert", "../deferred_shading.frag",
                                         geomPassHandler, MAX_LIGHTS_NUMBER);
    DebugDrawTexturesHandler debug("../fbo_debug.vert", "../fbo_debug.frag", geomPassHandler);

    TwInit(TW_OPENGL_CORE, NULL);
    TwWindowSize(utils::SCR_WIDTH, utils::SCR_HEIGHT);
    TwBar * GUI = TwNewBar("Settings");
    TwAddVarRW(GUI, "Lights number", TW_TYPE_UINT32, &lightPassHandler.lightsCount,
               ("step=1 min=0 max=" + std::to_string(MAX_LIGHTS_NUMBER)).c_str());
    TwEnumVal modes[] = {
            {utils::Mode::DEFERRED_LIGHTING, "Deferred lighting"},
            {utils::Mode::POSITION, "Position"},
            {utils::Mode::NORMALS, "Normals"},
            {utils::Mode::DIFFUSE_COLOR, "Diffuse color"},
            {utils::Mode::AMBIENT_COLOR, "Ambient color"},
            {utils::Mode::SPECULAR_COLOR, "Specular color"},
    };
    TwType modeType = TwDefineEnum("ModeType", modes, 6);
    TwAddVarRW(GUI, "Mode", modeType, &utils::mode, NULL);

    unsigned int rboDepth;
    glGenRenderbuffers(1, &rboDepth);
    glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, utils::SCR_WIDTH, utils::SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "Framebuffer not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    while (window->shouldNotEndLoop()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        geomPassHandler->geomPass();

        glViewport(0, 0, utils::SCR_WIDTH, utils::SCR_HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glDisable(GL_DEPTH_TEST);

        if (utils::mode != utils::DEFERRED_LIGHTING) {
            debug.debugDraw();
        } else {
            lightPassHandler.lightingPass();
        }
        TwDraw();
        window->endLoop();
    }
    delete geomPassHandler;
    TwTerminate();
    glfwTerminate();
    return 0;
}