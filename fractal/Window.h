#ifndef CG_WINDOW_H
#define CG_WINDOW_H

#include <glm/vec2.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

class Window {
public:
    static Window* getInstance()
    {
        if (!instance)
        {
            assert(0);
        }
        return instance;
    }

    static Window* getInstance( int width, int height)
    {
        if(!instance)
        {
            instance = new Window(width, height);
        }
        return instance;
    }
    int getWidth()
    {
        return width;
    }

    int getHeiht()
    {
        return height;
    }

    glm::vec2 getScale()
    {
        glm::vec2 vecScale(zoom, zoom);
        if (height > width)
        {
            vecScale.y *= float(height) / width;
        }
        else
        {
            vecScale.x *= float(width) / height;
        }
        return vecScale;
    }

    glm::vec2 getShift()
    {
       return shift;
    }

    glm::vec2 getMouseCoords()
    {
        return mouseCoords;
    }

    void setNewMouseCoords(glm::vec2 newCoords)
    {
        mouseCoords = newCoords;
    }

    void changeShift(glm::vec2 shiftDelta)
    {
        shift += shiftDelta;
    }

    void increaseZoom()
    {
        zoom *= zoomMultiplier;
    }
    void decreaseZoom()
    {
        zoom /= zoomMultiplier;
    }
    glm::vec2 toNormilizedCoords(int x, int y);

    bool shouldNotEndLoop()
    {
        return glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
               glfwWindowShouldClose(window) == 0;
    }

    void endLoop()
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    ~Window()
    {
        delete instance;
    }
private:
    Window(int width, int height);
    static Window * instance;
    int width;
    int height;
    float zoom = 1.0f;
    float zoomMultiplier = 1.1f;
    GLFWwindow* window;
    glm::vec2 mouseCoords;
    glm::vec2 shift;
};

#endif //CG_WINDOW_H
