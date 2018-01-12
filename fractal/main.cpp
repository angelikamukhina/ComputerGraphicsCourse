#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "ShadersLoader.h"
#include "Window.h"

int WIDTH = 600;
int HEIGHT = 400;
Window * window;

std::vector<glm::vec2>* getVertices() {
    auto * vertices = new std::vector<glm::vec2>();
    const GLsizei size = WIDTH * HEIGHT;
    vertices->resize(static_cast<unsigned long>(size));

    for (int y = 0; y < HEIGHT; ++y)
    {
        for (int x = 0; x < WIDTH; ++x)
        {
            int idx = y * WIDTH + x;
            (*vertices)[idx] = glm::vec2(2.0f * x / WIDTH - 1.0f, 2.0f * y / HEIGHT - 1.0f);
        }
    }
    return vertices;
}

GLuint getTexture(int length)
{
    auto colors = new  GLfloat[length];
    for (int i = 0; i < length; ++i)
    {
        colors[i] = GLfloat(i) / length;
    }
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_1D, textureID);
    glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, length, 0, GL_BGR, GL_FLOAT, colors);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glGenerateMipmap(GL_TEXTURE_1D);
    delete[] colors;
    return textureID;
}

int main( void )
{
    int maxIteration = 200;
    float radiusLimit = 2.0;
    std::cout << "Enter max iteration of fractal evaluating" << std::endl;
    std::cin >> maxIteration;
    std::cout << "Enter radius limit of fractal evaluating" << std::endl;
    std::cin >> radiusLimit;
    std::cout << "Enter window size" << std::endl;
    std::cout << "width: " << std::endl;
    std::cin >> WIDTH;
    std::cout << "height: " << std::endl;
    std::cin >> HEIGHT;

    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }
    window = Window::getInstance(WIDTH, HEIGHT);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }

    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // Create and compile our GLSL program from the shaders
    GLuint programID = ShadersLoader::LoadShaders( "./fractal.vertexShader", "./fractal.fragmentShader" );

    // Get a handle for our "MVP" uniform
    GLint MatrixID = glGetUniformLocation(programID, "MVP");
    GLint scaleID = glGetUniformLocation(programID, "scale");
    GLint shiftID = glGetUniformLocation(programID, "shift");

    glm::mat4 Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 100.0f);
    // Camera matrix
    glm::mat4 View       = glm::lookAt(
            glm::vec3(0.0f, 0.0f, 1.0f), // Camera is at (0,0,1), in World Space
            glm::vec3(0.0f, 0.0f, 0.0f), // and looks at the origin
            glm::vec3(0.0f, 1.0f, 0.0f)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    glm::mat4 Model      = glm::mat4(1.0f);
    glm::mat4 MVP        = Projection * View * Model;
    auto points = getVertices();

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, 2 * points->size() * sizeof(GLfloat), &(*points)[0], GL_STATIC_DRAW);

    GLuint texture = getTexture(1024);
    GLint textureID = glGetUniformLocation(programID, "sampler");

    GLint maxIterationID = glGetUniformLocation(programID, "maxIteration");
    GLint radiusLimitID = glGetUniformLocation(programID, "radiusLimit");

    do{

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_1D, texture);
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniform1i(maxIterationID, maxIteration);
        glUniform1f(radiusLimitID, radiusLimit);
        glm::vec2 scaleVec = window->getScale();
        glUniform2fv(scaleID, 1, &scaleVec[0]);
        glm::vec2 shift = window->getShift();
        glUniform2fv(shiftID, 1, &shift[0]);
        glUniform1i(textureID, 0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
                2,                  // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                0,                  // stride
                (void*)0            // array buffer offset
        );

        glDrawArrays(GL_POINTS, 0, points->size());
        glDisableVertexAttribArray(0);

        window->endLoop();
    } while(window->shouldNotEndLoop());

    // Cleanup VBO and shader
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteProgram(programID);
    glDeleteVertexArrays(1, &VertexArrayID);
    delete points;
    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}















