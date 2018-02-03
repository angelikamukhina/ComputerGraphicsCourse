#include <GL/glew.h>
#include "Window.h"
#include <functional>
#include <AntTweakBar.h>


Window* Window::instance = 0;

void processInput(GLFWwindow *_window)
{
    Window * window = Window::getInstance();
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);

    if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
        window->camera->ProcessKeyboard(FORWARD, window->deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
        window->camera->ProcessKeyboard(BACKWARD, window->deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
        window->camera->ProcessKeyboard(LEFT, window->deltaTime);
    if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
        window->camera->ProcessKeyboard(RIGHT, window->deltaTime);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* _window, double xpos, double ypos)
{
    if(!TwEventMousePosGLFW(int(xpos), int(ypos))) {
        Window *window = Window::getInstance();
        if (window->firstMouse) {
            window->lastX = xpos;
            window->lastY = ypos;
            window->firstMouse = false;
        }

        float xoffset = xpos - window->lastX;
        float yoffset = window->lastY - ypos; // reversed since y-coordinates go from bottom to top

        window->lastX = xpos;
        window->lastY = ypos;

        window->camera->ProcessMouseMovement(xoffset, yoffset);
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* _window, double xoffset, double yoffset)
{
    Window * window = Window::getInstance();
    window->camera->ProcessMouseScroll(yoffset);
}

void mouseButtonCallback(GLFWwindow * window, int button, int action, int) {
    TwEventMouseButtonGLFW(button, action);
}


Window::Window(int width, int height)
        : width(width),
          height(height) {
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
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, static_cast<GLFWmousebuttonfun>(mouseButtonCallback));

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        assert(0);
    }

    lastX = (float)width / 2.0f;
    lastY = (float)height / 2.0f;
};

