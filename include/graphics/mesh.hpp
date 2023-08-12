#pragma once

#include <cstdint>

namespace game::graphics{

    class Mesh{
    public:
        Mesh(float* vertexArray, uint64_t vertexCount, uint64_t dimensions);
        ~Mesh();

        void Bind();
        void Unbind();

        inline uint32_t GetVertexCount() const { return mVertexCount; }
    
    private:
        uint32_t mVertexCount;
        uint32_t mVao; // Vertex Array Object
        uint32_t mPositionVbo; // Vertex Buffer Object

    };
}