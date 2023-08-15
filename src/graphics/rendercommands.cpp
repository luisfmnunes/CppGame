#include<graphics/rendercommands.hpp>
#include<graphics/mesh.hpp>
#include<graphics/shader.hpp>
#include<graphics/helpers.hpp>

#include<log.hpp>


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

            glDrawArrays(GL_TRIANGLE_STRIP, 0, mesh->GetVertexCount()); LOG_CHECK_GL_ERROR

            shader->Unbind();
            mesh->Unbind();

        }
        else{
            LOG_WARN("Attempting to execute RenderMesh with invalid data");
        }
    }



}