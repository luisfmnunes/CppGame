#pragma once

#include<log.hpp>

#include<glad/glad.h>
#include<string>

namespace game::graphics
{

    inline void CheckGLError()
    {
        GLenum error = glGetError();

        bool shouldAssert = error != GL_NO_ERROR;
        while (error != GL_NO_ERROR)
        {

            std::string error_str;

            switch(error)
            {
            case GL_INVALID_OPERATION:              error_str = "GL_INVALID_OPERATION"; break;
            case GL_INVALID_ENUM:                   error_str = "GL_INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                  error_str = "GL_INVALID_VALUE"; break;
            case GL_OUT_OF_MEMORY:                  error_str = "GL_OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:  error_str = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
            default: error_str =                    std::to_string(error); break;
            }

            LOG_ERROR("OpenGL_Error: {}", error_str);
            error = glGetError();
        }

        LOG_ASSERT(!shouldAssert, "OpenGL Error!");

    }

}

#ifndef GAME_RELEASE
#define LOG_CHECK_GL_ERROR game::graphics::CheckGLError();
#else
#define LOG_CHECK_GL_ERROR (void)0
#endif