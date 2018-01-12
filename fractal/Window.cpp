#include "Window.h"
#include <functional>

Window* Window::instance = 0;

glm::vec2 Window::toNormilizedCoords(int x, int y)
{
    return getScale() * glm::vec2(2.0f * x / width - 1.0f, -(2.0f * y / height - 1.0f));
}

void mousePosCallback(GLFWwindow *_window, double x, double y)
{
    Window* window = Window::getInstance();
    glm::ivec2 curMouseCoords(x, y);
    if (glfwGetMouseButton(_window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        auto normCurCoords = window->toNormilizedCoords(curMouseCoords.x, curMouseCoords.y);
        glm::vec2 mouseCoords = window->getMouseCoords();
        auto normPrevCoords = window->toNormilizedCoords(mouseCoords.x, mouseCoords.y);
        glm::vec2 mouseCoordsDelta = normCurCoords - normPrevCoords;
        window->changeShift(-mouseCoordsDelta);
    }
    window->setNewMouseCoords(curMouseCoords);
}

void mouseWheelCallback(GLFWwindow *, double xoffset, double yoffset)
{
    Window* window = Window::getInstance();
    glm::vec2 mouseCoords = window->getMouseCoords();
    auto normMouseCoords = window->toNormilizedCoords(mouseCoords.x, mouseCoords.y);
    auto mouseCoordsBefore = normMouseCoords;
    if (yoffset < 0)
    {
        window->increaseZoom();
    }
    else
    {
        window->decreaseZoom();
    }
    auto mouseCoordsAfter = window->toNormilizedCoords(mouseCoords.x, mouseCoords.y);

    auto shiftDelta = mouseCoordsBefore - mouseCoordsAfter;
    window->changeShift(shiftDelta);
}

Window::Window(int width, int height)
        : width(width),
          height(height)
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    window = glfwCreateWindow( width, height, "Mandelbrot", nullptr, nullptr);
    if( window == nullptr){
        std::cerr << "Unable to create glfw window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetCursorPosCallback(window, static_cast<GLFWcursorposfun>(mousePosCallback));
    glfwSetScrollCallback(window, static_cast<GLFWscrollfun>(mouseWheelCallback));
};

