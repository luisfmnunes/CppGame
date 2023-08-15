#include <graphics/mesh.hpp>
#include <graphics/helpers.hpp>

#include <glad/glad.h>

namespace game::graphics{

    Mesh::Mesh(float* vertexArray, uint32_t vertexCount, uint32_t dimensions)
        : mVertexCount(vertexCount) 
    {
        glGenVertexArrays(1, &mVao); LOG_CHECK_GL_ERROR
        glBindVertexArray(mVao); LOG_CHECK_GL_ERROR

        glGenBuffers(1, &mPositionVbo); LOG_CHECK_GL_ERROR
        glBindBuffer(GL_ARRAY_BUFFER, mPositionVbo); LOG_CHECK_GL_ERROR
        glBufferData(GL_ARRAY_BUFFER, vertexCount * dimensions * sizeof(float), vertexArray, GL_STATIC_DRAW); LOG_CHECK_GL_ERROR

        glEnableVertexAttribArray(0); LOG_CHECK_GL_ERROR
        glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 0, 0); LOG_CHECK_GL_ERROR

        glDisableVertexAttribArray(0); LOG_CHECK_GL_ERROR
        glBindBuffer(GL_ARRAY_BUFFER, 0); LOG_CHECK_GL_ERROR //Unbinds VBO 

        glBindVertexArray(0); LOG_CHECK_GL_ERROR // Unbinds VAO
    }

    Mesh::~Mesh(){
        // Clean GL Buffers

        glDeleteBuffers(1, &mPositionVbo); LOG_CHECK_GL_ERROR
        glDeleteVertexArrays(1, &mVao); LOG_CHECK_GL_ERROR
    }

    void Mesh::Bind(){
        glBindVertexArray(mVao); LOG_CHECK_GL_ERROR
        glEnableVertexAttribArray(0); LOG_CHECK_GL_ERROR
    }

    void Mesh::Unbind(){
        glDisableVertexAttribArray(0); LOG_CHECK_GL_ERROR
        glBindVertexArray(0); LOG_CHECK_GL_ERROR
    }

}