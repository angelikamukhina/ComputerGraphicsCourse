#include "LightDepthPassHandler.h"
#include "ShadersLoader.h"

LightDepthPassHandler::LightDepthPassHandler(const char * vert_file_path, const char * frag_file_path) {
    programID = ShadersLoader::LoadShaders(vert_file_path, frag_file_path);
}

void LightDepthPassHandler::getDepthTextures(std::vector<Light *> const &lights) {
    for (auto light : lights) {
        glUseProgram(programID);
        // Get a handle for our "MVP" uniform
        GLint depthMatrixID = glGetUniformLocation(programID, "depthMVP");
        light->setMatrixID(depthMatrixID);

        // The framebuffer, which regroups 0, 1, or more textures, and 0 or 1 depth buffer.
        GLuint FramebufferName = 0;
        glGenFramebuffers(1, &FramebufferName);
        glBindFramebuffer(GL_FRAMEBUFFER, FramebufferName);

        light->setFramebuffer(FramebufferName);
        // Depth texture. Slower than a depth buffer, but you can sample it later in your shader
        GLuint depthTexture;
        glGenTextures(1, &depthTexture);
        glBindTexture(GL_TEXTURE_2D, depthTexture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, 1024, 1024, 0, GL_DEPTH_COMPONENT, GL_FLOAT, 0);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_R_TO_TEXTURE);

        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthTexture, 0);

        // No color output in the bound framebuffer, only depth.
        glDrawBuffer(GL_NONE);

        // Always check that our framebuffer is ok
        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            assert(0);
        light->setTexture(depthTexture);
    }
}
