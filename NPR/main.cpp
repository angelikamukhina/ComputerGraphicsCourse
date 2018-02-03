// Include standard headers
#include <cstdio>
#include <vector>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <AntTweakBar.h>
#include "ShadersLoader.h"
#include "Window.h"
#include "Scene.h"
#include "utils.h"
#include "LightDepthPassHandler.h"

int windowWidth = 1280;
int windowHeight = 720;

int main()
{
    Window* window = Window::getInstance(windowWidth, windowHeight);

    TwInit(TW_OPENGL_CORE, NULL);
    TwWindowSize(window->width, window->height);
    TwBar * GUI = TwNewBar("Settings");

    TwEnumVal modes[] = {
            {utils::Mode::TOON_SHADING, "Toon shading"},
            {utils::Mode::WIREFRAME, "Wireframe"}
    };
    TwType modeType = TwDefineEnum("ModeType", modes, 2);
    TwAddVarRW(GUI, "Mode", modeType, &utils::mode, NULL);

    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);

    auto * toonShadowsPassHandler = new ToonShadowsPassHandler( "../ShadowMapping.vert", "../ShadowMapping.frag" );
    Scene scene("../scene.obj", toonShadowsPassHandler);

    Light* staticLight = Light::getStatic();
    Light* movingLight = Light::getMoving();

    std::vector<Light*> lights{staticLight, movingLight};

    LightDepthPassHandler depthPassHandler("../DepthRTT.vert", "../DepthRTT.frag");
    depthPassHandler.setDepthTextures(lights);

    do{
        utils::Mode mode = utils::mode;

        if (mode == utils::TOON_SHADING) {
            for (auto light : lights) {
                GLuint FramebufferName = light->getFramebuffer();
                glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);
                glViewport(0, 0, windowWidth, windowHeight);
                glEnable(GL_CULL_FACE);
                glCullFace(GL_BACK);

                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                depthPassHandler.use();
                scene.drawShadows(light);
            }

            // Render to the screen
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            glViewport(0, 0, windowWidth, windowHeight);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            toonShadowsPassHandler->initializeShader(lights);
        }

        scene.drawScene(mode);

        for (auto light : lights)
        {
            light->moveLight();
        }

        window->endLoop();
    } while(window->shouldNotEndLoop());

    delete toonShadowsPassHandler;
    TwTerminate();
    glfwTerminate();

    return 0;
}

