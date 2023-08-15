#include <manager/renderManager.hpp>
#include <graphics/helpers.hpp>

#include<log.hpp>

#include<glad/glad.h>

namespace game::managers
{

    void RenderManager::Initialize()
    {
        LOG_INFO("OpenGL Info:\n   Vendor:\t{}\n  Renderer:\t{}\n  Version:\t{}", 
            (const char*) glGetString(GL_VENDOR),
            (const char*) glGetString(GL_RENDERER),
            (const char*) glGetString(GL_VERSION)
        );

        //Initialize OpenGL
    
        glEnable(GL_DEPTH_TEST); LOG_CHECK_GL_ERROR
        glDepthFunc(GL_LEQUAL); LOG_CHECK_GL_ERROR

        glEnable(GL_BLEND); LOG_CHECK_GL_ERROR
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC1_ALPHA); LOG_CHECK_GL_ERROR

        SetClearColor(0, 0, 0, 1);

    }

    void RenderManager::Shutdown()
    {
        while(!mRenderCommands.empty()){
            mRenderCommands.pop();
        }
    }

    void RenderManager::Clear(){
        LOG_ASSERT(mRenderCommands.empty(), "Unflushed Render Commands in Queue!");
        while(!mRenderCommands.empty()){
            mRenderCommands.pop();
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); LOG_CHECK_GL_ERROR
    }

    void RenderManager::SetClearColor(float r, float g, float b, float a){
        glClearColor(r, g, b, a); LOG_CHECK_GL_ERROR
    }

    void RenderManager::Submit(std::unique_ptr<graphics::rendercommands::RenderCommand> rc)
    {
        mRenderCommands.push(std::move(rc));
    }

    void RenderManager::Flush()
    {
        while(!mRenderCommands.empty()){
            auto rc = std::move(mRenderCommands.front());
            mRenderCommands.pop();

            rc->Execute();
        }

    }

}