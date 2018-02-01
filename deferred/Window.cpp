#include <GL/glew.h>
#include "Window.h"
#include <functional>
#include <AntTweakBar.h>

Window* Window::instance = 0;

void mouseButtonCallback(GLFWwindow * window, int button, int action, int) {
    TwEventMouseButtonGLFW(button, action);
}

void mousePosCallback(GLFWwindow * window, double x, double y) {
    TwEventMousePosGLFW(int(x), int(y));
}

Window::Window(int width, int height)
        : width(width),
          height(height)
{
    glfwInit();
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( width, height, "Deferred lighting", nullptr, nullptr);
    if( window == nullptr){
        std::cerr << "Unable to create glfw window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPosCallback(window, static_cast<GLFWcursorposfun>(mousePosCallback));
    glfwSetMouseButtonCallback(window, static_cast<GLFWmousebuttonfun>(mouseButtonCallback));

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        assert(0);
    }
};

