#include<graphics/rendercommands.hpp>
#include<log.hpp>

#include<graphics/mesh.hpp>
#include<graphics/shader.hpp>
#include<glad/glad.h>

namespace game::graphics::rendercommands
{

    void RenderMesh::Execute()
    {
        std::shared_ptr<Mesh> mesh = mMesh.lock();
        std::shared_ptr<Shader> shader = mShader.lock();

        if (mesh && shader){

            mesh->Bind();
            shader->Bind();

            glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->GetVertexCount());

            shader->Unbind();
            mesh->Unbind();

        }
        else{
            LOG_WARN("Attempting to execute RenderMesh with invalid data");
        }
    }



}