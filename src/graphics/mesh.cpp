#include <graphics/mesh.hpp>
#include <glad/glad.h>


namespace game::graphics{

    Mesh::Mesh(float* vertexArray, uint64_t vertexCount, uint64_t dimensions)
        : mVertexCount(vertexCount) 
    {
        glGenVertexArrays(1, &mVao);
        glBindVertexArray(mVao);

        glGenBuffers(1, &mPositionVbo);
        glBindBuffer(GL_ARRAY_BUFFER, mPositionVbo);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * dimensions * sizeof(float), vertexArray, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, dimensions, GL_FLOAT, GL_FALSE, 0, 0);

        glDisableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); //Unbinds VBO 

        glBindVertexArray(0); // Unbinds VAO
    }

    Mesh::~Mesh(){
        // Clean GL Buffers

        glDeleteBuffers(1, &mPositionVbo);
        glDeleteVertexArrays(1, &mVao);
    }

    void Mesh::Bind(){
        glBindVertexArray(mVao);
        glEnableVertexAttribArray(0);
    }

    void Mesh::Unbind(){
        glDisableVertexAttribArray(0);
        glBindVertexArray(0);
    }

}