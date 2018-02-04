#ifndef CG_WINDOW_H
#define CG_WINDOW_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <AntTweakBar.h>
#include "Camera.h"

class Window {
public:
    static Window* getInstance() {
        if (!instance)
        {
            assert(0);
        }
        return instance;
    }

    static Window* getInstance( int width, int height) {
        if(!instance)
        {
            instance = new Window(width, height);
        }
        return instance;
    }
    int getWidth() {
        return width;
    }

    int getHeiht() {
        return height;
    }

    bool shouldNotEndLoop() {
        return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
               glfwWindowShouldClose(window) == 0;
    }

    void endLoop() {
        TwDraw();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Camera* getCamera() {
        return camera;
    }

    ~Window() {
        delete instance;
    }

    // camera
    Camera * camera = new Camera(glm::vec3(0.0f, 0.0f, 8.0f));
    float lastX;
    float lastY;
    bool firstMouse = true;

// timing
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    static Window * instance;
    int width;
    int height;
    GLFWwindow* window;
private:
    Window(int width, int height);

};

#endif //CG_WINDOW_H
