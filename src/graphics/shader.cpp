#include<graphics/shader.hpp>
#include<graphics/helpers.hpp>
#include<log.hpp>


#include<glad/glad.h>

namespace game::graphics{

    Shader::Shader(const std::string& vertex, const std::string& fragment){

        mProgramId = glCreateProgram(); LOG_CHECK_GL_ERROR

        int status = GL_FALSE;
        char errorLog[512];

        // Shader Initialization
        uint32_t vertexShaderId = glCreateShader(GL_VERTEX_SHADER); LOG_CHECK_GL_ERROR
        {
            const GLchar* glSource = vertex.c_str();
            glShaderSource(vertexShaderId, 1, &glSource, NULL); LOG_CHECK_GL_ERROR
            glCompileShader(vertexShaderId); LOG_CHECK_GL_ERROR

            glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &status); LOG_CHECK_GL_ERROR
            
            if(status != GL_TRUE){
                glGetShaderInfoLog(vertexShaderId, sizeof(errorLog), NULL, errorLog); LOG_CHECK_GL_ERROR
                LOG_ERROR("Shader compilation error: {}", errorLog);
            } else {
                glAttachShader(mProgramId, vertexShaderId); LOG_CHECK_GL_ERROR
            }
        }

        uint32_t fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER); LOG_CHECK_GL_ERROR

        if(status == GL_TRUE){
        // Fragment Initialization
            const GLchar* glSource = fragment.c_str();
            glShaderSource(fragmentShaderId, 1, &glSource, NULL); LOG_CHECK_GL_ERROR
            glCompileShader(fragmentShaderId); LOG_CHECK_GL_ERROR

            glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &status); LOG_CHECK_GL_ERROR
            
            if(status != GL_TRUE){
                glGetShaderInfoLog(fragmentShaderId, sizeof(errorLog), NULL, errorLog); LOG_CHECK_GL_ERROR
                LOG_ERROR("Fragment shader compilation error: {}", errorLog);
            } else {
                glAttachShader(mProgramId, fragmentShaderId); LOG_CHECK_GL_ERROR
            }
        }

        // Assert Shader 
        LOG_ASSERT(status == GL_TRUE, "Error Compiling Shader");

        if (status == GL_TRUE){
            glLinkProgram(mProgramId); LOG_CHECK_GL_ERROR
            glValidateProgram(mProgramId); LOG_CHECK_GL_ERROR
            glGetProgramiv(mProgramId, GL_LINK_STATUS, &status); LOG_CHECK_GL_ERROR

            if(status != GL_TRUE){
                glGetProgramInfoLog(mProgramId, sizeof(errorLog), NULL, errorLog); LOG_CHECK_GL_ERROR
                LOG_ERROR("Shader link error: {}", errorLog);
                glDeleteProgram(mProgramId); LOG_CHECK_GL_ERROR

                mProgramId = -1;
            }
        }

        glDeleteShader(vertexShaderId); LOG_CHECK_GL_ERROR
        glDeleteShader(fragmentShaderId); LOG_CHECK_GL_ERROR


    }

    Shader::~Shader(){
        glUseProgram(0); LOG_CHECK_GL_ERROR
        glDeleteProgram(mProgramId); LOG_CHECK_GL_ERROR
    }

    void Shader::Bind(){
        glUseProgram(mProgramId); LOG_CHECK_GL_ERROR
    }

    void Shader::Unbind(){
        glUseProgram(0); LOG_CHECK_GL_ERROR
    }

    void Shader::SetUniformInt(const std::string &name, int val)
    {
        glUseProgram(mProgramId); LOG_CHECK_GL_ERROR
        glUniform1i(GetUniformLocation(name), val); LOG_CHECK_GL_ERROR
    }

    void Shader::SetUniformFloat(const std::string &name, float val)
    {
        glUseProgram(mProgramId); LOG_CHECK_GL_ERROR
        glUniform1f(GetUniformLocation(name), val); LOG_CHECK_GL_ERROR
    }

    void Shader::SetUniformFloat2(const std::string &name, float val1, float val2)
    {
        glUseProgram(mProgramId); LOG_CHECK_GL_ERROR
        glUniform2f(GetUniformLocation(name), val1, val2); LOG_CHECK_GL_ERROR
    }

    void Shader::SetUniformFloat3(const std::string &name, float val1, float val2, float val3)
    {
        glUseProgram(mProgramId); LOG_CHECK_GL_ERROR
        glUniform3f(GetUniformLocation(name), val1, val2, val3); LOG_CHECK_GL_ERROR
    }

    void Shader::SetUniformFloat4(const std::string &name, float val1, float val2, float val3, float val4)
    {
        glUseProgram(mProgramId); LOG_CHECK_GL_ERROR
        glUniform4f(GetUniformLocation(name), val1, val2, val3, val4); LOG_CHECK_GL_ERROR
    }

    int Shader::GetUniformLocation(const std::string &name)
    {
        auto it = mUniformLocations.find(name);
        if (it == mUniformLocations.end())
            mUniformLocations[name] = glGetUniformLocation(mProgramId, name.c_str()); LOG_CHECK_GL_ERROR

        return mUniformLocations[name];
    }

}

