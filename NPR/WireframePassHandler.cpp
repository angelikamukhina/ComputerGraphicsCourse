#include <functional>
#include <cassert>
#include "WireframePassHandler.h"
#include "ShadersLoader.h"
#include "Scene.h"

bool WireframePassHandler::initialized = false;

GLuint WireframePassHandler::programID;
GLint WireframePassHandler::mvpID;
GLint WireframePassHandler::lineWidthID;


void setupTexture() {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

WireframePassHandler::WireframePassHandler(const char * vertFilePath, const char * fragFilePath, int width, int height)
    : width(width)
    , height(height)
{
    if (!initialized)
    {
        programID = ShadersLoader::LoadShaders(vertFilePath, fragFilePath);
        mvpID = glGetUniformLocation(programID, "MVP");
        lineWidthID = glGetUniformLocation(programID, "f_thickness");
        initialized = true;
    }

    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
    setupTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    setupTexture();
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);

    const GLenum drawBuffers[] = {GL_COLOR_ATTACHMENT0};
    glDrawBuffers(1, drawBuffers);

    auto fbo_status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

    assert(fbo_status == GL_FRAMEBUFFER_COMPLETE);
}

void WireframePassHandler::pass(bool inverse, float linewidth, Object * object, GLint vertexbuffer, GLint bcbuffer)
{
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT);

    use();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    if (inverse)
    {
        glClearDepth(0.0);
        glClear(GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_GREATER);
    }
    else
    {
        glClearDepth(1.0);
        glClear(GL_DEPTH_BUFFER_BIT);
        glDepthFunc(GL_LESS);
    }
    glUniform1f(lineWidthID, linewidth);
//    draw_model();

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
    glBindBuffer(GL_ARRAY_BUFFER, bcbuffer);
    glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            0,
            (void *) 0
    );

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArrays(GL_TRIANGLES, object->getVertexOffset(),
                 static_cast<GLsizei>(object->getVertices().size()));

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

WireframePassHandler::~WireframePassHandler()
{
    glDeleteTextures(1, &texture);
    glDeleteFramebuffers(1, &framebuffer);
}
