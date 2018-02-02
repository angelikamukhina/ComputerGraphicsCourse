#ifndef CG_WINDOW_H
#define CG_WINDOW_H

#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

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
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ~Window() {
        delete instance;
    }
private:
    Window(int width, int height);
    static Window * instance;
    int width;
    int height;
    GLFWwindow* window;
};

#endif //CG_WINDOW_H
